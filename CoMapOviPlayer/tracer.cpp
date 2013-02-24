#include "qgeomappixmapobject.h"
#include <qgeoboundingbox.h>
#include <QRect>
#include <QPainter>
#include "tracer.h"
#include "geomap.h"
#include <QDebug>

Tracer::Tracer(GeoMap* map) :
    QGeoMapOverlay()
{

    //QPointF currPoint();
    //QPointF newPoint();
    QList<QGeoCoordinate> lineListU1;
    QList<QGeoCoordinate> lineListU2;
    this->map = map;
    this->boxPen.setWidth(3);
    this->userId = -1;//default
}

void Tracer::setUserId(int userId){
    this->userId = userId;
}

void Tracer::paint(QPainter *painter, const QStyleOptionGraphicsItem* option)
{


       QGeoBoundingBox boxU1 = map->getBoundingBoxU1(); //is passed as a parameter
       if(map->redTracer == true){
       updateU1(boxU1, painter, option);
       }
       QGeoBoundingBox boxU2 = map->getBoundingBoxU2();
       if(map->blueTracer == true){
       updateU2(boxU2, painter, option);
       }

}

void Tracer::updateU1(QGeoBoundingBox boxU1, QPainter *painter, const QStyleOptionGraphicsItem* option){


    if(currPointU1.isNull() && boxU1.isEmpty() == false){
        //currPoint.setX(boxU1.center());
        lineListU1.append(boxU1.center());
        currPointU1 = map->coordinateToScreenPosition(boxU1.center());

    }else if(newPointU1.isNull() && boxU1.isEmpty() == false){
     lineListU1.append(boxU1.center());

     //get two points
     //currPoint = map->coordinateToScreenPosition(boxU1.center());
     newPointU1 = map->coordinateToScreenPosition(boxU1.center());
     QLineF line = QLineF(currPointU1, newPointU1);
     QColor colour (255,0,0);
     this->boxPen.setColor(colour);
     painter->setPen(boxPen);
     painter->drawLine(line);
     currPointU1 = newPointU1;


    }else if(boxU1.isEmpty() == false && lineListU1.length() >= 2){
        //draw a line between currPoint and new point.
        // set curr point to new point
        lineListU1.append(boxU1.center());


        currPointU1 = map->coordinateToScreenPosition(lineListU1.at(0));
        newPointU1 = map->coordinateToScreenPosition(lineListU1.at(1));

        QLineF line = QLineF(currPointU1, newPointU1);
        QColor colour (255,0,0);
        this->boxPen.setColor(colour);
        painter->setPen(boxPen);
        painter->drawLine(line);
        currPointU1 = newPointU1;

        int counter = 2;
        while (counter < lineListU1.length() && lineListU1.length() > 2){
            newPointU1 = map->coordinateToScreenPosition(lineListU1.at(counter));

            QLineF line = QLineF(currPointU1, newPointU1);
            QColor colour (255,0,0);
            this->boxPen.setColor(colour);
            painter->setPen(boxPen);
            painter->drawLine(line);
            currPointU1 = newPointU1;
            counter++;


        }




    }
}

void Tracer::updateU2(QGeoBoundingBox boxU2, QPainter *painter, const QStyleOptionGraphicsItem* option){

    if(currPointU2.isNull() && boxU2.isEmpty() == false){
        //currPointU2.setX(boxU2.center());
        lineListU2.append(boxU2.center());
        currPointU2 = map->coordinateToScreenPosition(boxU2.center());

    }else if(newPointU2.isNull() && boxU2.isEmpty() == false){
     lineListU2.append(boxU2.center());

     //get two points
     //currPointU2 = map->coordinateToScreenPosition(boxU2.center());
     newPointU2 = map->coordinateToScreenPosition(boxU2.center());
     QLineF line = QLineF(currPointU2, newPointU2);
     QColor colour (255,0,0);
     this->boxPen.setColor(colour);
     painter->setPen(boxPen);
     painter->drawLine(line);
     currPointU2 = newPointU2;


    }else if(boxU2.isEmpty() == false){ //removed :
        //draw a line between currPointU2 and new point.
        // set curr point to new point
        lineListU2.append(boxU2.center());


        currPointU2 = map->coordinateToScreenPosition(lineListU2.at(0));
        newPointU2 = map->coordinateToScreenPosition(lineListU2.at(1));

        QLineF line = QLineF(currPointU2, newPointU2);
        QColor colour (0,0,255);
        this->boxPen.setColor(colour);
        painter->setPen(boxPen);
        painter->drawLine(line);
        currPointU2 = newPointU2;

        int counter = 2;
        while (counter < lineListU2.length() && lineListU2.length() > 2){
            newPointU2 = map->coordinateToScreenPosition(lineListU2.at(counter));

            QLineF line = QLineF(currPointU2, newPointU2);
            QColor colour (0,0,255);
            this->boxPen.setColor(colour);
            painter->setPen(boxPen);
            painter->drawLine(line);
            currPointU2 = newPointU2;
            counter++;


        }




    }

}
