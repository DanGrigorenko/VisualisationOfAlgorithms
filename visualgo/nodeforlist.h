#ifndef NODEFORLIST_H
#define NODEFORLIST_H


#include <QGraphicsItem>
#include <QList>

class EdgeForList;
class ListWidget;

class NodeForList : public QGraphicsItem
{
public:
    int m_node_id = 0;
    bool isChoosed = false;
    bool desired = false;
    bool insertAndRemove = false;
    NodeForList(ListWidget *graphWidget);

    void addEdge(EdgeForList *edge);
    QList<EdgeForList *> edges() const;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    bool advancePosition();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QList<EdgeForList *> edgeList;
    QPointF newPos;
    ListWidget *graph;
    NodeForList *arr;
};
#endif // NODEFORLIST_H
