#include "listwidget.h"
#include "edgeforlist.h"
#include "nodeforlist.h"
#include <QMessageBox>
#include <math.h>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QPainter>
#include <ctime>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QEventLoop>
#include <algorithm>
#include <QGraphicsColorizeEffect>

ListWidget::ListWidget(QWidget *parent)
    : QGraphicsView(parent)
 {
    for (int i = 0; i < 100000; i++) {
        listEdgeForList[i] = NULL;
    }
    connect(CreatButton,SIGNAL(clicked()),this, SLOT(CreateButtonClicked()));
    connect(RandomFxdS,SIGNAL(clicked()),this, SLOT(RandomFixSizeButtonClicked()));
    connect(InsertButton,SIGNAL(clicked()),this, SLOT(InsertButtonClicked()));
    connect(SearchButton,SIGNAL(clicked()),this, SLOT(SearchButtonClicked()));
    connect(RemoveButton,SIGNAL(clicked()),this, SLOT(RemoveButtonClicked()));
    connect(RandomButton,SIGNAL(clicked()),this, SLOT(RandomButtonClicked()));
    connect(RandomStoredButton,SIGNAL(clicked()),this, SLOT(RandomSortedButtonClicked()));
    connect(MenuuButton,SIGNAL(clicked()),this, SLOT(MenuButtonClicked()));
    connect(CreateGoButton,SIGNAL(clicked()),this, SLOT(CreateGoButtonClicked()));
    connect(SearchGoButton,SIGNAL(clicked()),this, SLOT(SearchGoButtonClicked()));
    connect(InsertTailButton,SIGNAL(clicked()),this, SLOT(InsertTailButtonClicked()));
    connect(InsertHeadButton,SIGNAL(clicked()),this, SLOT(InsertHeadButtonClicked()));
    connect(RemoveHeadButton,SIGNAL(clicked()),this, SLOT(RemoveHeadButtonClicked()));
    connect(RemoveTailButton,SIGNAL(clicked()),this, SLOT(RemoveTailButtonClicked()));
    connect(LinkListButton,SIGNAL(clicked()),this, SLOT(LinkListButtonClicked()));
    connect(StackButton,SIGNAL(clicked()),this, SLOT(StackButtonClicked()));

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

    scene->addWidget(RandomButton);
    scene->addWidget(RandomStoredButton);
    scene->addWidget(RandomFxdS);
    scene->addWidget(InsertHeadButton);
    scene->addWidget(InsertTailButton);
    scene->addWidget(SearchLE);
    scene->addWidget(SearchLabel);
    scene->addWidget(SearchGoButton);
    scene->addWidget(FixedSizeLe);
    scene->addWidget(CreateGoButton);
    scene->addWidget(RemoveHeadButton);
    scene->addWidget(RemoveTailButton);
    scene->addWidget(MenuuButton);
    scene->addWidget(CreatButton);
    scene->addWidget(SearchButton);
    scene->addWidget(InsertButton);
    scene->addWidget(RemoveButton);
    scene->addWidget(LinkListButton);
    scene->addWidget(StackButton);

    ShowMenuItem();
    HideButtons();

    LinkListButton->setGeometry(-500, -320, 495, 50);
    LinkListButton->setText("Cписок       ");
    LinkListButton->setStyleSheet("QPushButton{background: black; border: 0px solid black; color: white; text-align: right;}"
                                 "QPushButton:hover{background: black; border:none; color: white;}");
    LinkListButton->show();

    StackButton->setGeometry(-5, -320, 513, 50);
    StackButton->setText("      Стек");
    StackButton->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid black; color: black; text-align: left;}"
                             "QPushButton:hover{background: black; border:none; color: white;}");
    StackButton->show();

    MenuuButton->setGeometry(-480, 100, 50, 120);
    MenuuButton->setText(">");
    MenuuButton->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid black; color: black; text-align: center;}"
                             "QPushButton:hover{background: black; border:none; color: white;}");
    MenuuButton->show();


    FixedSizeLe->setMaximum(9);
    ListNode(nn);
}

