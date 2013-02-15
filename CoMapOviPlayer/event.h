#ifndef EVENT_H
#define EVENT_H

#include <QTime>
#include <qgeocoordinate.h>
#include <qgeoboundingbox.h>

QTM_USE_NAMESPACE

class Event
{
public:

    enum EventType
    {
        NavEvent,
        AnchorEvent
    };

    Event(Event::EventType& type, int userId, int h, int m, int s, int ms, QGeoCoordinate& pos, QGeoBoundingBox& box);

    inline QTime getTime() const {return time;}
    //inline void setTime(QTime time) {this->time = time;}
   // inline void setPos(QGeoCoordinate pos) {this->position = pos;}

private:
    Event::EventType type;
    int userId;
    QTime time;
    QGeoCoordinate position;
    QGeoBoundingBox box;
};

#endif // EVENT_H
