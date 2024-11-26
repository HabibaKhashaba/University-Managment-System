#ifndef STUDENTUI_H
#define STUDENTUI_H

#include "course.h"
#include "event.h"
#include "student.h"
#include <QMainWindow>

namespace Ui {
class StudentUi;
}

class StudentUi : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentUi(QWidget *parent = nullptr, QString studentEmail = "");
    ~StudentUi();

private slots:
    void on_coursesBtn_clicked();

    void on_listViewCourses_clicked(const QModelIndex &index);

    void on_add_new_course_button_clicked();

    void on_studentsBtn_clicked();

    void on_eventsBtn_clicked();

    void on_listViewEvents_clicked(const QModelIndex &index);

    void on_add_new_course_button_2_clicked();

private:
    void fetchCourses();
    void updateCoursesList();
    void fetchEvents();
    void findStudentByEmail(const QString& email);
    void saveStudentsToFile();
    void updateEventsList();
    QString getEventsWithUpcomingDeadlines(const std::map<QString, Event>& events);
    QString getCoursesWithUpcomingDeadlines(const std::map<QString, Course>& courses);
    std::map<QString, Student> fetchStudents();
    Ui::StudentUi *ui;
    std::map<QString, Course> *courses;
    Student currentStudent;
    std::map<QString, Event> *events;
};

#endif // STUDENTUI_H