void ListWidget::ShowMenuItem()
{
    CreatButton->setGeometry(-415, 100, 150, 30);
    CreatButton->setText("Создать");
    CreatButton->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid black; color: black; text-align: left;}"
                                 "QPushButton:hover{background: black; border:none; color: white;}");
    CreatButton->show();

    SearchButton->setGeometry(-415, 130, 150, 30);
    if (!isStack) {
        SearchButton->setText("Поиск");
        scene()->update();
    }
    else {
        SearchButton->setText("Просмотор Head");
        scene()->update();
    }
    SearchButton->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid black; color: black; text-align: left;}"
                        "QPushButton:hover{background: black; border:none; color: white;}");
    SearchButton->show();

    InsertButton->setGeometry(-415, 160, 150, 30);
    InsertButton->setText("Вставка");
    InsertButton->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid black; color: black; text-align: left;}"
                        "QPushButton:hover{background: black; border:none; color: white;}");
    InsertButton->show();

    RemoveButton->setGeometry(-415, 190, 150, 30);
    RemoveButton->setText("Удаление");
    RemoveButton->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid black; color: black; text-align: left;}"
                        "QPushButton:hover{background: black; border:none; color: white;}");
    RemoveButton->show();

}

void ListWidget::timeChange(int time) {//время задержки между сменой цветов
    QEventLoop loop;
    QTimer timer;
    timer.setInterval(time); //5 sec
    connect (&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    timer.start();
    loop.exec();
}

void ListWidget::NodePlacement()
{
    int num = 500;
    for (int i = 0; i < nn; i++) {
        if (i == 0) {
            num+=nn*(-100);
        }
        listNodeForList.at(i)->setPos(num,-100);
        num+=100;
    }
}

void ListWidget::StackNodePlacement()
{
    int num = -500;
    for (int i = 0; i < nn; i++) {
        if (i == 0) {
            num+=800;
        }
        stackNodeForList.at(i)->setPos(400,num);
        num-=100;
    }
}

void ListWidget::AddEdge(int firstIndex)
{
    int maxid = qMax(firstIndex,firstIndex+1);
    int minid = qMin(firstIndex,firstIndex+1);
    int edge_id = (18-minid)*(minid+1)/2+maxid-10;

    listEdgeForList[edge_id] = new EdgeForList(listNodeForList[firstIndex], listNodeForList[firstIndex+1]);
    scene()->addItem(listEdgeForList[edge_id]);
}

void ListWidget::RemoveEdge(int index, bool flag)
{
    if (!flag) {
        int maxid = qMax(index,index+1);
        int minid = qMin(index,index+1);
        int edge_id = (18-minid)*(minid+1)/2+maxid-10;

        scene()->removeItem(listEdgeForList[edge_id]);
        listEdgeForList[edge_id] = NULL;
    }
    else {
        int maxid = qMax(index-2,index-1);
        int minid = qMin(index-2,index-1);
        int edge_id = (18-minid)*(minid+1)/2+maxid-10;
        scene()->removeItem(listEdgeForList[edge_id]);
        listEdgeForList[edge_id] = NULL;
    }
}

void ListWidget::StackEdgeRemove(int i)
{
    int maxid = qMax(i,i+1);
    int minid = qMin(i,i+1);
    int edge_id = (18-minid)*(minid+1)/2+maxid-10;

    scene()->removeItem(stackEdgeForList[edge_id]);
    stackEdgeForList[edge_id] = NULL;
}

void ListWidget::StackEdgeAdd(int i)
{
    int maxid = qMax(i,i+1);
    int minid = qMin(i,i+1);
    int edge_id = (18-minid)*(minid+1)/2+maxid-10;

    stackEdgeForList[edge_id] = new EdgeForList(stackNodeForList[i+1], stackNodeForList[i]);
    scene()->addItem(stackEdgeForList[edge_id]);
}

void ListWidget::HideButtons()
{
    RandomButton->hide();
    RandomStoredButton->hide();
    RandomFxdS->hide();
    InsertHeadButton->hide();
    InsertTailButton->hide();
    SearchLE->hide();
    SearchLabel->hide();
    SearchGoButton->hide();
    FixedSizeLe->hide();
    RemoveHeadButton->hide();
    RemoveTailButton->hide();
    FixedSizeLe->hide();
    CreateGoButton->hide();
    CreatButton->hide();
    SearchButton->hide();
    InsertButton->hide();
    RemoveButton->hide();
}

void ListWidget::LinkListButtonClicked()
{
    LinkListButton->setStyleSheet("QPushButton{background: black; border: 0px solid black; color: white; text-align: right;}"
                                 "QPushButton:hover{background: black; border:none; color: white;}");
    StackButton->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid black; color: black; text-align: left;}"
                                "QPushButton:hover{background: black; border:none; color: white;}");
    HideButtons();
    count = 1;
    isStack = false;
    if (!stackNodeForList.isEmpty()) {
        for (int i = 0; i < nn; i++) {
            scene()->removeItem(stackNodeForList.at(i));
        }

        for (int i = 0; i < nn; i++) {
            if (i != nn-1) {
                StackEdgeRemove(i);
            }
        }
        stackNodeForList.clear();
    }

    if (listNodeForList.isEmpty()) {
        ListNode(nn);
    }
}

