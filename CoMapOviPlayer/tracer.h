#ifndef TRACER_H
#define TRACER_H

#include "qgeomapoverlay.h"
#include <QVector>
#include <QPen>
#include <QColor>
#include <QList>
#include <qgeocoordinate.h>
#include <qgeoboundingbox.h>

using namespace std;
QTM_USE_NAMESPACE

class GeoMap;

class Tracer : public QGeoMapOverlay
{
public:
    explicit Tracer(GeoMap* map);

    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option);

    void setUserId(int userId);
    void updateU1(QGeoBoundingBox boxU1, QPainter *painter, const QStyleOptionGraphicsItem* option);
    void updateU2(QGeoBoundingBox boxU2, QPainter *painter, const QStyleOptionGraphicsItem* option);


    //void setWedge (QGeoMapPixmapObject* mapObject);
    //void setWedge (QGeoCoordinate coordinate);
    //void clearWedges (void);
private:
    GeoMap* map;
    //QVector<Wedge> wedges;
    QList<QGeoCoordinate> lineListU1;
    QList<QGeoCoordinate> lineListU2;
    QPointF currPointU1;
    QPointF newPointU1;
    QPointF currPointU2;
    QPointF newPointU2;
    QPen boxPen;
    int userId;
};

#endif // TRACER_H
