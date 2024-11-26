#include "course.h"

Course::Course() {}

QString Course::getCourseId() const
{
    return courseId;
}

void Course::setCourseId(const QString &newCourseId)
{
    courseId = newCourseId;
}

QString Course::getName() const
{
    return name;
}

void Course::setName(const QString &newName)
{
    name = newName;
}

QString Course::getDepartment() const
{
    return department;
}

void Course::setDepartment(const QString &newDepartment)
{
    department = newDepartment;
}

QString Course::getSchedule() const
{
    return schedule;
}

void Course::setSchedule(const QString &newSchedule)
{
    schedule = newSchedule;
}

QString Course::getPreRequisits() const
{
    return preRequisits;
}

void Course::setPreRequisits(const QString &newPreRequisits)
{
    preRequisits = newPreRequisits;
}

QString Course::getInstructor() const
{
    return instructor;
}

void Course::setInstructor(const QString &newInstructor)
{
    instructor = newInstructor;
}

QString Course::getStatus() const
{
    return status;
}

void Course::setStatus(const QString &newStatus)
{
    status = newStatus;
}

QString Course::getRegistreationDeadline() const
{
    return registreationDeadline;
}

void Course::setRegistreationDeadline(const QString &newRegistreationDeadline)
{
    registreationDeadline = newRegistreationDeadline;
}
