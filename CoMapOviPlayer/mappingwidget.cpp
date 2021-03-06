#include <QGraphicsScene>
#include "qgeoboundingbox.h"
#include "qgeocoordinate.h"
#include <QGraphicsView>
#include <qgeoserviceprovider.h>
#include "mappingwidget.h"
#include "geomap.h"
#include "zoombuttonitem.h"
#include "mapoverlay.h"
#include <limits>
#include <QDebug>
#include "tracer.h"


QTM_USE_NAMESPACE

MappingWidget::MappingWidget(QRect &screenSize, QWidget *parent) :
    QWidget(parent), screenSize(screenSize), clientList(NULL)
{
    this->map = NULL;
    this->view = NULL;
    //this->tracer = new Tracer(map);
}

MappingWidget::~MappingWidget()
{
    if (map != NULL)
        delete map;

    if (view != NULL)
        delete view;
}

void MappingWidget::initialize(QGeoMappingManager* mapManager)
{
    //QRect viewportRect = QRect(0, 0, this->screenSize.width() -200, this->screenSize.height() - 150);
    //this->setMinimumSize(viewportRect.width(), viewportRect.height());

    this->setMaximumSize(this->screenSize.width(), this->screenSize.height());
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QRect viewportRect = this->rect();

    map = new GeoMap (mapManager, this);

    QGraphicsScene* scene = new QGraphicsScene;
    scene->addItem(map);

    //map->resize(viewportRect.width(), viewportRect.height());
    map->setMaximumSize(this->screenSize.width(), this->screenSize.height());
    map->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scene->setSceneRect(viewportRect);
    map->setCenter(QGeoCoordinate(48.854716, 2.346611));
    map->setZoomLevel(12);




    MapOverlay* overlayRed = new MapOverlay(map);
    map->addMapOverlay(overlayRed);

    tracer = new Tracer(map);
    map->addMapOverlay(tracer);

    //MapOverlay* overlayBlue = new MapOverlay(map);
   // map->addMapOverlay(overlayBlue);


    view = new QGraphicsView(scene, this);
    //view->resize(viewportRect.width(), viewportRect.height());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    zoomButton = new ZoomButtonItem(map);
    zoomButton->setRect(width() - 50, 0, 50, 100);
    scene->addItem(zoomButton);

    view->setVisible (true);
    view->setInteractive (true);
}

void MappingWidget::resetTracer(){
    map->removeMapOverlay(tracer);
    tracer = new Tracer(map);
    map->addMapOverlay(tracer);
}

void MappingWidget::mapPositionChanged(QGeoCoordinate coordinate)
{
    map->setCenter(coordinate);
}

void MappingWidget::mapScaleChanged(int scale){
    map->setZoomLevel(scale);
}

void MappingWidget::mapAnchorAdded(QGeoCoordinate pos, int userId){
    addAnchor(pos,userId);
}

void MappingWidget::mapBoxChanged(QGeoBoundingBox box, int userId){
    if(userId == 0){
        map->setGeoBoundingBoxU1(box);
    }else if(userId == 1){
        map->setGeoBoundingBoxU2(box);
    }else{
        qDebug() << "Invalid user id passed to MappingWidget";
    }
}

void MappingWidget::userIdChanged(int userId){
    map->setUserId(userId);
}

void MappingWidget::setClientList (QList<ClientConnection*>* list)
{
    this->clientList = list;
}

void MappingWidget::paintEvent(QPaintEvent *)
{
    this->map->update();
}

void MappingWidget::resizeEvent ( QResizeEvent * event )
{
    QRect viewportRect = this->rect();
    map->resize(viewportRect.width(), viewportRect.height());
    view->scene()->setSceneRect(viewportRect);
    view->resize(viewportRect.width(), viewportRect.height());
    zoomButton->setRect(map->rect().width() - 50, 0, 50, 100);
}

MapMarker* MappingWidget::addMapMarker(MapMarker::MarkerType markerType, QGeoCoordinate location)
{
    return addMapMarker(markerType, location, "");
}

