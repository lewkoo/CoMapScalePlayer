#ifndef GEOMAP_H
#define GEOMAP_H

#include <QPen>
#include <QColor>
#include <qgraphicsgeomap.h>
#include "mappingwidget.h"
#include <qgeoboundingbox.h>

QTM_USE_NAMESPACE

class GeoMap : public QGraphicsGeoMap
{
    Q_OBJECT

public:
    GeoMap (QGeoMappingManager* mapManager, MappingWidget* mapWidget);
    ~GeoMap ();

//    void updateWedges(void);
    //void updateWedges(QGeoCoordinate coordinate);
    QPoint coordinateToOffscreenPosition (QGeoCoordinate coordinate);
    void setZoomLevel(qreal zoomLevel); //Shadows parent method.
    void setPixelsPerDegree (void);

    void resetGeoBoundingBox();
    void setGeoBoundingBoxU1(QGeoBoundingBox box);
    void setGeoBoundingBoxU2(QGeoBoundingBox box);
    QGeoBoundingBox getBoundingBoxU1();
    QGeoBoundingBox getBoundingBoxU2();

    void setRedTracerSwitch(bool value);
    void setBlueTracerSwitch(bool value);

    int getUserId();
    void setUserId(int userId);

    inline MappingWidget* getMapWidget() {return mapWidget;}

    MapMarker* poiMarker;//make private, add accessors
    MapMarker* poiMarker2;

    bool redTracer; //make private add accessors
    bool blueTracer;


private:
    //Events
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    //void wheelEvent(QGraphicsSceneWheelEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *parent);

private:
    MappingWidget* mapWidget;
    bool panActive;

    double pixelsPerDegreeLatitude;
    double pixelsPerDegreeLongitude;
    QPen textPen;
    //QGeoCoordinate getMapCoordinate();
    QGeoBoundingBox boxU1;
    QGeoBoundingBox boxU2;

    int userId;
};

#endif // GEOMAP_H
