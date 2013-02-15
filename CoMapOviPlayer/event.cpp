#include "event.h"

Event::Event(Event::EventType& type, int userId,  int h, int m, int s, int ms, QGeoCoordinate& pos, QGeoBoundingBox& box)
{
    this->type = type;
    this->time = time;
    this->position = pos;
    this->box = box;
}
