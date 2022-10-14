#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include <sortwindow2.h>
#include <graphwindow.h>
#include <listwindow.h>
#include <hashtablewindow.h>

namespace Ui {
class MenuWindow;
}

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private slots:
    void on_pushButton_clicked();

    void on_action_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MenuWindow *ui;
    SortWindow2 *sort;
    GraphWindow *graph;
    ListWindow *list;
    HashTableWindow *hashTable;
};

#endif // MENUWINDOW_H
