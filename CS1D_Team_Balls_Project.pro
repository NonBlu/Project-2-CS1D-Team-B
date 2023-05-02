QT += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminlogin.cpp \
    adminpage.cpp \
    dynamictable.cpp \
    informationview.cpp \
    main.cpp \
    mainwindow.cpp \
    receipt.cpp \
    selectyourtour.cpp \
    souvenirshop.cpp \
    tourpage.cpp \
    mlb.cpp \
    stadiummanager.cpp

HEADERS += \
    adminlogin.h \
    adminpage.h \
    dynamictable.h \
    informationview.h \
    mainwindow.h \
    receipt.h \
    selectyourtour.h \
    souvenirshop.h \
    tourpage.h \
    Containers/Graph.h \
    Containers/Map.h \
    Containers/Vector.h \
    mlb.h \
    stadiummanager.h

FORMS += \
    adminlogin.ui \
    adminpage.ui \
    dynamictable.ui \
    informationview.ui \
    mainwindow.ui \
    receipt.ui \
    selectyourtour.ui \
    souvenirshop.ui \
    tourpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
  Resources.qrc
