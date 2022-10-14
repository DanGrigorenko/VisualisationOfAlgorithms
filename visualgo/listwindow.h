#ifndef LISTWINDOW_H
#define LISTWINDOW_H

#include <QMainWindow>

namespace Ui {
class ListWindow;
}

class ListWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ListWindow(QWidget *parent = nullptr);
    ~ListWindow();

private slots:
    void on_action_triggered();

    void on_action_4_triggered();

    void on_action_5_triggered();

    void on_action_2_triggered();

private:
    Ui::ListWindow *ui;
};

#endif // LISTWINDOW_H