void ListWidget::StackButtonClicked()
{
    LinkListButton->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid black; color: black; text-align: right;}"
                                 "QPushButton:hover{background: black; border:none; color: white;}");
    StackButton->setStyleSheet("QPushButton{background: black; border: 0px solid black; color: white; text-align: left;}"
                                "QPushButton:hover{background: black; border:none; color: white;}");

    HideButtons();
     count = 1;
    isStack = true;
    if (!listNodeForList.isEmpty()) {
        for (int i = 0; i < nn; i++) {
            scene()->removeItem(listNodeForList.at(i));
        }

        for (int i = 0; i < nn; i++) {
            if (i != nn-1) {
                RemoveEdge(i, false);
            }
        }
        listNodeForList.clear();
    }

    if (stackNodeForList.isEmpty()) {
        if (nn > 6) {
            nn -= 3;
        }
        StackNode(nn);
    }
}

void ListWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void ListWidget::ListNode(int nn)
{
    for (int i = 0; i < nn; i++) {
        listNodeForList.push_back(new NodeForList(this));
    }

    srand(time(NULL));
    for (int i = 0; i < nn; i++) {
        listNodeForList.at(i)->m_node_id = 1+rand()%99;
        scene()->addItem(listNodeForList.at(i));
    }

    NodePlacement();

    for (int i = 0; i < nn; i++) {
        if (i != nn-1) {
            AddEdge(i);
        }
    }

    scene()->update();
}

void ListWidget::StackNode(int nn)
{
    for (int i = 0; i < nn; i++) {
        stackNodeForList.push(new NodeForList(this));
    }

    srand(time(NULL));
    for (int i = 0; i < nn; i++) {
        stackNodeForList.at(i)->m_node_id = 1+rand()%99;
        scene()->addItem(stackNodeForList.at(i));
    }

    StackNodePlacement();

    for (int i = 0; i < nn; i++) {
        if (i != nn-1) {
            StackEdgeAdd(i);
        }
    }

    scene()->update();
}

void ListWidget::MenuButtonClicked()
{
    if (count != 2) {
        MenuuButton->setText("<");

        ShowMenuItem();
        count++;
    }
    else  {
        MenuuButton->setText(">");
        HideButtons();
        count = 1;
    }
}

void ListWidget::CreateButtonClicked()
{
    InsertHeadButton->hide();
    InsertTailButton->hide();
    SearchLE->hide();
    SearchLabel->hide();
    SearchGoButton->hide();
    RemoveHeadButton->hide();
    RemoveTailButton->hide();

    RandomButton->setGeometry(-230, 100, 60, 30);
    RandomButton->setText("Random");
    RandomButton->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid black; color: black; text-align: left;}"
                             "QPushButton:hover{background: black; border:none; color: white;}");
    RandomButton->show();

    RandomStoredButton->setGeometry(-150, 100, 110, 30);
    RandomStoredButton->setText("Random Sorted");
    RandomStoredButton->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid black; color: black; text-align: left;}"
                             "QPushButton:hover{background: black; border:none; color: white;}");
    RandomStoredButton->show();

    RandomFxdS->setGeometry(-20, 100, 130, 30);
    RandomFxdS->setText("Random Fixed Size");
    RandomFxdS->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid black; color: black; text-align: left;}"
                             "QPushButton:hover{background: black; border:none; color: white;}");
    RandomFxdS->show();
}

