#ifndef COURSE_H
#define COURSE_H

#include "QtCore/qstring.h"
class Course
{
public:
    Course();
    QString getCourseId() const;
    void setCourseId(const QString &newCourseId);

    QString getName() const;
    void setName(const QString &newName);

    QString getDepartment() const;
    void setDepartment(const QString &newDepartment);

    QString getSchedule() const;
    void setSchedule(const QString &newSchedule);

    QString getPreRequisits() const;
    void setPreRequisits(const QString &newPreRequisits);

    QString getInstructor() const;
    void setInstructor(const QString &newInstructor);

    QString getStatus() const;
    void setStatus(const QString &newStatus);

    QString getRegistreationDeadline() const;
    void setRegistreationDeadline(const QString &newRegistreationDeadline);

private:
    QString courseId;
    QString name;
    QString department;
    QString schedule;
    QString preRequisits;
    QString instructor;
    QString status;
    QString registreationDeadline;
};

#endif // COURSE_H
