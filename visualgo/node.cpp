#include "edge.h"
#include "node.h"
#include "graphwidget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

Node::Node(GraphWidget *graphWidget)
    : graph(graphWidget)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QVector<Edge *> Node::edges() const
{
    return edgeList;
}

bool Node::advancePosition()
{
    if (newPos == pos())
        return false;

    setPos(newPos);
    return true;
}

QRectF Node::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);

    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);

        if (is_work) {
            gradient.setColorAt(1, QColor(Qt::red).lighter(120));
            gradient.setColorAt(0, QColor(Qt::red).lighter(120));
        }
        else if (!is_choosed) {
            gradient.setColorAt(0, Qt::yellow);
            gradient.setColorAt(1, Qt::darkYellow);
        }
        else
        {
            gradient.setColorAt(1, QColor(Qt::green).lighter(120));
            gradient.setColorAt(0, QColor(Qt::green).lighter(120));
        }
    } else {
        if (is_work) {
            gradient.setColorAt(1, QColor(Qt::red).lighter(120));
            gradient.setColorAt(0, QColor(Qt::red).lighter(120));
        }
        else if (!is_choosed) {
            gradient.setColorAt(0, Qt::yellow);
            gradient.setColorAt(1, Qt::darkYellow);
        }
        else
        {
            gradient.setColorAt(1, QColor(Qt::green).lighter(120));
            gradient.setColorAt(0, QColor(Qt::green).lighter(120));
        }
    }


    painter->setBrush(gradient);

    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);
    painter->drawText(QPointF(-4,4),QString::number(m_node_id));
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        for (Edge *edge : qAsConst(edgeList))
            edge->adjust();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    graph->choosenode(m_node_id);
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

