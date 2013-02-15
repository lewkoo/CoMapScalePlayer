#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <QQueue>
#include <event.h>

class EventManager
{
public:

    EventManager();

    void addEvent (Event::EventType type, int userId, QString params);

private:
    void addEvent (Event* event);
    QQueue<Event*> eventQueue;
};

#endif // EVENTMANAGER_H