void ListWidget::SearchButtonClicked()
{
    RandomButton->hide();
    RandomStoredButton->hide();
    RandomFxdS->hide();
    InsertHeadButton->hide();
    InsertTailButton->hide();
    FixedSizeLe->hide();
    CreateGoButton->hide();
    RemoveHeadButton->hide();
    RemoveTailButton->hide();

    if (!isStack) {

        SearchLE->setGeometry(-230, 130, 60, 30);
        SearchLE->show();

        SearchLabel->setGeometry(-260,130,30,30);
        SearchLabel->setText("v=");
        SearchLabel->setStyleSheet("background: #D7E1E9; font-size: 25px");
        SearchLabel->show();

        SearchGoButton->setGeometry(-160, 130, 50, 30);
        SearchGoButton->setText("Go");
        SearchGoButton->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid black; color: black; text-align: left;}"
                                 "QPushButton:hover{background: black; border:none; color: white;}");
        SearchGoButton->show();
    }
    else  {
        stackNodeForList[nn-1]->isChoosed = true;
        stackNodeForList[nn-1]->update();
    }
}

void ListWidget::InsertButtonClicked()
{
    SearchLE->hide();
    RandomButton->hide();
    RandomStoredButton->hide();
    RandomFxdS->hide();
    SearchLabel->hide();
    SearchGoButton->hide();
    FixedSizeLe->hide();
    CreateGoButton->hide();
    RemoveHeadButton->hide();
    RemoveTailButton->hide();

    if (!isStack) {
        InsertHeadButton->setGeometry(-230, 160, 150, 30);
        InsertHeadButton->setText("i=0(Head), specify v=");
        InsertHeadButton->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid black; color: black; text-align: left;}"
                                 "QPushButton:hover{background: black; border:none; color: white;}");
        InsertHeadButton->show();

        InsertTailButton->setGeometry(-60, 160, 150, 30);
        InsertTailButton->setText("i=0(Tail), specify v=");
        InsertTailButton->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid black; color: black; text-align: left;}"
                                 "QPushButton:hover{background: black; border:none; color: white;}");
        InsertTailButton->show();
    }
    else {
        if (nn != 6) {
            stackNodeForList[nn-1]->isChoosed = false;
            stackNodeForList[nn-1]->update();

            for (int i = 0; i < nn; i++) {
                if (i != nn-1) {
                    StackEdgeRemove(i);
                }
            }
            nn++;
        }
        else {
            QMessageBox::warning(this, tr("Ошибка"), tr("Максимальная длинна стека 6!"));//сообщение об ошибке
            return;
        }
        InsertButton->setEnabled(false);

        NodeForList* node = new NodeForList(this);
        node->m_node_id = 1+rand()%99;
        stackNodeForList.push(node);
        scene()->addItem(stackNodeForList.at(nn-1));

        StackNodePlacement();

        for (int i = 0; i < nn; i++) {
            if (i != nn-1) {
                StackEdgeAdd(i);
            }
        }

        NodeForList* buff = stackNodeForList[nn-1];
        stackNodeForList[nn-1]->insertAndRemove = true;
        auto *moveAnimation = new QVariantAnimation();
        moveAnimation->setDuration(2000);
        moveAnimation->setStartValue(QPointF( stackNodeForList[nn-2]->x()-100,  stackNodeForList[nn-2]->y()));
        moveAnimation->setEndValue(QPointF( stackNodeForList[nn-2]->x(),  stackNodeForList[nn-2]->y()-100));
        moveAnimation->start(QAbstractAnimation::DeleteWhenStopped);

        QObject::connect(moveAnimation, &QVariantAnimation::valueChanged, [buff](const QVariant &value){
            buff->setPos(value.toPointF());
            buff->update();
        });

        timeChange(2100);
        stackNodeForList[nn-1]->insertAndRemove = false;
        stackNodeForList[nn-1]->update();
        InsertButton->setEnabled(true);
    }
}

