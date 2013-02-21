
#include "qgeomappixmapobject.h"
#include <qgeoboundingbox.h>
#include <QRect>
#include <QPainter>
#include "mapoverlay.h"
#include "geomap.h"
#include <QDebug>

MapOverlay::MapOverlay(GeoMap* map) :
    QGeoMapOverlay()
{
    this->map = map;
    this->boxPen.setWidth(3);
    this->userId = -1;//default
}

void MapOverlay::setUserId(int userId){
    this->userId = userId;
}

void MapOverlay::paint(QPainter *painter, const QStyleOptionGraphicsItem* option)
{
    // QGeoBoundingBox box = map->getBoundingBox(); //is passed as a parameter



           QGeoBoundingBox boxU1 = map->getBoundingBoxU1(); //is passed as a parameter
           QGeoBoundingBox boxU2 = map->getBoundingBoxU2(); //is passed as a parameter
           userId = map->getUserId();//redundant


           QPointF topLeft = map->coordinateToScreenPosition(boxU1.topLeft());
           QPointF bottomRight = map->coordinateToScreenPosition(boxU1.bottomRight());
           QRectF rect = QRectF(topLeft, bottomRight);
           QColor colour (255,0,0);
           this->boxPen.setColor(colour);
           painter->setPen(boxPen);
           painter->drawRect(rect);



           topLeft = map->coordinateToScreenPosition(boxU2.topLeft());
           bottomRight = map->coordinateToScreenPosition(boxU2.bottomRight());
           rect = QRectF(topLeft, bottomRight);
           colour.setRgb(0,0,255);
           this->boxPen.setColor(colour);
           painter->setPen(boxPen);
           painter->drawRect(rect);





            map->poiMarker->setCoordinate(boxU1.center());
            map->addMapObject (map->poiMarker);



}

