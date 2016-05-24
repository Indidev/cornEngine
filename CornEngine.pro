#-------------------------------------------------
#
# Project created by QtCreator 2016-05-14T17:41:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cornEngine
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += cornEngine.cpp\
        view/Gui.cpp \
        view/widgets/LayeredWidget.cpp \
        control/io/Input.cpp \
        control/io/Output.cpp \
    model/GameMap.cpp \
    control/util/Log.cpp \
    model/Spirit.cpp \
    control/res/SpiritManager.cpp \
    control/res/GameMapManager.cpp \
    control/render/DrawableStack.cpp \
    control/render/Camera.cpp \
    model/MovableSpirit.cpp \
    model/interface/Collisionable.cpp \
    model/primitives/Triangle.cpp \
    model/primitives/Point.cpp \
    model/primitives/TriangleFactory.cpp \
    control/util/Math.cpp

HEADERS  += view/Gui.h \
        view/widgets/LayeredWidget.h \
        control/io/Input.h \
        control/io/Output.h \
    model/GameMap.h \
    control/util/Log.h \
    model/Spirit.h \
    control/res/SpiritManager.h \
    control/res/GameMapManager.h \
    model/Drawable.h \
    control/render/DrawableStack.h \
    control/render/Camera.h \
    model/MovableSpirit.h \
    model/interface/Collisionable.h \
    model/primitives/Triangle.h \
    model/primitives/Point.h \
    model/primitives/TriangleFactory.h \
    control/util/Math.h

FORMS    += view/Gui.ui

# Define copy command for linux and windows
QMAKE_COPY = cp -rf
Win32:QMAKE_COPY = copy /y

# cp(src, dest) returns the copy command
defineReplace(cp) {
    SDIR = $$PWD/$$1
    DDIR = $$OUT_PWD/$$2

    # Replace slashes in paths with backslashes for Windows
    win32:DDIR ~= s,/,\\,g
    win32:SDIR ~= s,/,\\,g

    return($$QMAKE_COPY $$SDIR $$DDIR;)
}
cpFiles.commands += $$cp(res, ./)

#Add dependencies to first
first.depends += cpFiles

#add dependencies to makefile
QMAKE_EXTRA_TARGETS += first cpFiles
