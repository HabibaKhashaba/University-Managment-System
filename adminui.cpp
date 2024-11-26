#include "adminui.h"
#include "QtCore/qfile.h"
#include "ui_adminui.h"

#include <QMessageBox>
#include <QStringListModel>
#include <QDir>

AdminUi::AdminUi(QWidget *parent, QString name)
    : QMainWindow(parent)
    , ui(new Ui::AdminUi)
{
    ui->setupUi(this);
    fetchCourses();
    fetchStudents();
    fetchEvents();
    ui->coursesBox->show();
    ui->studentsBox->hide();
    ui->eventsBox->hide();
}

AdminUi::~AdminUi()
{
    delete ui;
    saveCoursesToFile();
    saveStudentsToFile();
    saveEventsToFile();
    QCoreApplication::quit();
    QMessageBox::information(this, "Confirmation", "All your data has been saved");
}

void AdminUi::fetchCourses()
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

void AdminUi::updateCoursesList()
{
    QStringList courseKeys;
    for (const auto& [key, value] : *courses) {
        courseKeys.append(key);
    }

    QStringListModel* model = new QStringListModel(this);
    model->setStringList(courseKeys);
    ui->listViewCourses->setModel(model);
}

void AdminUi::saveCoursesToFile()
{
    QString filePath = QDir::homePath() + "/StudentManagmentSystem/courses.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error: Unable to open file for writing.";
        return;
    }

    QTextStream out(&file);

    for (const auto& [key, course] : *courses) {
        out << course.getCourseId() << "|"
            << course.getName() << "|"
            << course.getDepartment() << "|"
            << course.getSchedule() << "|"
            << course.getPreRequisits() << "|"
            << course.getInstructor() << "|"
            << course.getStatus() << "|"
            << course.getRegistreationDeadline() << "\n";
    }

    file.close();
}

void AdminUi::fetchStudents()
{
    QString filePath = QDir::homePath() + "/StudentManagmentSystem/students.txt";
    QFile file(filePath);
    students = new std::map<QString, Student>;
    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Warning", "Students file not found or cannot be opened!");
        return;
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
    updateStudentsList();
}

void AdminUi::updateStudentsList()
{
    QStringList studentsKeys;
    for (const auto& [key, value] : *students) {
        studentsKeys.append(key);
    }

    QStringListModel* model = new QStringListModel(this);
    model->setStringList(studentsKeys);
    ui->listViewStudents->setModel(model);
}

void AdminUi::saveStudentsToFile()
{
    QString filePath = QDir::homePath() + "/StudentManagmentSystem/students.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error: Unable to open file for writing.";
        return;
    }

    QTextStream out(&file);
    for (const auto& [key, student] : *students) {
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

void AdminUi::fetchEvents()
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

void AdminUi::updateEventsList()
{
    QStringList eventsKeys;
    for (const auto& [key, value] : *events) {
        eventsKeys.append(key);
    }

    QStringListModel* model = new QStringListModel(this);
    model->setStringList(eventsKeys);
    ui->listViewEvent->setModel(model);
}

void AdminUi::saveEventsToFile()
{
    QString filePath = QDir::homePath() + "/StudentManagmentSystem/events.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error: Unable to open file for writing.";
        return;
    }

    QTextStream out(&file);
    for (const auto& [key, event] : *events) {
        out << event.getEventId() << "|"
            << event.getTitle() << "|"
            << event.getDescription() << "|"
            << event.getSpeaker() << "|"
            << event.getSchedule() << "\n";
    }

    file.close();
}

