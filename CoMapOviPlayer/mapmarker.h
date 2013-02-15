#ifndef MAPMARKER_H
#define MAPMARKER_H

//#include <QGeoMapPixmapObject>
#include "qgeomappixmapobject.h"

QTM_USE_NAMESPACE

class MapMarker : public QGeoMapPixmapObject
{
    //Q_OBJECT
public:
    enum MarkerType
    {
        PeerType,   //Another user
        PeerOrangeType,
        PeerPurpleType,
        PeerRedType,
        PeerBlueType,
        PoiType,    //A point of interest
        AnchorType, //A visit wear
        AnchorOrangeType,
        AnchorPurpleType,
        AnchorRedType,
        AnchorBlueType,
        HotelType,
        RestaurantType
    };

    explicit MapMarker(MapMarker::MarkerType type, QString text = QString(""));

public:
    inline MapMarker::MarkerType markerType() const { return this->type; }
    inline QString getText() {return text;}

private:
    void setMarkerType (MapMarker::MarkerType type);

private:
    MapMarker::MarkerType  type;
    QString text;
};

#endif // MAPMARKER_H
