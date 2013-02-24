#ifndef MAPPINGWIDGET_H
#define MAPPINGWIDGET_H

#include <QWidget>
//#include <QGeoMappingManager>
#include "qgeomappingmanager.h"
//#include "clientstate.h"
#include "mapmarker.h"
#include "tracer.h"



QTM_USE_NAMESPACE

class GeoMap;
class QGraphicsView;
class ZoomButtonItem;
class ClientConnection;

class MappingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MappingWidget(QRect &screenSize, QWidget *parent = 0);
    ~MappingWidget ();

    //void resizeEvent(QResizeEvent *event);

    void mapPositionChanged(QGeoCoordinate coordinate);
    void mapScaleChanged(int scale);
    void mapBoxChanged(QGeoBoundingBox box, int userId);
    void mapAnchorAdded(QGeoCoordinate pos, int userId);
    void userIdChanged(int userId);
    void setClientList (QList<ClientConnection*>* list);

    inline QList<ClientConnection*>* getClientList() {return clientList;}

    MapMarker* addMapMarker(MapMarker::MarkerType markerType, QGeoCoordinate location);
    MapMarker* addMapMarker(MapMarker::MarkerType markerType, QGeoCoordinate location, QString text);
    qreal getClosestVw(QGeoCoordinate location);
    void removeMapMarker(MapMarker* marker);
    void clearMapObjects();
    QList<QGeoMapObject*> getMapObjects();

    void addIcons(QStringList iconList);
    void addIcon(QString lineItem);

    void addAnchor(QGeoCoordinate pos, int userId);

    void resetTracer();

    void turnOffRedTracer();
    void turnOnRedTracer();

    void turnOffBlueTracer();
    void turnOnBlueTracer();


protected: //events
    void paintEvent(QPaintEvent *);
    void resizeEvent ( QResizeEvent * event );

signals:

public slots:
    void initialize (QGeoMappingManager* mapManager);

private:
    const QRect screenSize;
    Tracer* tracer;
    GeoMap* map;
    QGraphicsView* view;
    ZoomButtonItem* zoomButton;
    QList<ClientConnection*>* clientList;
};

#endif // MAPPINGWIDGET_H