void ListWidget::RemoveButtonClicked()
{

    SearchLE->hide();
    RandomButton->hide();
    RandomStoredButton->hide();
    RandomFxdS->hide();
    SearchLabel->hide();
    SearchGoButton->hide();
    FixedSizeLe->hide();
    CreateGoButton->hide();
    InsertHeadButton->hide();
    InsertTailButton->hide();

     if (!isStack) {
        RemoveHeadButton->setGeometry(-230, 190, 150, 30);
        RemoveHeadButton->setText("Remove i=0 (Head)");
        RemoveHeadButton->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid black; color: black; text-align: left;}"
                                 "QPushButton:hover{background: black; border:none; color: white;}");
        RemoveHeadButton->show();

        RemoveTailButton->setGeometry(-60, 190, 150, 30);
        RemoveTailButton->setText("Remove i=N-1 (Tail)");
        RemoveTailButton->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid black; color: black; text-align: left;}"
                                 "QPushButton:hover{background: black; border:none; color: white;}");
        RemoveTailButton->show();
    }
     else {
         if (nn == 1) {
             QMessageBox::warning(this, tr("Ошибка"), tr("Минимальная длинна стека 1!"));//сообщение об ошибке
             return;
         }
         RemoveButton->setEnabled(false);

         stackNodeForList[nn-1]->isChoosed = false;
         stackNodeForList[nn-1]->update();

         NodeForList* buff = stackNodeForList.at(nn-1);
         stackNodeForList[nn-1]->isChoosed = true;
         auto *moveAnimation = new QVariantAnimation();
         moveAnimation->setDuration(1000);
         moveAnimation->setStartValue(QPointF(stackNodeForList.at(nn-1)->x(),  stackNodeForList.at(nn-1)->y()));
         moveAnimation->setEndValue(QPointF(stackNodeForList.at(nn-2)->x(),  stackNodeForList.at(nn-2)->y()-40));
         moveAnimation->start(QAbstractAnimation::DeleteWhenStopped);

         QObject::connect(moveAnimation, &QVariantAnimation::valueChanged, [buff](const QVariant &value){
             buff->setPos(value.toPointF());
             buff->update();
         });
         timeChange(1000);

         int maxid = qMax(nn-2,nn-1);
         int minid = qMin(nn-2,nn-1);
         int edge_id = (18-minid)*(minid+1)/2+maxid-10;
         scene()->removeItem(stackEdgeForList[edge_id]);
         stackEdgeForList[edge_id] = NULL;

         scene()->removeItem(stackNodeForList.at(nn-1));
         stackNodeForList.pop_back();

         nn--;
         RemoveButton->setEnabled(true);

     }
}

void ListWidget::RandomButtonClicked()
{

    isFront = false;
    countt = 0;
    FixedSizeLe->hide();
    CreateGoButton->hide();

    if (!isStack) {
        for (int i = 0; i < nn; i++) {
            scene()->removeItem(listNodeForList.at(i));
        }

        for (int i = 0; i < nn; i++) {
            if (i != nn-1) {
                RemoveEdge(i, false);
            }
        }
        listNodeForList.clear();

        srand(time(NULL));
        int b = nn;
        while (nn == b) {
            nn = 2 + rand()%(9-2+1);
        }
        ListNode(nn);
    }
    else {
        for (int i = 0; i < nn; i++) {
            scene()->removeItem(stackNodeForList.at(i));
        }

        for (int i = 0; i < nn; i++) {
            if (i != nn-1) {
                StackEdgeRemove(i);
            }
        }
        stackNodeForList.clear();

        srand(time(NULL));
        int b = nn;
        while (nn == b) {
            nn = 2 + rand()%(6-2+1);
        }
        StackNode(nn);
    }
}

