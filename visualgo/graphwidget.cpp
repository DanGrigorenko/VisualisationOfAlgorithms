#include "graphwidget.h"
#include "edge.h"
#include "node.h"
#include <QMessageBox>
#include <math.h>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QPainter>

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    scale(qreal(0.8), qreal(0.8));

    QGraphicsScene *scene = new QGraphicsScene(this);;
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-300, -300, 600, 600);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setMinimumSize(400, 400);

    le1->setGeometry(-299, -299, 150, 30);
    le1->setPlaceholderText("Введите графу: '1,3'");
    scene->addWidget(le1);

    for (int i = 0; i < 100000; i++) {
        edge[i] = NULL;
    }

    Node_ON_Scene(nn);
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Plus:
            zoomIn();
            break;
        case Qt::Key_Minus:
            zoomOut();
            break;
        case Qt::Key_Space:
            shuffle();
            break;
        case Qt::Key_F10:
            Deikstra();
            break;
        case Qt::Key_F11:
            RemoveEdge();
            break;
        default:
        QGraphicsView::keyPressEvent(event);
    }
}

#if QT_CONFIG(wheelevent)
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow(2., -event->angleDelta().y() / 240.0));
}
#endif
void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
    painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
    painter->fillRect(bottomShadow, Qt::darkGray);

    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->setPen(Qt::black);
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::shuffle()
{
    Clear();
    const QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + QRandomGenerator::global()->bounded(300), -150 + QRandomGenerator::global()->bounded(300));
    }
}

void GraphWidget::Node_ON_Scene(int nn)
{
    for (int i = 0; i < nn; i++) {
        arr[i] = new Node(this);
    }

    for (int i = 0; i < nn; i++) {
        arr[i]->m_node_id = i+1;
        scene()->addItem(arr[i]);
    }

    int num = -50;
    int num2 = -50;
    int count = 0;
    for (int i = 0; i < nn; i++) {
        count++;
        if (count == 4) {
            num2+=50;
            num = -50;
        }
        if (count == 5) {
            num2 = 0;
            num = 0;
        }
        if (count == 6) {
            num2 = 0;
            num = 50;
        }
        if (count == 7) {
            num2 = 50;
            num = -50;
        }

        arr[i]->setPos(num, num2);
        num+=50;
    }
    scene()->update();
}

void GraphWidget::zoomIn()
{
    for (auto item : edge) {
        if (item != NULL) {
            QMessageBox::warning(this, tr("Ошибка"), tr("Для добавление графа удалите все текущие ребра!"));//сообщение об ошибке
            return;
        }
    }

    for (int i = 0; i < nn; i++) {
        scene()->removeItem(arr[i]);
        arr[i] =NULL;
    }

    if (nn <= 8) {
        nn++;
    }
    else {
        QMessageBox::warning(this, tr("Ошибка"), tr("Максимальное количество граф равно '9'!"));//сообщение об ошибке
    }

    Node_ON_Scene(nn);
}

void GraphWidget::zoomOut()
{
    for (auto item : edge) {
        if (item != NULL) {
            QMessageBox::warning(this, tr("Ошибка"), tr("Для удаление графа удалите все текущие ребра!"));//сообщение об ошибке
            return;
        }
    }

    for (int i = 0; i < nn; i++) {
        scene()->removeItem(arr[i]);
        arr[i] = NULL;
    }


    if (nn > 3) {
        nn--;
    }
    else {
        QMessageBox::warning(this, tr("Ошибка"), tr("Минимальное количествво граф равно '3'!"));//сообщение об ошибке
    }
    Node_ON_Scene(nn);
}

void GraphWidget::choosenode(int node_id)
{
    Clear();
    node_id--;
    if(is_waitlink == false) {
        firstnode = node_id;
        arr[firstnode]->is_choosed = true;
        arr[firstnode]->update();
        is_waitlink = true;
    }
    else {
        arr[firstnode]->is_choosed = false;
        arr[firstnode]->update();
        if(node_id != firstnode) {
            int maxid = qMax(node_id,firstnode);
            int minid = qMin(node_id,firstnode);
            int edge_id = (18-minid)*(minid+1)/2+maxid-10;
            if(!edge[edge_id]) {
                edge[edge_id] = new Edge(arr[firstnode], arr[node_id]);
                scene()->addItem(edge[edge_id]);
            }
            else {
                scene()->removeItem(edge[edge_id]);
                edge[edge_id] = NULL;
                arr[firstnode]->is_choosed = false;
            }
        }
        is_waitlink = false;
    }
}

void GraphWidget::RemoveEdge() {
    Clear();
    for (int i = 0; i < 100000; i++) {
        if (edge[i] != NULL) {
            scene()->removeItem(edge[i]);
            edge[i] = NULL;
        }
    }
}

