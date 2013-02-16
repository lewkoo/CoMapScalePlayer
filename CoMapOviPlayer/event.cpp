#include "event.h"

Event::Event(Event::EventType& type, int userId,  int h, int m, int s, int ms, QGeoCoordinate& pos, QGeoBoundingBox& box)
{
    this->type = type;
    this->time = QTime(h,m,s,ms);
    this->position = pos;
    this->box = box;
}



void Event::setTime(QTime time){
    this->time = time;
}

void Event::setPos(QGeoCoordinate& pos){
    this->position=pos;
}

QGeoCoordinate Event::getPos(){
    return this->position;
}

void Event::setBox(QGeoBoundingBox &box){
    this->box = box;
}

QGeoBoundingBox Event::getBox(){
    return this->box;
}

void Event::printEvent(){

}




