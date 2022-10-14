#include "admin.h"
#include "ui_admin.h"
#include <autentificationwindow.h>

Admin::Admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");//создание объекта классаа QSqlDatabase
    db.setDatabaseName("./testDB.db");//задаём название БД

    if (db.open()) {//провнерка на открытие БД
         qDebug("open");
    }
    else {
        qDebug("no open");
    }

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE user_info(login TEXT NOT NULL, password TEXT NOT NULL);");//создание таблицы

    model = new QSqlTableModel(this, db);
    model->setTable("user_info");
    model->select();

    ui->tableView->setModel(model);//вывод таблтцы на экран
}

Admin::~Admin()
{
    delete ui;
}

void Admin::on_pushButton_clicked()
{
     model->insertRow(model->rowCount());
}

void Admin::on_pushButton_2_clicked()//при нажатии выбраный пользователь удаляется
{
    model->removeRow(row);
}

void Admin::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}

void Admin::on_action_triggered()//при нажатии открывается окно авторизации
{
    auto w = new AutentificationWindow();//объект главного окна
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();//показываем окно
    deleteLater();//прячем предыдущее окно
}