void GraphWidget::Deikstra() {
    int count = 0;
    for (auto item : edge) {
        if (item == NULL) {
            count++;
        }
    }

    if (count == 100000) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Добавьтье рёбра!"));//сообщение об ошибке
        return;
    }

    QString data = le1->text();
    QStringList list = data.split(",");
    if (data == nullptr || list.size() > 2 || list.size() < 2) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Данные некоректны!"));//сообщение об ошибке
        return;
    }

    int exCount0 = 0;
    int exCount1 = 0;
    for (int i = 0; i < nn; i++) {
        if (list[0].toInt() != arr[i]->m_node_id) {
            exCount0++;
        }
        if (list[1].toInt() != arr[i]->m_node_id) {
            exCount1++;
        }
    }

    if (exCount0 == nn || exCount1 == nn) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Введёные значения должны совподать с значениями вершин!"));//сообщение об ошибке
        return;
    }

    int exCount = 0;
    for (int i = 0; i < nn; i++) {
            int maxid = qMax(list[0].toInt()-1,arr[i]->m_node_id-1);
            int minid = qMin(list[0].toInt()-1,arr[i]->m_node_id-1);
            int edge_id = (18-minid)*(minid+1)/2+maxid-10;
            if(edge[edge_id] == NULL) {
                ++exCount;
                if (exCount == nn) {
                    QMessageBox::warning(this, tr("Ошибка"), tr("Невозможно построить путь от этой вершины!"));//сообщение об ошибке
                    return;
                }
            }
    }

    exCount = 0;
    for (int i = 0; i < nn; i++) {
            int maxid = qMax(list[1].toInt()-1,arr[i]->m_node_id-1);
            int minid = qMin(list[1].toInt()-1,arr[i]->m_node_id-1);
            int edge_id = (18-minid)*(minid+1)/2+maxid-10;
            if(edge[edge_id] == NULL) {
                ++exCount;
                if (exCount == nn) {
                    QMessageBox::warning(this, tr("Ошибка"), tr("Невозможно построить путь до этой вершины!"));//сообщение об ошибке
                    return;
                }
            }
    }

    int a[nn][nn];
    int d[nn];
    int v[nn];
    int temp, minindex, min;
    int begin_index = list[0].toInt()-1;

    for (int i = 0; i< nn; i++)
    {
        for (int j = 0; j<nn; j++) {
            a[i][j] = 0;
        }
    }

    for (int i = 0; i< nn; i++)
    {
        for (int j = i + 1; j<nn; j++) {
            int maxid = qMax(arr[j]->m_node_id-1,arr[i]->m_node_id-1);
            int minid = qMin(arr[j]->m_node_id-1,arr[i]->m_node_id-1);
            int edge_id = (18-minid)*(minid+1)/2+maxid-10;
            if(!edge[edge_id]) {
                a[i][j] = 0;
                a[j][i] = 0;
            }
            else {
                a[i][j] = edge[edge_id]->l;
                a[j][i] = edge[edge_id]->l;
            }
        }
    }


    for (int i = 0; i<nn; i++) {
        d[i] = 10000;
        v[i] = list[0].toInt();
    }

    d[begin_index] = 0;
    do {
        minindex = 10000;
        min = 10000;
        for (int i = 0; i<nn; i++) {
            if ((v[i] == list[0].toInt()) && (d[i]<min)) {
                min = d[i];
                minindex = i;
            }
        }

        if (minindex != 10000) {
            for (int i = 0; i<nn; i++) {
                if (a[minindex][i] > 0) {
                    temp = min + a[minindex][i];
                    if (temp < d[i]) {
                        d[i] = temp;
                    }
                }
            }
            v[minindex] = 0;
        }
    } while (minindex < 10000);

    int ver[nn];
    int end = list[1].toInt() - 1;
    ver[0] = end + 1;
    int k = 1;
    int weight = d[end];

    while (end != begin_index) {
        for (int i = 0; i<nn; i++)
        if (a[i][end] != 0) {
            int temp = weight - a[i][end];
            if (temp == d[i]) {
                weight = temp;
                end = i;
                ver[k] = i + 1;
                k++;
            }
        }
    }

    Clear();

    for (int i = 0; i < nn; i++) {
        for (int j = 0; j < k; j++) {
            if (arr[i]->m_node_id == ver[j]) {
                arr[i]->is_work = true;
                arr[i]->update();
                break;
            }
        }
    }

    for (int i = 0; i < k; i++) {
        if (i != k -1) {
            int maxid = qMax(ver[i]-1,ver[i+1]-1);
            int minid = qMin(ver[i]-1,ver[i+1]-1);
            int edge_id = (18-minid)*(minid+1)/2+maxid-10;
            edge[edge_id]->work = true;
            edge[edge_id]->update();
        }
    }
}

void GraphWidget::Clear() {
    for (int i = 0; i < nn; i++) {
        arr[i]->is_work = false;
        arr[i]->update();
    }

    for (int i = 0; i < 100000; i++) {
        if (edge[i] != NULL) {
            edge[i]->work = false;
            edge[i]->update();
        }
    }
}

