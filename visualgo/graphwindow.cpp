#include "graphwindow.h"
#include "ui_graphwindow.h"
#include <QMessageBox>
#include <graphwidget.h>
#include <menuwindow.h>

GraphWindow::GraphWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::on_action_triggered()//при нажатии открывается окно авторизации
{
    auto w = new MenuWindow();//объект главного окна
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();//показываем окно
    deleteLater();//прячем предыдущее окно
}

void GraphWindow::on_action_4_triggered()
{
    QMessageBox::about(this, tr("Алгоритм Дейстры"), tr("..."));
}


void GraphWindow::on_action_5_triggered()
{
    QMessageBox::about(this, tr("Использование"), tr("Графы\n 1. Для удаление графы нажмите '-' \n 2. Для добавление графы нажмите '+' \n\n Рёбра\n 1. Для установление ребра между графами нажмите на одну графу и на другую \n 2. Для удаление всех рёбер нажмите 'F11'\n 3. Для удаление конкретного ребра нажмтие на графу и на графу которое это ребро соеденяет\n\n Запуск программы \n 1. Введите в текстовое поле значение вершин между которымы хотите найти кратчайший путь \n 2. Для начала визуализвции нажмите 'F10'"));
}