void AdminUi::on_add_new_course_button_clicked()
{
    QString courseId = ui->course_Id->text();
    QString name = ui->course_name->text();
    QString department = ui->course_department->text();
    QString schedule = ui->course_schedule->text();
    QString preRequisits = ui->course_prerequists->text();
    QString instructor = ui->course_instructor->text();
    QString status = ui->course_status->text();
    QString deadline = ui->course_deadline->text();

    if (courseId.isEmpty() || name.isEmpty() || department.isEmpty() || schedule.isEmpty() ||
        preRequisits.isEmpty() || instructor.isEmpty() || status.isEmpty() || deadline.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please fill all fields!");
        return;
    }

    QStringList dateParts = deadline.split('-');
    if (dateParts.size() != 3 ||
        dateParts[0].toInt() < 1 || dateParts[0].toInt() > 31 ||
        dateParts[1].toInt() < 1 || dateParts[1].toInt() > 12 ||
        dateParts[2].toInt() < 1900 || dateParts[2].toInt() > 2100) {
        QMessageBox::warning(this, "Warning", "Deadline must be in the format DD-MM-YYYY!");
        return;
    }

    if (status != "Open" && status != "Closed") {
        QMessageBox::warning(this, "Warning", "Status must be either 'Open' or 'Closed'!");
        return;
    }

    if (!preRequisits.contains(',') && preRequisits.simplified().contains(' ')) {
        QMessageBox::warning(
            this,
            "Warning",
            "Pre-requisites must either be a single word or a comma-separated list (e.g., Math, Science, Physics)!"
            );
        return;
    }

    Course course;
    course.setCourseId(courseId);
    course.setName(name);
    course.setDepartment(department);
    course.setSchedule(schedule);
    course.setPreRequisits(preRequisits);
    course.setInstructor(instructor);
    course.setStatus(status);
    course.setRegistreationDeadline(deadline);

    (*courses)[name] = course;

    QMessageBox::information(this, "Success", "Course added successfully!");

    ui->course_Id->clear();
    ui->course_name->clear();
    ui->course_department->clear();
    ui->course_schedule->clear();
    ui->course_prerequists->clear();
    ui->course_instructor->clear();
    ui->course_status->clear();
    ui->course_deadline->clear();
    updateCoursesList();
}


void AdminUi::on_listViewCourses_clicked(const QModelIndex &index)
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


void AdminUi::on_update_course_button_clicked()
{
    QString courseId = ui->course_Id->text();
    QString name = ui->course_name->text();
    QString department = ui->course_department->text();
    QString schedule = ui->course_schedule->text();
    QString preRequisits = ui->course_prerequists->text();
    QString instructor = ui->course_instructor->text();
    QString status = ui->course_status->text();
    QString deadline = ui->course_deadline->text();

    if (courseId.isEmpty() || name.isEmpty() || department.isEmpty() || schedule.isEmpty() ||
        preRequisits.isEmpty() || instructor.isEmpty() || status.isEmpty() || deadline.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please fill all fields!");
        return;
    }

    QStringList dateParts = deadline.split('-');
    if (dateParts.size() != 3 ||
        dateParts[0].toInt() < 1 || dateParts[0].toInt() > 31 ||
        dateParts[1].toInt() < 1 || dateParts[1].toInt() > 12 ||
        dateParts[2].toInt() < 1900 || dateParts[2].toInt() > 2100) {
        QMessageBox::warning(this, "Warning", "Deadline must be in the format DD-MM-YYYY!");
        return;
    }

    if (status != "Open" && status != "Closed") {
        QMessageBox::warning(this, "Warning", "Status must be either 'Open' or 'Closed'!");
        return;
    }

    if (!preRequisits.contains(',') && preRequisits.simplified().contains(' ')) {
        QMessageBox::warning(
            this,
            "Warning",
            "Pre-requisites must either be a single word or a comma-separated list (e.g., Math, Science, Physics)!"
            );
        return;
    }

    Course course;
    course.setCourseId(courseId);
    course.setName(name);
    course.setDepartment(department);
    course.setSchedule(schedule);
    course.setPreRequisits(preRequisits);
    course.setInstructor(instructor);
    course.setStatus(status);
    course.setRegistreationDeadline(deadline);

    (*courses)[name] = course;
        QMessageBox::information(this, "Success", "Course added successfully!");

    ui->course_Id->clear();
    ui->course_name->clear();
    ui->course_department->clear();
    ui->course_schedule->clear();
    ui->course_prerequists->clear();
    ui->course_instructor->clear();
    ui->course_status->clear();
    ui->course_deadline->clear();
    updateCoursesList();
}


