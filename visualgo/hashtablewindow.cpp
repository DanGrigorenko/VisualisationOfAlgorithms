#include "hashtablewindow.h"
#include "ui_hashtablewindow.h"
#include <menuwindow.h>
#include <QMessageBox>

HashTableWindow::HashTableWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HashTableWindow)
{
    ui->setupUi(this);
}

HashTableWindow::~HashTableWindow()
{
    delete ui;
}

void HashTableWindow::on_action_triggered()
{
    auto w = new MenuWindow();//объект главного окна
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();//показываем окно
    deleteLater();//прячем предыдущее окно
}


void HashTableWindow::on_action_4_triggered()
{
    QMessageBox::about(this, tr("Использование"), tr("..."));
}


void HashTableWindow::on_action_6_triggered()
{
    QMessageBox::about(this, tr("Линейное зондирование"), tr("..."));
}


void HashTableWindow::on_action_7_triggered()
{
    QMessageBox::about(this, tr("Квадратичное зондирование"), tr("..."));
}

