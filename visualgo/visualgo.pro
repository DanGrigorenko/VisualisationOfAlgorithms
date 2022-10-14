QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    autentificationwindow.cpp \
    edge.cpp \
    edgeforlist.cpp \
    graphwidget.cpp \
    graphwindow.cpp \
    hashtablewindow.cpp \
    hashwidget.cpp \
    listwidget.cpp \
    listwindow.cpp \
    main.cpp \
    menuwindow.cpp \
    node.cpp \
    nodeforhash.cpp \
    nodeforlist.cpp \
    registrationwindow.cpp \
    sortwindow2.cpp

HEADERS += \
    admin.h \
    autentificationwindow.h \
    edge.h \
    edgeforlist.h \
    graphwidget.h \
    graphwindow.h \
    hashtablewindow.h \
    hashwidget.h \
    listwidget.h \
    listwindow.h \
    menuwindow.h \
    node.h \
    nodeforhash.h \
    nodeforlist.h \
    registrationwindow.h \
    sortwindow2.h

FORMS += \
    admin.ui \
    autentificationwindow.ui \
    graphwindow.ui \
    hashtablewindow.ui \
    listwindow.ui \
    menuwindow.ui \
    registrationwindow.ui \
    sortwindow2.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES +=