void ListWidget::RandomSortedButtonClicked()
{
    isFront = false;
    countt = 0;
    FixedSizeLe->hide();
    CreateGoButton->hide();

    if (!isStack) {
        for (int i = 0; i < nn; i++) {
            scene()->removeItem(listNodeForList.at(i));
        }

        for (int i = 0; i < nn; i++) {
            if (i != nn-1) {
                RemoveEdge(i, false);
            }
        }
        listNodeForList.clear();

        srand(time(NULL));
        int b = nn;
        while (nn == b) {
            nn = 2 + rand()%(9-2+1);
        }

        for (int i = 0; i < nn; i++) {
            listNodeForList.push_back(new NodeForList(this));
        }

        srand(time(NULL));
        QList<int> listInt;
        for (int i = 0; i < nn; i++) {
            int num = 1+rand()%99;
            listInt.push_back(num);
        }

        for (int i = 0; i < nn-1; i++) {
            for (int j = 0; j < nn-i-1; j++) {
                if (listInt[j] > listInt[j+1]) {
                    qSwap(listInt[j],listInt[j+1]);
                }
            }
        }

        for (int i = 0; i < nn; i++) {
            listNodeForList.at(i)->m_node_id = listInt.at(i);
            scene()->addItem(listNodeForList.at(i));
        }

        NodePlacement();

        for (int i = 0; i < nn; i++) {
            if (i != nn-1) {
                AddEdge(i);
            }
        }

        scene()->update();
    }
    else {
        for (int i = 0; i < nn; i++) {
            scene()->removeItem(stackNodeForList.at(i));
        }

        for (int i = 0; i < nn; i++) {
            if (i != nn-1) {
               StackEdgeRemove(i);
            }
        }
        stackNodeForList.clear();

        srand(time(NULL));
        int b = nn;
        while (nn == b) {
            nn = 2 + rand()%(6-2+1);
        }

        for (int i = 0; i < nn; i++) {
            stackNodeForList.push(new NodeForList(this));
        }

        srand(time(NULL));
        QList<int> listInt;
        for (int i = 0; i < nn; i++) {
            int num = 1+rand()%99;
            listInt.push_back(num);
        }

        for (int i = 0; i < nn-1; i++) {
            for (int j = 0; j < nn-i-1; j++) {
                if (listInt[j] > listInt[j+1]) {
                    qSwap(listInt[j],listInt[j+1]);
                }
            }
        }

        int k = nn-1;
        for (int i = 0; i < nn; i++) {
            stackNodeForList.at(i)->m_node_id = listInt.at(k);
            scene()->addItem(stackNodeForList.at(i));
            k--;
        }

        StackNodePlacement();

        for (int i = 0; i < nn; i++) {
            if (i != nn-1) {
                StackEdgeAdd(i);
            }
        }
        scene()->update();
    }

}

void ListWidget::RandomFixSizeButtonClicked()
{
    if(!isStack)
        FixedSizeLe->setMaximum(9);
    else
        FixedSizeLe->setMaximum(6);
    FixedSizeLe->setGeometry(-20, 125, 76, 30);
    FixedSizeLe->show();

    CreateGoButton->setGeometry(58, 125, 50, 30);
    CreateGoButton->setText("Go");
    CreateGoButton->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid black; color: black; text-align: left;}"
                             "QPushButton:hover{background: black; border:none; color: white;}");
    CreateGoButton->show();
}

void ListWidget::CreateGoButtonClicked()
{
    if (!isStack) {
        isFront = false;
        countt = 0;

        for (int i = 0; i < nn; i++) {
            scene()->removeItem(listNodeForList.at(i));
        }

        for (int i = 0; i < nn; i++) {
            if (i != nn-1) {
                RemoveEdge(i, false);
            }
        }
        listNodeForList.clear();

        QString number= FixedSizeLe->text();
        nn = number.toInt();
        ListNode(nn);
    }
    else {
        for (int i = 0; i < nn; i++) {
            scene()->removeItem(stackNodeForList.at(i));
        }

        for (int i = 0; i < nn; i++) {
            if (i != nn-1) {
               StackEdgeRemove(i);
            }
        }
        stackNodeForList.clear();

        QString number= FixedSizeLe->text();
        nn = number.toInt();
        StackNode(nn);
    }
}

void ListWidget::SearchGoButtonClicked()
{
    SearchGoButton->setEnabled(false);
    MenuuButton->setEnabled(false);
    CreatButton->setEnabled(false);
    SearchButton->setEnabled(false);
    InsertButton->setEnabled(false);
    RemoveButton->setEnabled(false);
    StackButton->setEnabled(false);
    LinkListButton->setEnabled(false);

    for (int i = 0; i < nn; i++) {
        listNodeForList.at(i)->desired = false;
        listNodeForList.at(i)->isChoosed = false;
        listNodeForList.at(i)->update();
    }

    int k = 0;
    int edge_id, maxid, minid;
    for (int i = 0; i < nn; i++) {
        listNodeForList.at(i)->isChoosed = true;
        listNodeForList.at(i)->update();

        if (listNodeForList.at(i)->m_node_id == SearchLE->text().toInt()) {
            listNodeForList.at(i)->desired = true;
            break;
        }

        timeChange(500);
        if (i != nn-1) {
            if (!isFront) {
                maxid = qMax(k,k+1);
                minid = qMin(k,k+1);
            }
            else {
                maxid = qMax(nn-i-2,nn-i-1);
                minid = qMin(nn-i-2,nn-i-1);
            }
                edge_id = (18-minid)*(minid+1)/2+maxid-10;
                listEdgeForList[edge_id]->isChoosed = true;
                listEdgeForList[edge_id]->update();
                k++;
                timeChange(500);
                listEdgeForList[edge_id]->isChoosed = false;
                listEdgeForList[edge_id]->update();
        }

        listNodeForList.at(i)->isChoosed = false;
        listNodeForList.at(i)->update();
    }

    SearchGoButton->setEnabled(true);
    MenuuButton->setEnabled(true);
    CreatButton->setEnabled(true);
    SearchButton->setEnabled(true);
    InsertButton->setEnabled(true);
    RemoveButton->setEnabled(true);
    StackButton->setEnabled(true);
    LinkListButton->setEnabled(true);
}

