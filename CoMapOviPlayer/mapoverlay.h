#ifndef MAPOVERLAY_H
#define MAPOVERLAY_H

#include "qgeomapoverlay.h"
#include <QVector>
#include <QPen>
#include <QColor>

using namespace std;
QTM_USE_NAMESPACE

class GeoMap;

class MapOverlay : public QGeoMapOverlay
{
public:
    explicit MapOverlay(GeoMap* map);

    void paint (QPainter *painter, const QStyleOptionGraphicsItem *option);

    //void setWedge (QGeoMapPixmapObject* mapObject);
    //void setWedge (QGeoCoordinate coordinate);
    //void clearWedges (void);
private:
    GeoMap* map;
    //QVector<Wedge> wedges;

    QPen boxPen;
};

#endif // MAPOVERLAY_H
