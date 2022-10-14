#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QSqlQuery>

namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrationWindow(QWidget *parent = nullptr);
    ~RegistrationWindow();

private slots:

    void on_pushButton_clicked();

    void on_action_triggered();

private:
    Ui::RegistrationWindow *ui;
};

class Creat_Acc
{
private:
    QString user_login;
public:
    Creat_Acc() {}
    Creat_Acc(QString a)
    {
        user_login = a;
    }

    bool Creat()
    {
        QString login, password;

        QSqlQuery query ("SELECT login FROM user_info");//WHERE Username = default
        while (query.next())
        {
            login = query.value(0).toString();
            if (user_login == login) {
                return true;
            }

        }
        return false;
    }
};


#endif // REGISTRATIONWINDOW_H
