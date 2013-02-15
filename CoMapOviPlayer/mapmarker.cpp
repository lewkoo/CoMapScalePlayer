#include "mapmarker.h"

MapMarker::MapMarker(MapMarker::MarkerType type, QString text)
{
    setMarkerType (type);

    this->text = text;
}

void MapMarker::setMarkerType (MapMarker::MarkerType type)
{
    QString filename;
    QPoint offset;
    int scale;

    this->type = type;

    switch (this->type)
    {
    case PeerType:
        filename = ":/Icons/peer";
        offset = QPoint (-23, -14);
        scale = 40;
        break;
    case PeerOrangeType:
        filename = ":/Icons/peerOrange";
        offset = QPoint (-23, -14);
        scale = 40;
        this->setZValue(20);
        break;
    case PeerPurpleType:
        filename = ":/Icons/peerPurple";
        offset = QPoint (-23, -14);
        scale = 40;
        this->setZValue(20);
        break;
    case PeerRedType:
        filename = ":/Icons/peerRed";
        offset = QPoint (-23, -14);
        scale = 40;
        this->setZValue(20);
        break;
    case PeerBlueType:
        filename = ":/Icons/peerBlue";
        offset = QPoint (-23, -14);
        scale = 40;
        this->setZValue(20);
        break;
    case PoiType:
        filename = ":/Icons/poi";
        offset = QPoint (-23, -22);
        scale = 40;
        break;
    case AnchorType:
        filename = ":/Icons/anchor";
        offset = QPoint (-20, -25);
        scale = 40;
        break;
    case AnchorOrangeType:
        filename = ":/Icons/anchorOrange";
        offset = QPoint (-20, -25);
        scale = 40;
        break;
    case AnchorPurpleType:
        filename = ":/Icons/anchorPurple";
        offset = QPoint (-20, -25);
        scale = 40;
        break;
    case AnchorRedType:
        filename = ":/Icons/anchorRed";
        offset = QPoint (-20, -25);
        scale = 40;
        break;
    case AnchorBlueType:
        filename = ":/Icons/anchorBlue";
        offset = QPoint (-20, -25);
        scale = 40;
        break;
    case HotelType:
        filename = ":/Icons/hotel";
        offset = QPoint (-46, -24);
        scale = 40;
        this->setZValue(10);
        break;
    case RestaurantType:
        filename = ":/Icons/restaurant";
        offset = QPoint (-38, -27);
        scale = 40;
        this->setZValue(10);
        break;
    }

    //Correct the offset
    float scaleRatio = ((float)-scale) / (2 * offset.x());
    offset.setX(offset.x() * scaleRatio);
    offset.setY(offset.y() * scaleRatio);

    setOffset (offset);
    setPixmap (QPixmap(filename).scaledToWidth(scale, Qt::SmoothTransformation));
}
