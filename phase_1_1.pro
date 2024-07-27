QT       += core gui
 QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    baseattacker.cpp \
    baseattacker3.cpp \
    baseenemy.cpp \
    baseenemy2.cpp \
    buff.cpp \
    bullet.cpp \
    defenders.cpp \
    enemy.cpp \
    flyer.cpp \
    main.cpp \
    map.cpp \
    nut.cpp \
    objects.cpp \
    tower.cpp \
    towerdefence.cpp

HEADERS += \
    baseattacker.h \
    baseattacker3.h \
    baseenemy.h \
    baseenemy2.h \
    buff.h \
    bullet.h \
    defenders.h \
    enemy.h \
    flyer.h \
    map.h \
    nut.h \
    objects.h \
    tower.h \
    towerdefence.h

FORMS += \
    towerdefence.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/phase1_res.qrc
