#-------------------------------------------------
#
# Project created by QtCreator 2016-09-08T16:26:56
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PostOffice_db
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp \
    mainwindow.cpp \
    authorizationdialog.cpp \
    idAttachmentDelegat.cpp \
    NoEditColumnDelegate.cpp \
    SqlTypeModel.cpp \
    simplecrypt.cpp

HEADERS  += \
    mainwindow.h \
    authorizationdialog.h \
    SqlTypeModel.h \
    idAttachmentDelegat.h \
    NoEditColumnDelegate.h \
    simplecrypt.h

FORMS    += \
    mainwindow.ui \
    authorizationdialog.ui
