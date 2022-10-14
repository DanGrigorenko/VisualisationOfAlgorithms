#ifndef NODEFORHASH_H
#define NODEFORHASH_H


#include <QGraphicsItem>
#include <QList>

class HashWidget;

class NodeForHash : public QGraphicsItem
{
public:
    QString m_node_id = "";
    bool isChoosed = false;
    bool desired = false;
    bool insertAndRemove = false;
    NodeForHash(HashWidget *graphWidget);

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
    QPointF newPos;
    HashWidget *graph;
    NodeForHash *arr;
};
#endif // NODEFORHASH_H