void ListWidget::InsertHeadButtonClicked()
{
    for (int i = 0; i < nn; i++) {
        listNodeForList.at(i)->desired = false;
        listNodeForList.at(i)->isChoosed = false;
        listNodeForList.at(i)->update();
    }

    isFront = true;
    countt = 0;

    if (nn != 9)
        nn++;
    else {
        QMessageBox::warning(this, tr("Ошибка"), tr("Максимальная длинна листа 9!"));//сообщение об ошибке
        return;
    }

    InsertHeadButton->setEnabled(false);

    NodeForList* node = new NodeForList(this);
    node->m_node_id = 1+rand()%99;
    listNodeForList.push_front(node);
    scene()->addItem(listNodeForList.at(0));

    NodePlacement();

    int maxid = qMax(nn-2,nn-1);
    int minid = qMin(nn-2,nn-1);
    int edge_id = (18-minid)*(minid+1)/2+maxid-10;
    listEdgeForList[edge_id] = new EdgeForList(listNodeForList[0], listNodeForList[1]);
    scene()->addItem(listEdgeForList[edge_id]);

    NodeForList* buff = listNodeForList[0];
    listNodeForList[0]->insertAndRemove = true;
    auto *moveAnimation = new QVariantAnimation();
    moveAnimation->setDuration(1000);
    moveAnimation->setStartValue(QPointF(listNodeForList[1]->x(), listNodeForList[1]->y()+100));
    moveAnimation->setEndValue(QPointF(listNodeForList[1]->x()-100, listNodeForList[1]->y()));
    moveAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    QObject::connect(moveAnimation, &QVariantAnimation::valueChanged, [buff](const QVariant &value){
        buff->setPos(value.toPointF());
        buff->update();
    });

    timeChange(1100);
    listNodeForList[0]->insertAndRemove = false;
    listNodeForList[0]->update();
    InsertHeadButton->setEnabled(true);
}


void ListWidget::InsertTailButtonClicked()
{
    for (int i = 0; i < nn; i++) {
        listNodeForList.at(i)->desired = false;
        listNodeForList.at(i)->isChoosed = false;
        listNodeForList.at(i)->update();
    }

    isFront = false;
    countt = 0;

    if (nn != 9)
        nn++;
    else {
        QMessageBox::warning(this, tr("Ошибка"), tr("Максимальная длинна листа 9!"));//сообщение об ошибке
        return;
    }

    InsertTailButton->setEnabled(false);

    NodeForList* node = new NodeForList(this);
    node->m_node_id = 1+rand()%99;
    listNodeForList.push_back(node);
    scene()->addItem(listNodeForList.at(nn-1));

    NodePlacement();

    int maxid = qMax(nn-2,nn-1);
    int minid = qMin(nn-2,nn-1);
    int edge_id = (18-minid)*(minid+1)/2+maxid-10;
    listEdgeForList[edge_id] = new EdgeForList(listNodeForList[nn-2], listNodeForList[nn-1]);
    scene()->addItem(listEdgeForList[edge_id]);

    NodeForList* buff = listNodeForList[nn-1];
    listNodeForList[nn-1]->insertAndRemove = true;
    auto *moveAnimation = new QVariantAnimation();
    moveAnimation->setDuration(1000);
    moveAnimation->setStartValue(QPointF(listNodeForList[nn-2]->x(), listNodeForList[nn-2]->y()+100));
    moveAnimation->setEndValue(QPointF(listNodeForList[nn-2]->x()+100, listNodeForList[nn-2]->y()));
    moveAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    QObject::connect(moveAnimation, &QVariantAnimation::valueChanged, [buff](const QVariant &value){
        buff->setPos(value.toPointF());
        buff->update();
    });

    timeChange(1100);
    listNodeForList[nn-1]->insertAndRemove = false;
    listNodeForList[nn-1]->update();
    InsertTailButton->setEnabled(true);
}