MapMarker* MappingWidget::addMapMarker(MapMarker::MarkerType markerType, QGeoCoordinate location, QString text)
{
    MapMarker* marker = new MapMarker(markerType, text);
    marker->setCoordinate(location);
    map->addMapObject (marker);

    //Map takes ownership of marker, but the peer state needs a handle for position updates.
    return marker;
}

void MappingWidget::removeMapMarker(MapMarker *marker)
{
    map->removeMapObject(marker);
}

//TODO: Look only for anchors of a specific colour.
qreal MappingWidget::getClosestVw(QGeoCoordinate location)
{
    QList<QGeoMapObject*> mapObjects;
    qreal shortestDistance = numeric_limits<double>::max();
    MapMarker* mapMarker;

    mapObjects = this->map->mapObjects();

    for (int i = 0; i < mapObjects.count(); i++)
    {
        QGeoMapObject* mapObject = mapObjects.at(i);
        mapMarker = dynamic_cast<MapMarker*>(mapObject);

        if (mapMarker != NULL)
        {
            if (mapMarker->markerType() == MapMarker::AnchorType ||
                    mapMarker->markerType() == MapMarker::AnchorOrangeType ||
                    mapMarker->markerType() == MapMarker::AnchorPurpleType ||
                    mapMarker->markerType() == MapMarker::AnchorRedType ||
                    mapMarker->markerType() == MapMarker::AnchorBlueType)
            {
                QGeoCoordinate mapObjectLocation = mapMarker->coordinate();
                qreal distance = location.distanceTo(mapObjectLocation);

                if (distance < shortestDistance)
                {
                    shortestDistance = distance;
                }
            }
        }
    }

    return shortestDistance;
}

void MappingWidget::addIcons(QStringList iconList)
{
    foreach (QString line, iconList)
    {
        addIcon(line);
    }
}

void MappingWidget::addIcon(QString lineItem)
{
    try
    {
        QStringList elements = lineItem.split(',');
        QString type = elements.at(0);
        double latitude = elements.at(1).toDouble();
        double longitude = elements.at(2).toDouble();
        QString text = "";

        if (elements.count() >= 3)
        {
            text = elements.at(3);
        }

        QGeoCoordinate coordinate(latitude, longitude);
        MapMarker::MarkerType markerType;

        if (type.compare("hot") == 0)
        {
            markerType = MapMarker::HotelType;
        }
        else if (type.compare("res") == 0)
        {
            markerType = MapMarker::RestaurantType;
        }
        else
        {
            qDebug() << "Unknown map icon type: " + type;
        }

        this->addMapMarker(markerType, coordinate, text);
    }
    catch (...)
    {
        qDebug() << "Error parsing lineItem in method addIcon: " + lineItem;
    }
}

void MappingWidget::addAnchor(QGeoCoordinate pos, int userId){
    MapMarker::MarkerType markerType;
    QString text = "";

    if (userId == 0)
    {
        markerType = MapMarker::AnchorRedType;
    }
    else if (userId == 1)
    {
        markerType = MapMarker::AnchorBlueType;
    }
    else
    {
        qDebug() << "Unknown anchor user id type: ";
    }

    this->addMapMarker(markerType, pos, text);
}


QList<QGeoMapObject*> MappingWidget::getMapObjects()
{
    QList<QGeoMapObject*> objectList = map->mapObjects();
    return objectList;
}

void MappingWidget::clearMapObjects()
{
    map->resetGeoBoundingBox();
    resetTracer();
    //map->update();
    map->clearMapObjects();
}

void MappingWidget::turnOffRedTracer(){
    map->setRedTracerSwitch(false);
}

void MappingWidget::turnOnRedTracer(){
     map->setRedTracerSwitch(true);
}

void MappingWidget::turnOffBlueTracer(){
    map->setBlueTracerSwitch(false);
}

void MappingWidget::turnOnBlueTracer(){
    map->setBlueTracerSwitch(true);
}



