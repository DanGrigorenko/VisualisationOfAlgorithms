#ifndef SORTWINDOW2_H
#define SORTWINDOW2_H

#include <QMainWindow>
#include <QLabel>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>

namespace Ui {
class SortWindow2;
}

class SortWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit SortWindow2(QWidget *parent = nullptr);
    ~SortWindow2();

private slots:
    void timeChange(int time);
    void countReangements(int& count);
    void clear();
    void InputValues();
    void Animation(int i);
    void AnimationSecondEl(int i);
    void on_pushButton_11_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_12_clicked();
    void on_action_triggered();
    void on_pushButton_19_clicked();
    void on_actionBUBBLE_triggered();
    void on_actionSELECTION_triggered();
    void on_actionINSERTION_triggered();
    void on_actionMERGE_triggered();
    void on_action_3_triggered();
    void Enabled();

private:
    Ui::SortWindow2 *ui;
    QLabel* buttonList[8];
    int n = 8, count;
    bool bubble, selection, insertion, shaker, isWork = false;
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
    QGraphicsDropShadowEffect *effect2 = new QGraphicsDropShadowEffect();
    QGraphicsDropShadowEffect *effect3 = new QGraphicsDropShadowEffect();
};

#endif // SORTWINDOW2_H
