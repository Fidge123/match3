TEMPLATE = app

QT += core widgets

CONFIG += c++11

SOURCES += main.cpp \
    grid.cpp \
    tile.cpp \
    game.cpp

RESOURCES += \
    assets.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    grid.h \
    tile.h \
    game.h
