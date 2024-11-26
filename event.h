#ifndef EVENT_H
#define EVENT_H

#include "QtCore/qstring.h"
class Event
{
public:
    Event();
    QString getEventId() const;
    void setEventId(const QString &newEventId);

    QString getTitle() const;
    void setTitle(const QString &newTitle);

    QString getDescription() const;
    void setDescription(const QString &newDescription);

    QString getSpeaker() const;
    void setSpeaker(const QString &newSpeaker);

    QString getSchedule() const;
    void setSchedule(const QString &newSchedule);

private:
    QString eventId;
    QString title;
    QString description;
    QString speaker;
    QString schedule;
};

#endif // EVENT_H
