TEMPLATE = app
TARGET = serial2tcp
INCLUDEPATH += .

HEADERS += serial2tcp.h
SOURCES += main.cpp serial2tcp.cpp

CONFIG += console
QT -= gui
QT += serialport network