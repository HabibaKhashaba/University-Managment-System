#include "event.h"

Event::Event() {}

QString Event::getEventId() const
{
    return eventId;
}

void Event::setEventId(const QString &newEventId)
{
    eventId = newEventId;
}

QString Event::getTitle() const
{
    return title;
}

void Event::setTitle(const QString &newTitle)
{
    title = newTitle;
}

QString Event::getDescription() const
{
    return description;
}

void Event::setDescription(const QString &newDescription)
{
    description = newDescription;
}

QString Event::getSpeaker() const
{
    return speaker;
}

void Event::setSpeaker(const QString &newSpeaker)
{
    speaker = newSpeaker;
}

QString Event::getSchedule() const
{
    return schedule;
}

void Event::setSchedule(const QString &newSchedule)
{
    schedule = newSchedule;
}
