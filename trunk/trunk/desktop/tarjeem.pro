QT       += widgets core gui sql network

TARGET = Tarjeem
TEMPLATE = app

RESOURCES = $$PWD/resources/tarjeem.qrc

SOURCES +=  main.cpp \
            tarjeem.cpp \
            content.cpp

HEADERS  += tarjeem.h \
            content.h
