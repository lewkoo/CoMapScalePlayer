#ifndef GEOMAP_H
#define GEOMAP_H

#include <QPen>
#include <QColor>
#include <qgraphicsgeomap.h>
#include "mappingwidget.h"

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


    inline MappingWidget* getMapWidget() {return mapWidget;}

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
};

#endif // GEOMAP_H
