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
    Event(Event::EventType& type, int userId,  int h, int m, int s, int ms, QGeoCoordinate& pos, QGeoBoundingBox& box, int scale);
    ~Event();

    inline EventType getType() const {return type;}

    inline QTime getTime() const {return time;}
    inline void setTime(QTime time);

    inline void setPos(QGeoCoordinate& pos);
    inline QGeoCoordinate getPos() const {return position;}

    inline void setBox(QGeoBoundingBox& box);
    inline QGeoBoundingBox getBox() const {return box;}

    inline int getScale() const {return scale;}

    inline int getUserId() const {return userId;}


private:
    Event::EventType type;
    int userId;
    QTime time;
    QGeoCoordinate position;
    QGeoBoundingBox box;

    int scale; //???
};

#endif // EVENT_H
