#ifndef ADMINUI_H
#define ADMINUI_H

#include "course.h"
#include "event.h"
#include "student.h"
#include <QMainWindow>

namespace Ui {
class AdminUi;
}

class AdminUi : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminUi(QWidget *parent = nullptr, QString name = "temp");
    ~AdminUi();

private slots:
    void on_add_new_course_button_clicked();

    void on_listViewCourses_clicked(const QModelIndex &index);

    void on_update_course_button_clicked();

    void on_delete_course_button_clicked();


    void on_coursesBtn_clicked();

    void on_studentsBtn_clicked();

    void on_listViewStudents_clicked(const QModelIndex &index);

    void on_add_new_student_button_clicked();

    void on_update_student_button_clicked();

    void on_delete_student_button_clicked();

    void on_eventsBtn_clicked();

    void on_listViewEvent_clicked(const QModelIndex &index);

    void on_update_event_button_clicked();

    void on_add_new_event_button_clicked();

    void on_delete_event_button_clicked();

private:
    void fetchCourses();
    void updateCoursesList();
    void saveCoursesToFile();
    void fetchStudents();
    void updateStudentsList();
    void saveStudentsToFile();
    void fetchEvents();
    void updateEventsList();
    void saveEventsToFile();
    Ui::AdminUi *ui;
    std::map<QString, Course> *courses;
    std::map<QString, Student> *students;
    std::map<QString, Event> *events;
};

#endif // ADMINUI_H
