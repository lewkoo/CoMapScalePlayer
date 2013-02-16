#include "eventmanager.h"
#include <QDebug>
#include <QStringList>
#include <qgeocoordinate.h>
#include <qgeoboundingbox.h>

EventManager::EventManager()
{
}

void EventManager::addEvent(Event::EventType type, int userId, QString params)
{
    QStringList elements = params.split(';');
    QStringList timeParts = elements[0].split(':');
    QStringList secondParts = timeParts[2].split('.');
    int h, m, s, ms;

    h = timeParts[0].toInt();
    m = timeParts[1].toInt();
    s = secondParts[0].toInt();
    ms = secondParts[1].toInt();
    QGeoCoordinate pos (elements[1].toFloat(), elements[2].toFloat());
    QGeoCoordinate topLeft (elements[3].toFloat(), elements[4].toFloat());
    QGeoCoordinate botRight (elements[5].toFloat(), elements[6].toFloat());
    QGeoBoundingBox box (topLeft, botRight);
    Event* newEvent = new Event(type, userId, h, m, s, ms, pos, box);

    addEvent(newEvent);
}

void EventManager::addEvent(Event* event)
{
    bool eventInserted = false;
    for (int i = 0; i < eventQueue.count(); i++)
    {
        const Event* otherEvent = eventQueue.at(i);

        if (otherEvent->getTime() > event->getTime())
        {
            eventQueue.insert(i, event);
            eventInserted = true;
        }
    }

    if (!eventInserted)
    {
        eventQueue.append(event);
    }
}

Event* EventManager::getNextEvent(){
    return eventQueue.dequeue();
}

bool EventManager::isInicialized(){
    if(eventQueue.isEmpty() == true){
        return false;
    }else{
        return true;
    }
}