void AdminUi::on_delete_course_button_clicked()
{
    QString courseId = ui->course_Id->text();
        (*courses).erase(courseId);

        QMessageBox::information(this, "Success", "Course deleted successfully!");

        ui->course_Id->clear();
        ui->course_name->clear();
        ui->course_department->clear();
        ui->course_schedule->clear();
        ui->course_prerequists->clear();
        ui->course_instructor->clear();
        ui->course_status->clear();
        ui->course_deadline->clear();

        updateCoursesList();
}

void AdminUi::on_coursesBtn_clicked()
{
    ui->coursesBox->show();
    ui->studentsBox->hide();
    ui->eventsBox->hide();
}


void AdminUi::on_studentsBtn_clicked()
{
    ui->studentsBox->show();
    ui->coursesBox->hide();
    ui->eventsBox->hide();
}


void AdminUi::on_listViewStudents_clicked(const QModelIndex &index)
{
    QString key = index.data(Qt::DisplayRole).toString();
    Student student = (*students)[key];
    ui->student_name->setText(student.getName());
    ui->student_email->setText(student.getEmail());
    ui->student_password->setText(student.getPassword());
    ui->student_id->setText(student.getStudentId());
    ui->student_academic_year->setText(student.getAcademicLevel());
    ui->student_completed_courses->setText(student.getCompletedCoursesId());
    ui->student_course->setText(student.getEnrolledCoursesId());
    ui->student_events->setText(student.getRegisteredEvents());
}


void AdminUi::on_add_new_student_button_clicked()
{
    QString name = ui->student_name->text();
    QString email = ui->student_email->text();
    QString password = ui->student_password->text();
    QString studentId = ui->student_id->text();
    QString academicYear = ui->student_academic_year->text();
    QString completedCourses = ui->student_completed_courses->text();
    QString enrolledCourses = ui->student_course->text();
    QString events = ui->student_events->text();

    if (name.isEmpty() || email.isEmpty() || password.isEmpty() || studentId.isEmpty() || academicYear.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please fill all mandatory fields!");
        return;
    }

    Student newStudent;
    newStudent.setName(name);
    newStudent.setEmail(email);
    newStudent.setPassword(password);
    newStudent.setStudentId(studentId);
    newStudent.setAcademicLevel(academicYear);
    newStudent.setCompletedCoursesId(completedCourses);
    newStudent.setEnrolledCoursesId(enrolledCourses);
    newStudent.setRegisteredEvents(events);

    (*students)[studentId] = newStudent;

    updateStudentsList();

    QMessageBox::information(this, "Success", "New student added successfully!");
}


void AdminUi::on_update_student_button_clicked()
{
    QString name = ui->student_name->text();
    QString email = ui->student_email->text();
    QString password = ui->student_password->text();
    QString studentId = ui->student_id->text();
    QString academicYear = ui->student_academic_year->text();
    QString completedCourses = ui->student_completed_courses->text();
    QString enrolledCourses = ui->student_course->text();
    QString events = ui->student_events->text();

    if (name.isEmpty() || email.isEmpty() || password.isEmpty() || studentId.isEmpty() || academicYear.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please fill all mandatory fields!");
        return;
    }

    Student newStudent;
    newStudent.setName(name);
    newStudent.setEmail(email);
    newStudent.setPassword(password);
    newStudent.setStudentId(studentId);
    newStudent.setAcademicLevel(academicYear);
    newStudent.setCompletedCoursesId(completedCourses);
    newStudent.setEnrolledCoursesId(enrolledCourses);
    newStudent.setRegisteredEvents(events);

    (*students)[studentId] = newStudent;

    updateStudentsList();
}


void AdminUi::on_delete_student_button_clicked()
{
    QString studentId = ui->student_id->text();
        students->erase(studentId);

        QMessageBox::information(this, "Success", "Student deleted successfully!");

        ui->student_id->clear();
        ui->student_name->clear();
        ui->student_email->clear();
        ui->student_password->clear();
        ui->student_academic_year->clear();
        ui->student_completed_courses->clear();
        ui->student_course->clear();
        ui->student_events->clear();

        updateStudentsList();
}


