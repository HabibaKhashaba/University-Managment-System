#include "student.h"

Student::Student() {}

QString Student::getStudentId() const
{
    return studentId;
}

void Student::setStudentId(const QString &newStudentId)
{
    studentId = newStudentId;
}

QString Student::getEnrolledCoursesId() const
{
    return enrolledCoursesId;
}

void Student::setEnrolledCoursesId(const QString &newEnrolledCoursesId)
{
    enrolledCoursesId = newEnrolledCoursesId;
}

QString Student::getAcademicLevel() const
{
    return academicLevel;
}

void Student::setAcademicLevel(const QString &newAcademicLevel)
{
    academicLevel = newAcademicLevel;
}

QString Student::getCompletedCoursesId() const
{
    return completedCoursesId;
}

void Student::setCompletedCoursesId(const QString &newCompletedCoursesId)
{
    completedCoursesId = newCompletedCoursesId;
}

QString Student::getRegisteredEvents() const
{
    return registeredEvents;
}

void Student::setRegisteredEvents(const QString &newRegisteredEvents)
{
    registeredEvents = newRegisteredEvents;
}
