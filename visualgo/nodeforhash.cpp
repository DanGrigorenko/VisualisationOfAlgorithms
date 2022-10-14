#include "nodeforhash.h"
#include "hashwidget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

NodeForHash::NodeForHash(HashWidget *HashWidget)
    : graph(HashWidget)
{
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}



bool NodeForHash::advancePosition()
{
    if (newPos == pos())
        return false;

    setPos(newPos);
    return true;
}

QRectF NodeForHash::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -20 - adjust, -20 - adjust, 35 + adjust, 35 + adjust);
}

QPainterPath NodeForHash::shape() const
{
    QPainterPath path;
    path.addEllipse(-20, -20, 35, 35);
    return path;
}

void NodeForHash::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);

    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);

        if (desired == true)
            gradient.setColorAt(1, Qt::green);
        else if (insertAndRemove)
            gradient.setColorAt(1, Qt::green);
        else if (!isChoosed)
            gradient.setColorAt(1, Qt::white);
        else
            gradient.setColorAt(1, Qt::red);
    } else {
        if (desired == true)
            gradient.setColorAt(1, Qt::green);
        else if (insertAndRemove)
            gradient.setColorAt(1, Qt::green);
        else if (!isChoosed)
            gradient.setColorAt(1, Qt::white);
        else
            gradient.setColorAt(1, Qt::red);
    }


    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 3));
    painter->drawEllipse(-20, -20, 35, 35);
    painter->drawText(QPointF(-12,4),(m_node_id));
}

QVariant NodeForHash::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void NodeForHash::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void NodeForHash::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