void AdminUi::on_eventsBtn_clicked()
{
    ui->eventsBox->show();
    ui->coursesBox->hide();
    ui->studentsBox->hide();
}


void AdminUi::on_listViewEvent_clicked(const QModelIndex &index)
{
    QString key = index.data(Qt::DisplayRole).toString();
    Event event = (*events)[key];

    ui->event_id->setText(event.getEventId());
    ui->event_title->setText(event.getTitle());
    ui->event_description->setText(event.getDescription());
    ui->event_speaker->setText(event.getSpeaker());
    ui->event_schedule->setText(event.getSchedule());
}


void AdminUi::on_update_event_button_clicked()
{
    QString eventId = ui->event_id->text();
    QString title = ui->event_title->text();
    QString description = ui->event_description->text();
    QString speaker = ui->event_speaker->text();
    QString schedule = ui->event_schedule->text();

    if (eventId.isEmpty() || title.isEmpty() || description.isEmpty() || speaker.isEmpty() || schedule.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please fill all fields!");
        return;
    }

    QStringList dateParts = schedule.split('-');
    if (dateParts.size() != 3 ||
        dateParts[0].toInt() < 1 || dateParts[0].toInt() > 31 ||
        dateParts[1].toInt() < 1 || dateParts[1].toInt() > 12 ||
        dateParts[2].toInt() < 1900 || dateParts[2].toInt() > 2100) {
        QMessageBox::warning(this, "Warning", "Schedule must be in the format DD-MM-YYYY!");
        return;
    }

    Event event;
    event.setEventId(eventId);
    event.setTitle(title);
    event.setDescription(description);
    event.setSpeaker(speaker);
    event.setSchedule(schedule);
    (*events)[eventId] = event;
    QMessageBox::information(this, "Success", "Event updated successfully!");

    ui->event_id->clear();
    ui->event_title->clear();
    ui->event_description->clear();
    ui->event_speaker->clear();
    ui->event_schedule->clear();

    updateEventsList();
}


void AdminUi::on_add_new_event_button_clicked()
{
    QString eventId = ui->event_id->text();
    QString title = ui->event_title->text();
    QString description = ui->event_description->text();
    QString speaker = ui->event_speaker->text();
    QString schedule = ui->event_schedule->text();

    if (eventId.isEmpty() || title.isEmpty() || description.isEmpty() || speaker.isEmpty() || schedule.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please fill all fields!");
        return;
    }

    QStringList dateParts = schedule.split('-');
    if (dateParts.size() != 3 ||
        dateParts[0].toInt() < 1 || dateParts[0].toInt() > 31 ||
        dateParts[1].toInt() < 1 || dateParts[1].toInt() > 12 ||
        dateParts[2].toInt() < 1900 || dateParts[2].toInt() > 2100) {
        QMessageBox::warning(this, "Warning", "Schedule must be in the format DD-MM-YYYY!");
        return;
    }

    Event newEvent;
    newEvent.setEventId(eventId);
    newEvent.setTitle(title);
    newEvent.setDescription(description);
    newEvent.setSpeaker(speaker);
    newEvent.setSchedule(schedule);

    (*events)[eventId] = newEvent;

    updateEventsList();

    QMessageBox::information(this, "Success", "New event added successfully!");
    ui->event_id->clear();
    ui->event_title->clear();
    ui->event_description->clear();
    ui->event_speaker->clear();
    ui->event_schedule->clear();
}


void AdminUi::on_delete_event_button_clicked()
{
    QString eventId = ui->event_id->text();

    if (eventId.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please provide an Event ID to delete!");
        return;
    }

    if (events->find(eventId) == events->end()) {
        QMessageBox::warning(this, "Warning", "Event not found!");
        return;
    }

    events->erase(eventId);

    QMessageBox::information(this, "Success", "Event deleted successfully!");

    // Clear the UI fields
    ui->event_id->clear();
    ui->event_title->clear();
    ui->event_description->clear();
    ui->event_speaker->clear();
    ui->event_schedule->clear();

    updateEventsList();
}

