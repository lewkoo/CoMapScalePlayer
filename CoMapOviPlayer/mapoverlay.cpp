
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
}

void MapOverlay::paint(QPainter *painter, const QStyleOptionGraphicsItem* option)
{
    // QGeoBoundingBox box = map->getBoundingBox(); //is passed as a parameter



           QGeoBoundingBox box = map->getBoundingBox(); //is passed as a parameter
           QPointF topLeft = map->coordinateToScreenPosition(box.topLeft());
           QPointF bottomRight = map->coordinateToScreenPosition(box.bottomRight());
           QRectF rect = QRectF(topLeft, bottomRight);
           QColor colour (255,0,0);

           this->boxPen.setColor(colour);
            painter->setPen(boxPen);
            painter->drawRect(rect);


}

