#ifndef ZOOMBUTTONITEM_H
#define ZOOMBUTTONITEM_H

#include <QGraphicsRectItem>

class ZoomButtonItemPimpl;
class QGraphicsSceneMouseEvent;
class GeoMap;

class ZoomButtonItem : public QGraphicsRectItem
{
public:
    explicit ZoomButtonItem(GeoMap* map);

    void setRect (qreal x, qreal y, qreal width, qreal height);


protected:
    void mousePressEvent (QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


private:
    bool isTopHalf (const QPointF &point);
    bool isBottomHalf (const QPointF &point);

private:
    GeoMap* map;

    QGraphicsSimpleTextItem *plusText;
    QGraphicsSimpleTextItem *minusText;

    bool pressedOverTopHalf;
    bool pressedOverBottomHalf;
};

#endif // ZOOMBUTTONITEM_H
