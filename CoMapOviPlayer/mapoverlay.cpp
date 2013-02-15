
#include "qgeomappixmapobject.h"
#include <qgeoboundingbox.h>
#include <QRect>
#include <QPainter>
#include "mapoverlay.h"
#include "geomap.h"

MapOverlay::MapOverlay(GeoMap* map) :
    QGeoMapOverlay()
{
    this->map = map;
    this->boxPen.setWidth(3);
}

void MapOverlay::paint(QPainter *painter, const QStyleOptionGraphicsItem *option)
{
//    QList<ClientConnection*>* clientList = map->getMapWidget()->getClientList();

//    if (clientList != NULL)
//    {
//        for (int i = 0; i < clientList->size(); i++)
//        {
//            QGeoBoundingBox box = clientState->getLastBox();
//            QPointF topLeft = map->coordinateToScreenPosition(box.topLeft());
//            QPointF bottomRight = map->coordinateToScreenPosition(box.bottomRight());
//            QRectF rect = QRectF(topLeft, bottomRight);
//            QColor colour = clientState->getColour();

//            this->boxPen.setColor(colour);
//            painter->setPen(boxPen);
//            painter->drawRect(rect);
//        }
//    }
}

