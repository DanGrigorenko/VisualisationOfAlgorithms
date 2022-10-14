#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphWindow(QWidget *parent = nullptr);
    ~GraphWindow();

private slots:
    void on_action_triggered();

    void on_action_4_triggered();

    void on_action_5_triggered();

private:
    Ui::GraphWindow *ui;

};

#endif // GRAPHWINDOW_H
