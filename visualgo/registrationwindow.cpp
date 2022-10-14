#include "registrationwindow.h"
#include "ui_registrationwindow.h"
#include <autentificationwindow.h>
#include <QSqlQuery>
#include <QMessageBox>

RegistrationWindow::RegistrationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegistrationWindow)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    ui->lineEdit->setPlaceholderText("Логин");
    ui->lineEdit_2->setPlaceholderText("Пароль");
    ui->lineEdit_3->setPlaceholderText("Повторите пароль");
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::on_pushButton_clicked()//при нажатии открывается пользователь заносится в БД и открывается окно авторизации
{
    QString login = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QString repeat_password = ui->lineEdit_3->text();
    QSqlQuery query;
    Creat_Acc creat(login);
    if (login != nullptr) {
        if (creat.Creat() == false) {
            if (password.length() >= 5 && password.length() <= 13) {
                 if (password == repeat_password) {
                    query = QSqlQuery("INSERT INTO user_info (login, password) VALUES('" + login + "', '" + password + "')");

                    QMessageBox::about(this, tr("Справка"), tr("Аккаунт успешно создан!"));//уведомление о соз

                    auto w = new AutentificationWindow();//объект главного окна
                    w->setAttribute(Qt::WA_DeleteOnClose);
                    w->show();//показываем окно
                    deleteLater();//прячем предыдущее окно
                 }
                 else {
                     QMessageBox::warning(this, tr("Ошибка"), tr("Пароли не совпадают!"));//сообщение об ошибке
                 }
            }
            else {
                QMessageBox::warning(this, tr("Ошибка"), tr("Длинна пароля должна быть неменьше 5 и небольше 13!"));//сообщение об ошибке
            }
        }
        else {
            QMessageBox::warning(this, tr("Ошибка"), tr("Аккаунт с таким имнем уже существует!"));//сообщение об ошибке
        }
    }
    else {
        QMessageBox::warning(this, tr("Ошибка"), tr("Поле логин должно быть заполненно!"));//сообщение об ошибке
    }
}


void RegistrationWindow::on_action_triggered()//при нажатии открывается окно авторизации
{
    auto w = new AutentificationWindow();//объект главного окна
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();//показываем окно
    deleteLater();//прячем предыдущее окно
}


