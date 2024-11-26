#include "studentui.h"
#include "QtCore/qstringlistmodel.h"
#include "ui_studentui.h"

#include <QDir>
#include <QMessageBox>

StudentUi::StudentUi(QWidget *parent, QString student)
    : QMainWindow(parent)
    , ui(new Ui::StudentUi)
{
    ui->setupUi(this);
    ui->coursesBox->show();
    ui->profileBox->hide();
    ui->eventsBox->hide();
    fetchCourses();
    fetchEvents();
    findStudentByEmail(student);
}

StudentUi::~StudentUi()
{
    delete ui;
    saveStudentsToFile();
    QMessageBox::information(this, "Confirmation", "All your data has been saved");
}

void StudentUi::on_coursesBtn_clicked()
{
    ui->coursesBox->show();
    ui->profileBox->hide();
    ui->eventsBox->hide();
}

void StudentUi::fetchCourses()
{
    QString filePath = QDir::homePath() + "/StudentManagmentSystem/courses.txt";
    QFile file(filePath);
    courses = new std::map<QString, Course>;

    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Warning", "Courses file not found or cannot be opened!");
        return;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList attributes = line.split('|'); // Assuming '|' is used as the delimiter
        if (attributes.size() != 8) {
            QMessageBox::warning(this, "Warning", "Malformed line in courses file: " + line);
            continue;
        }
        Course course;
        course.setCourseId(attributes[0]);
        course.setName(attributes[1]);
        course.setDepartment(attributes[2]);
        course.setSchedule(attributes[3]);
        course.setPreRequisits(attributes[4]);
        course.setInstructor(attributes[5]);
        course.setStatus(attributes[6]);
        course.setRegistreationDeadline(attributes[7]);
        (*courses)[course.getCourseId()] = course;
    }

    file.close();
    updateCoursesList();
}

void StudentUi::updateCoursesList()
{
    QStringList courseKeys;
    for (const auto& [key, value] : *courses) {
        courseKeys.append(key);
    }

    QStringListModel* model = new QStringListModel(this);
    model->setStringList(courseKeys);
    ui->listViewCourses->setModel(model);
}

void StudentUi::fetchEvents()
{
    QString filePath = QDir::homePath() + "/StudentManagmentSystem/events.txt";
    QFile file(filePath);
    events = new std::map<QString, Event>;

    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Warning", "Events file not found or cannot be opened!");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList attributes = line.split('|');
        if (attributes.size() != 5) {
            QMessageBox::warning(this, "Warning", "Malformed line in events file: " + line);
            continue;
        }
        Event event;
        event.setEventId(attributes[0]);
        event.setTitle(attributes[1]);
        event.setDescription(attributes[2]);
        event.setSpeaker(attributes[3]);
        event.setSchedule(attributes[4]);
        (*events)[event.getEventId()] = event;
    }

    file.close();
    updateEventsList();
}

void StudentUi::findStudentByEmail(const QString &email)
{
    std::map<QString, Student> students = fetchStudents();
    for (const auto& [key, student] : students) {
        if (student.getEmail() == email) {
            // Set the selected student
            currentStudent = student;
            ui->student_academic_year->setText(currentStudent.getAcademicLevel());
            ui->student_complete_courses->setText(currentStudent.getCompletedCoursesId());
            ui->student_enrolled_courses->setText(currentStudent.getEnrolledCoursesId());
            ui->student_email->setText(currentStudent.getEmail());
            ui->student_password->setText(currentStudent.getPassword());
            ui->student_id->setText(currentStudent.getStudentId());
            ui->student_registered_events->setText(currentStudent.getRegisteredEvents());
            ui->student_name->setText(currentStudent.getName());
            QString upcommingCourses = getCoursesWithUpcomingDeadlines(*courses);
            ui->student_courses_deadline->setText(upcommingCourses);
            QString upcomminEvents = getEventsWithUpcomingDeadlines(*events);
            ui->student_event_deadline->setText(upcomminEvents);
            return;
        }
    }
    QMessageBox::warning(this, "Warning", "No student found with the provided email.");
}

void StudentUi::saveStudentsToFile()
{
    QString filePath = QDir::homePath() + "/StudentManagmentSystem/students.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error: Unable to open file for writing.";
        return;
    }

    std::map<QString, Student> students = fetchStudents();
    students[currentStudent.getStudentId()] = currentStudent;

    QTextStream out(&file);
    for (const auto& [key, student] : students) {
        out << student.getEmail() << "|"
            << student.getPassword() << "|"
            << student.getName() << "|"
            << student.getStudentId() << "|"
            << student.getAcademicLevel() << "|"
            << student.getEnrolledCoursesId() << "|"
            << student.getCompletedCoursesId() << "|"
            << student.getRegisteredEvents() << "\n";
    }

    file.close();
}

void StudentUi::updateEventsList()
{
    QStringList eventsKeys;
    for (const auto& [key, value] : *events) {
        eventsKeys.append(key);
    }

    QStringListModel* model = new QStringListModel(this);
    model->setStringList(eventsKeys);
    ui->listViewEvents->setModel(model);
}

QString StudentUi::getEventsWithUpcomingDeadlines(const std::map<QString, Event> &events)
{
    QString result;
    QDate currentDate = QDate::currentDate();

    for (const auto& [key, event] : events) {
        QString deadlineStr = event.getSchedule();
        QStringList dateParts = deadlineStr.split('-');

        if (dateParts.size() == 3) {
            QDate eventDate(dateParts[2].toInt(), dateParts[1].toInt(), dateParts[0].toInt());

            if (currentDate.daysTo(eventDate) <= 7 && currentDate.daysTo(eventDate) >= 0) {
                result += QString("Event: %1, Scheduled Date: %2\n")
                              .arg(event.getTitle())
                              .arg(deadlineStr);
            }
        }
    }

    if (result.isEmpty()) {
        result = "No events are scheduled within the next week.";
    } else {
        result = "Events scheduled within the next week:\n" + result;
    }

    return result;
}

