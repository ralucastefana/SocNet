#-------------------------------------------------
#
# Project created by QtCreator 2017-01-07T13:49:48
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProiectRCClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp \
    login.cpp \
    homepage.cpp \
    register.cpp \
    profileedit.cpp \
    friend.cpp \
    addfriend.cpp \
    viewchats.cpp \
    createchat.cpp \
    chat.cpp

HEADERS  += mainwindow.h \
    client.h \
    login.h \
    structs.h \
    homepage.h \
    register.h \
    profileedit.h \
    friend.h \
    addfriend.h \
    viewchats.h \
    createchat.h \
    chat.h

FORMS    += mainwindow.ui \
    login.ui \
    homepage.ui \
    register.ui \
    profileedit.ui \
    friend.ui \
    addfriend.ui \
    viewchats.ui \
    createchat.ui \
    chat.ui
