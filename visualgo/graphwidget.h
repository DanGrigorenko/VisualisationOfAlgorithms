#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QLineEdit>

class Node;
class Edge;
class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = nullptr);
    Node *arr[9];
    Edge *edge[100000];
    int firstnode = 0;
    bool is_waitlink = false;

public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();
    void Node_ON_Scene(int n);
    void RemoveEdge();
    void choosenode(int node_id);
    void Deikstra();
    void Clear();

protected:
    void keyPressEvent(QKeyEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void scaleView(qreal scaleFactor);

private:
    int nn = 3;
    QGraphicsTextItem * field;
    QLineEdit *le1 = new QLineEdit();
};

#endif // GRAPHWIDGET_H
