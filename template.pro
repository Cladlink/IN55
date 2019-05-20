QT       += core gui widgets

TARGET = template
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/mainwidget.cpp \
    src/geometryengine.cpp \
    src/frame.cpp \
    src/parameter.cpp

HEADERS += \
    src/mainwidget.h \
    src/geometryengine.h \
    src/frame.h \
    src/parameter.h

RESOURCES += \
    ressources/shaders.qrc \
