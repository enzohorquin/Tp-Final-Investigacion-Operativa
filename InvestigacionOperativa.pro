#-------------------------------------------------
#
# Project created by QtCreator 2015-11-18T08:36:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InvestigacionOperativa
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tablerohorarios.cpp \
    restriccion.cpp \
    conjuntomat.cpp \
    nuevaventana.cpp \
    materia.cpp \
    solucion.cpp \
    matriz.cpp \
    form.cpp \
    horariodia.cpp \
    aula.cpp

HEADERS  += mainwindow.h \
    tablerohorarios.h \
    restriccion.h \
    conjuntomat.h \
    nuevaventana.h \
    materia.h \
    solucion.h \
    matriz.h \
    form.h \
    horariodia.h \
    aula.h

FORMS    += mainwindow.ui \
    nuevaventana.ui \
    form.ui

RESOURCES += \
    imagenes.qrc

RC_ICONS = images.ico
