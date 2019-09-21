DESTDIR = release

BUILD_DLL {
    TEMPLATE = lib
    TARGET = serial2tcp
    INCLUDEPATH += .

    HEADERS += serial2tcp.h
    SOURCES += serial2tcp.cpp
}

BUILD_APP {
    TEMPLATE = app
    TARGET = serial2tcp
    INCLUDEPATH += .

    HEADERS += serial2tcp.h
    SOURCES += main.cpp
    LIBS    += $$DESTDIR/serial2tcp.dll
}

CONFIG += console
CONFIG += release
QT -= gui
QT += serialport network


OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
