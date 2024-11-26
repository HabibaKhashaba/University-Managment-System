#ifndef STUDENT_H
#define STUDENT_H

#include "QtCore/qstring.h"
#include "user.h"
class Student: public User
{
public:
    Student();
    QString getStudentId() const;
    void setStudentId(const QString &newStudentId);

    QString getEnrolledCoursesId() const;
    void setEnrolledCoursesId(const QString &newEnrolledCoursesId);

    QString getAcademicLevel() const;
    void setAcademicLevel(const QString &newAcademicLevel);

    QString getCompletedCoursesId() const;
    void setCompletedCoursesId(const QString &newCompletedCoursesId);

    QString getRegisteredEvents() const;
    void setRegisteredEvents(const QString &newRegisteredEvents);

private:
    QString studentId;
    QString enrolledCoursesId;
    QString academicLevel;
    QString completedCoursesId;
    QString registeredEvents;
};

#endif // STUDENT_H
