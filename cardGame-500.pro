#-------------------------------------------------
#
# Project created by QtCreator 2018-06-03T12:52:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14 static
INCLUDEPATH += headers

TARGET = cards-500
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    sources/card.cpp \
    sources/clickableqlabel.cpp \
    sources/deck.cpp \
    sources/gamelogic_500.cpp \
    sources/main.cpp \
    sources/mainwindow.cpp \
    sources/player.cpp \
    sources/user_bid_dialog.cpp

HEADERS += \
    headers/card.h \
    headers/clickableqlabel.h \
    headers/deck.h \
    headers/gamelogic_500.h \
    headers/mainwindow.h \
    headers/player.h \
    headers/user_bid_dialog.h

FORMS += \
    mainwindow.ui \
    user_bid_dialog.ui

RESOURCES += \
    cardgame.qrc
