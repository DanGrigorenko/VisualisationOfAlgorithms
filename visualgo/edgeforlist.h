#ifndef EDGEFORLIST_H
#define EDGEFORLIST_H


#include <QGraphicsItem>

class NodeForList;

//! [0]
class EdgeForList : public QGraphicsItem
{
public:
    EdgeForList(NodeForList *sourceNode, NodeForList *destNode);
    NodeForList *sourceNode() const;
    NodeForList *destNode() const;
    bool isChoosed = false;

    void adjust();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    NodeForList *source, *dest;
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize = 10;
};
//! [0]

#endif // EDGEFORLIST_H
