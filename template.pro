QT       += core gui widgets

TARGET = template
TEMPLATE = app

SOURCES += \
    src/cube.cpp \
    src/igeometryengine.cpp \
    src/main.cpp \
    src/mainwidget.cpp \
    src/frame.cpp \
    src/parameter.cpp \
    src/pyramide.cpp

HEADERS += \
    src/cube.h \
    src/igeometryengine.h \
    src/mainwidget.h \
    src/frame.h \
    src/parameter.h \
    src/pyramide.h

RESOURCES += \
    ressources/shaders.qrc \
