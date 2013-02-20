#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include "qgeomappixmapobject.h"
#include <QPainter>
#include "qgeoboundingbox.h"
#include "geomap.h"
#include "mapoverlay.h"

GeoMap::GeoMap (QGeoMappingManager* mapManager, MappingWidget* mapWidget) :
    QGraphicsGeoMap(mapManager), mapWidget (mapWidget)
{
    panActive = false;
    textPen.setColor(QColor("black"));
    poiMarker = new MapMarker(MapMarker::PeerRedType);
}

GeoMap::~GeoMap()
{
//    for (int i = 0; i < mapOverlays().count(); i++)
//    {
//        QGeoMapOverlay* overlay = this->mapOverlays.at(i);
//        delete overlay;
//    }
}

void GeoMap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    panActive = true;
    event->accept();
}

void GeoMap::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    panActive = false;
    event->accept();
}

void GeoMap::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (panActive)
    {
        QPointF delta = event->lastPos() - event->pos();
        pan(delta.x(), delta.y());
    }

    //QGeoCoordinate coordinate = this->getMapCoordinate();

    //mapWidget->mapPositionChanged(coordinate);
    //updateWedges(coordinate);
    event->accept();
}

void GeoMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *parent)
{
    QList<QGeoMapObject*> mapObjects;
    MapMarker* pixmapObject = NULL;
    QGeoCoordinate coordinate;

    QGraphicsGeoMap::paint(painter, option, parent);
    painter->setPen(this->textPen);
    QPointF offset(-20, 25);

    mapObjects = this->mapObjects();

    for (int i = 0; i < mapObjects.count(); i++)
    {
        QGeoMapObject* mapObject = mapObjects.at(i);
        pixmapObject = dynamic_cast<MapMarker*>(mapObject);

        if (pixmapObject != NULL)
        {
            coordinate = pixmapObject->coordinate();

            if (!pixmapObject->getText().isEmpty() && viewport().contains(pixmapObject->coordinate()))
            {
                QPointF position = this->coordinateToScreenPosition(coordinate) + offset;
                painter->drawText(position, pixmapObject->getText());
            }
        }
    }
}

//QGeoCoordinate GeoMap::getMapCoordinate()
//{
//    QList<QGeoMapObject*> mapObjects;
//    QGeoMapPixmapObject* pixmapObject = NULL;
//    QGeoCoordinate coordinate;

//    mapObjects = this->mapObjects();

//    for (int i = 0; i < mapObjects.count(); i++)
//    {
//        QGeoMapObject* mapObject = mapObjects.at(i);
//        pixmapObject = dynamic_cast<QGeoMapPixmapObject*>(mapObject);

//        if (pixmapObject != NULL )//&& ! viewport().contains(pixmapObject->coordinate()))
//        {
//            coordinate = pixmapObject->coordinate();
//        }
//    }

//    return coordinate;
//}

//void GeoMap::wheelEvent(QGraphicsSceneWheelEvent *event)
//{
//    qreal panx = event->pos().x() - size().width() / 2.0;
//    qreal pany = event->pos().y() - size().height() / 2.0;
//    pan(panx, pany);
//    if (event->delta() > 0)
//    {   // zoom in
//        if (zoomLevel() < maximumZoomLevel())
//        {
//            setZoomLevel(zoomLevel() + 1);
//        }
//    }
//    else
//    {                    // zoom out
//        if (zoomLevel() > minimumZoomLevel())
//        {
//            setZoomLevel(zoomLevel() - 1);
//        }
//    }
//    pan(-panx, -pany);
//    event->accept();
//}

//void GeoMap::updateWedges()
//void GeoMap::updateWedges(QGeoCoordinate coordinate)
//{
//    //QList<QGeoMapObject*> mapObjects;
//    QList<QGeoMapOverlay*> mapOverlays;
//    MapOverlay* wedgeOverlay = NULL;
//    //QGeoMapPixmapObject* pixmapObject = NULL;

//    //mapObjects = this->mapObjects();
//    mapOverlays = this->mapOverlays();

//    if (mapOverlays.count() > 0)
//    {
//        QGeoMapOverlay* overlay = mapOverlays.at(0);
//        wedgeOverlay = dynamic_cast<MapOverlay*>(overlay);
//    }

//    if (wedgeOverlay != NULL)
//    {
//        wedgeOverlay->clearWedges();

//        wedgeOverlay->setWedge(coordinate);
////        for (int i = 0; i < mapObjects.count(); i++)
////        {
////            QGeoMapObject* mapObject = mapObjects.at(i);
////            pixmapObject = dynamic_cast<QGeoMapPixmapObject*>(mapObject);

////            if (pixmapObject != NULL )//&& ! viewport().contains(pixmapObject->coordinate()))
////            {
////                wedgeOverlay->setWedge(pixmapObject);
////            }
////        }
//    }
//}

QPoint GeoMap::coordinateToOffscreenPosition (QGeoCoordinate coordinate)
{
    QPoint pixelPosition;
    QGeoCoordinate originCoordinate = screenPositionToCoordinate(QPointF(0,0));
    QGeoCoordinate differenceFromOrigin = QGeoCoordinate (originCoordinate.latitude() - coordinate.latitude(), coordinate.longitude() - originCoordinate.longitude());

    pixelPosition = QPoint(differenceFromOrigin.longitude() * pixelsPerDegreeLongitude, differenceFromOrigin.latitude() * pixelsPerDegreeLatitude);

    return pixelPosition;
}

void GeoMap::setZoomLevel(qreal zoomLevel)
{
    QGraphicsGeoMap::setZoomLevel(zoomLevel);

    setPixelsPerDegree();
    //updateWedges(this->getMapCoordinate());
}

void GeoMap::setPixelsPerDegree()
{
    QGeoCoordinate topLeft, topRight, bottomLeft;
    double screenWidthDegrees;
    double screenHeightDegrees;

    topLeft = viewport().topLeft();
    topRight = viewport().topRight();
    bottomLeft = viewport().bottomLeft();

    QPointF botRight = coordinateToScreenPosition(viewport().bottomRight());

    screenWidthDegrees = topRight.longitude() - topLeft.longitude();
    screenHeightDegrees = topLeft.latitude() - bottomLeft.latitude();

    pixelsPerDegreeLongitude = this->size().width() / screenWidthDegrees;
    pixelsPerDegreeLatitude = this->size().height() / screenHeightDegrees;
}

void GeoMap::setGeoBoundingBox(QGeoBoundingBox box){
    this->box = box;
}

QGeoBoundingBox GeoMap::getBoundingBox(){
    return this->box;
}

void GeoMap::resetGeoBoundingBox(){
    //this->box = NULL;

}