void ListWidget::RemoveHeadButtonClicked()
{
    if (nn == 1) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Минимальная длинна листа 1!"));//сообщение об ошибке
        return;
    }

    RemoveHeadButton->setEnabled(false);

    if (!isFront) {
        NodeForList* buff = listNodeForList.at(0);
        listNodeForList[0]->isChoosed = true;
        auto *moveAnimation = new QVariantAnimation();
        moveAnimation->setDuration(1000);
        moveAnimation->setStartValue(QPointF( listNodeForList.at(0)->x(),  listNodeForList.at(0)->y()));
        moveAnimation->setEndValue(QPointF(listNodeForList.at(1)->x()-40,  listNodeForList.at(1)->y()));
        moveAnimation->start(QAbstractAnimation::DeleteWhenStopped);

        QObject::connect(moveAnimation, &QVariantAnimation::valueChanged, [buff](const QVariant &value){
            buff->setPos(value.toPointF());
            buff->update();
        });
        timeChange(1000);
        RemoveEdge(countt, false);
    }
    else {
        NodeForList* buff = listNodeForList.at(0);
        listNodeForList[0]->isChoosed = true;
        auto *moveAnimation = new QVariantAnimation();
        moveAnimation->setDuration(1000);
        moveAnimation->setStartValue(QPointF( listNodeForList.at(0)->x(),  listNodeForList.at(0)->y()));
        moveAnimation->setEndValue(QPointF(listNodeForList.at(1)->x()-40,  listNodeForList.at(1)->y()));
        moveAnimation->start(QAbstractAnimation::DeleteWhenStopped);

        QObject::connect(moveAnimation, &QVariantAnimation::valueChanged, [buff](const QVariant &value){
            buff->setPos(value.toPointF());
            buff->update();
        });
        timeChange(1000);
        RemoveEdge(nn, true);
    }
    scene()->removeItem(listNodeForList.at(0));
    listNodeForList.pop_front();

    RemoveHeadButton->setEnabled(true);

    countt++;
    nn--;
}

void ListWidget::RemoveTailButtonClicked()
{
    if (nn == 1) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Минимальная длинна листа 1!"));//сообщение об ошибке
        return;
    }

   RemoveTailButton->setEnabled(false);

    if (isFront) {
        NodeForList* buff = listNodeForList.at(nn-1);
        listNodeForList[nn-1]->isChoosed = true;
        auto *moveAnimation = new QVariantAnimation();
        moveAnimation->setDuration(1000);
        moveAnimation->setStartValue(QPointF( listNodeForList.at(nn-1)->x(),  listNodeForList.at(nn-1)->y()));
        moveAnimation->setEndValue(QPointF(listNodeForList.at(nn-2)->x()+40,  listNodeForList.at(nn-2)->y()));
        moveAnimation->start(QAbstractAnimation::DeleteWhenStopped);

        QObject::connect(moveAnimation, &QVariantAnimation::valueChanged, [buff](const QVariant &value){
            buff->setPos(value.toPointF());
            buff->update();
        });
        timeChange(1000);
         RemoveEdge(countt, false);
    }
    else {
        NodeForList* buff = listNodeForList.at(nn-1);
        listNodeForList[nn-1]->isChoosed = true;
        auto *moveAnimation = new QVariantAnimation();
        moveAnimation->setDuration(1000);
        moveAnimation->setStartValue(QPointF( listNodeForList.at(nn-1)->x(),  listNodeForList.at(nn-1)->y()));
        moveAnimation->setEndValue(QPointF(listNodeForList.at(nn-2)->x()+40,  listNodeForList.at(nn-2)->y()));
        moveAnimation->start(QAbstractAnimation::DeleteWhenStopped);

        QObject::connect(moveAnimation, &QVariantAnimation::valueChanged, [buff](const QVariant &value){
            buff->setPos(value.toPointF());
            buff->update();
        });
        timeChange(1000);
        RemoveEdge(nn, true);
    }

    RemoveTailButton->setEnabled(true);

    scene()->removeItem(listNodeForList.at(nn-1));
    listNodeForList.pop_back();

    countt++;
    nn--;
}
