#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QGraphicsView>
#include <QLineEdit>
#include <QList>
#include <QStack>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>
#include <QPropertyAnimation>

class NodeForList;
class EdgeForList;
class ListWidget : public QGraphicsView
{
    Q_OBJECT

public:
    ListWidget(QWidget *parent = nullptr);
    QList<NodeForList*> listNodeForList;
    EdgeForList* listEdgeForList[100000];
    QStack<NodeForList*> stackNodeForList;
    EdgeForList* stackEdgeForList[100000];
    int firstnode = 0;

public slots:
    void ShowMenuItem();
    void timeChange(int time);
    void NodePlacement();
    void StackNodePlacement();
    void AddEdge(int i);
    void RemoveEdge(int i, bool flag);
    void StackEdgeRemove(int i);
    void StackEdgeAdd(int i);
    void HideButtons();
    void LinkListButtonClicked();
    void StackButtonClicked();
    void ListNode(int n);
    void StackNode(int n);
    void CreateButtonClicked();
    void InsertButtonClicked();
    void SearchButtonClicked();
    void RandomFixSizeButtonClicked();
    void RemoveButtonClicked();
    void RandomButtonClicked();
    void RandomSortedButtonClicked();
    void MenuButtonClicked();
    void CreateGoButtonClicked();
    void SearchGoButtonClicked();
    void InsertTailButtonClicked();
    void InsertHeadButtonClicked();
    void RemoveHeadButtonClicked();
    void RemoveTailButtonClicked();
protected:
    void scaleView(qreal scaleFactor);

private:
    int nn = 3, count = 1, countt = 0, counttt = 0;
    bool isFront = false, isStack = false;
    QPushButton* LinkListButton = new QPushButton();
    QPushButton* StackButton = new QPushButton();
    QPushButton* InsertButton = new QPushButton();
    QPushButton* RemoveButton = new QPushButton();
    QPushButton* SearchButton = new QPushButton();
    QPushButton* CreatButton = new QPushButton();
    QPushButton* RandomButton = new QPushButton();
    QPushButton* RandomFxdS = new QPushButton();
    QSpinBox* FixedSizeLe = new QSpinBox();
    QPushButton* CreateGoButton = new QPushButton();
    QPushButton* RandomStoredButton = new QPushButton();
    QPushButton* InsertHeadButton = new QPushButton();
    QPushButton* InsertTailButton = new QPushButton();
    QSpinBox* SearchLE = new QSpinBox();
    QLabel* SearchLabel = new QLabel();
    QPushButton* SearchGoButton = new QPushButton();
    QPushButton* RemoveHeadButton = new QPushButton();
    QPushButton* RemoveTailButton = new QPushButton();
    QPushButton* MenuuButton = new QPushButton();
};
#endif // LISTWIDGET_H
