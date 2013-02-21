#include "event.h"

Event::Event(Event::EventType& type, int userId,  int h, int m, int s, int ms, QGeoCoordinate& pos, QGeoBoundingBox& box)
{
    this->type = type;
    this->userId = userId;
    this->time = QTime(h,m,s,ms);
    this->position = pos;
    this->box = box;
}

Event::Event(Event::EventType& type, int userId,  int h, int m, int s, int ms, QGeoCoordinate& pos, QGeoBoundingBox& box, int scale)
{
    this->type = type;
    this->userId = userId;
    this->time = QTime(h,m,s,ms);
    this->position = pos;
    this->box = box;
    this->scale = scale;
}

Event::~Event(){
    delete &type;
    delete &time;
    delete &position;
    delete &box;
}


void Event::setTime(QTime time){
    this->time = time;
}

void Event::setPos(QGeoCoordinate& pos){
    this->position = pos;
}



void Event::setBox(QGeoBoundingBox &box){
    this->box = box;
}