QString StudentUi::getCoursesWithUpcomingDeadlines(const std::map<QString, Course> &courses)
{
    QString result;
    QDate currentDate = QDate::currentDate();

    for (const auto& [key, course] : courses) {
        QString deadlineStr = course.getRegistreationDeadline();
        QStringList dateParts = deadlineStr.split('-');

        if (dateParts.size() == 3) {
            QDate deadlineDate(dateParts[2].toInt(), dateParts[1].toInt(), dateParts[0].toInt());

            if (currentDate.daysTo(deadlineDate) <= 7 && currentDate.daysTo(deadlineDate) >= 0) {
                result += QString("Course: %1, Deadline: %2\n")
                              .arg(course.getName())
                              .arg(deadlineStr);
            }
        }
    }

    if (result.isEmpty()) {
        result = "No courses have deadlines within the next week.";
    } else {
        result = "Courses with upcoming deadlines:\n" + result;
    }

    return result;
}

std::map<QString, Student> StudentUi::fetchStudents()
{
    QString filePath = QDir::homePath() + "/StudentManagmentSystem/students.txt";
    QFile file(filePath);
    std::map<QString, Student> *students = new std::map<QString, Student>;
    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Warning", "Students file not found or cannot be opened!");
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList attributes = line.split('|');
        if (attributes.size() != 8) {
            QMessageBox::warning(this, "Warning", "Malformed line in students file: " + line);
            continue;
        }

        // Create a new User object
        Student student;
        student.setEmail(attributes[0]);
        student.setPassword(attributes[1]);
        student.setName(attributes[2]);
        student.setStudentId(attributes[3]);
        student.setAcademicLevel(attributes[4]);

        student.setEnrolledCoursesId(attributes[5]);
        student.setCompletedCoursesId(attributes[6]);
        student.setRegisteredEvents(attributes[7]);

        (*students)[student.getStudentId()] = student;
    }

    file.close();
    return *students;
}


void StudentUi::on_listViewCourses_clicked(const QModelIndex &index)
{
    QString key = index.data(Qt::DisplayRole).toString();
    Course course = (*courses)[key];
    ui->course_Id->setText(course.getCourseId());
    ui->course_name->setText(course.getName());
    ui->course_department->setText(course.getDepartment());
    ui->course_schedule->setText(course.getSchedule());
    ui->course_prerequists->setText(course.getPreRequisits());
    ui->course_instructor->setText(course.getInstructor());
    ui->course_status->setText(course.getStatus());
    ui->course_deadline->setText(course.getRegistreationDeadline());
}


void StudentUi::on_add_new_course_button_clicked()
{
    QString courseName = ui->course_name->text();

    if (courseName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a course.");
        return;
    }

    QString courseStatus = ui->course_status->text();

    if (courseStatus == "Closed") {
        QMessageBox::warning(this, "Warning", "The course is closed.");
        return;
    }

    QString currentCourses = currentStudent.getEnrolledCoursesId();
    QString completedCourses = currentStudent.getCompletedCoursesId();
    QString prerequisites = ui->course_prerequists->text();

    if (prerequisites != "-" && !prerequisites.isEmpty()) {
        QStringList prerequisiteList = prerequisites.split(",");
        for (const QString& prerequisite : prerequisiteList) {
            if (!completedCourses.contains(prerequisite.trimmed())) {
                QMessageBox::warning(
                    this,
                    "Warning",
                    "You cannot enroll in this course because you have not completed the prerequisite: " + prerequisite
                    );
                return;
            }
        }
    }

    if (currentCourses.contains(courseName)) {
        QMessageBox::information(this, "Information", "You are already enrolled in this course.");
        return;
    }

    if (completedCourses.contains(courseName)) {
        QMessageBox::information(this, "Information", "You have already completed this course.");
        return;
    }

    if (!currentCourses.isEmpty()) {
        currentCourses += "," + courseName;
    } else {
        currentCourses = courseName;
    }
    currentStudent.setEnrolledCoursesId(currentCourses);

    QMessageBox::information(this, "Success", "You have been successfully enrolled in the course!");
}


void StudentUi::on_studentsBtn_clicked()
{
    ui->coursesBox->hide();
    ui->eventsBox->hide();
    ui->profileBox->show();
}

void StudentUi::on_eventsBtn_clicked()
{
    ui->coursesBox->hide();
    ui->eventsBox->show();
    ui->profileBox->hide();
}


void StudentUi::on_listViewEvents_clicked(const QModelIndex &index)
{
    QString key = index.data(Qt::DisplayRole).toString();
    Event event = (*events)[key];

    ui->event_id->setText(event.getEventId());
    ui->event_title->setText(event.getTitle());
    ui->event_description->setText(event.getDescription());
    ui->event_speaker->setText(event.getSpeaker());
    ui->event_schedule->setText(event.getSchedule());
}


void StudentUi::on_add_new_course_button_2_clicked()
{
    QString eventId = ui->event_id->text();

    if (eventId.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select an event.");
        return;
    }

    currentStudent.setRegisteredEvents(currentStudent.getRegisteredEvents() + "," + eventId);

    QMessageBox::information(this, "Success", "You have been successfully enrolled in the course!");

}
