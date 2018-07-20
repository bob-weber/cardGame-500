#-------------------------------------------------
#
# Project created by QtCreator 2018-06-03T12:52:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14
INCLUDEPATH += headers

# Define major/minor builds
# Build # and date are automatically calculated
MAJOR_VERSION=0
MINOR_VERSION=1
BUILD_NUM = $$system(./buildNumber)
DEFINES += MAJOR_VERSION=$${MAJOR_VERSION} MINOR_VERSION=$${MINOR_VERSION} BUILD_NUMBER=$${BUILD_NUM}

TARGET = cards-500-$${MAJOR_VERSION}.$${MINOR_VERSION}
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
    sources/main.cpp \
    sources/mainwindow.cpp \
    sources/player.cpp \
    sources/user_bid_dialog.cpp \
    sources/logic.cpp \
    sources/utilities.cpp \
    sources/bid.cpp \
    sources/mergecards.cpp \
    sources/score.cpp \
    sources/bidding.cpp \
    sources/mergeDialog.cpp

HEADERS += \
    headers/card.h \
    headers/clickableqlabel.h \
    headers/deck.h \
    headers/mainwindow.h \
    headers/player.h \
    headers/user_bid_dialog.h \
    headers/logic.h \
    headers/utilities.h \
    headers/bid.h \
    headers/mergecards.h \
    headers/bidding.h \
    headers/score.h \
    headers/game_500_settings.h \
    headers/mergeDialog.h

FORMS += \
    mainwindow.ui \
    user_bid_dialog.ui \
    mergeDialog.ui

RESOURCES += \
    cardgame.qrc
