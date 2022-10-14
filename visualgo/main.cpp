#include "autentificationwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto w = new MenuWindow;
    QSplashScreen* splash = new QSplashScreen();

    splash->setPixmap(QPixmap("/home/cigan/Workspace/QT2/проект/untitled/IMG/visualgo.jpeg"));
    splash->show();

    w->setAttribute(Qt::WA_DeleteOnClose);
    QTimer::singleShot(2500,splash,SLOT(close()));
    QTimer::singleShot(2500,w,SLOT(show()));

    //w->show();
    return a.exec();
}
