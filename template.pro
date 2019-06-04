QT       += core gui widgets

TARGET = template
TEMPLATE = app

SOURCES += \
    src/DebugSlider.cpp \
    src/ShapeGenerator.cpp \
    src/camera.cpp \
    src/cube.cpp \
    src/igeometryengine.cpp \
    src/main.cpp \
    src/mainwidget.cpp \
    src/frame.cpp \
    src/parameter.cpp \
    src/pyramide.cpp \
    src/colortextedit.cpp \
    src/shape.cpp

HEADERS += \
    src/DebugSlider.h \
    src/Light.h \
    src/ShapeData.h \
    src/ShapeGenerator.h \
    src/TeapotData.h \
    src/Vertex.h \
    src/camera.h \
    src/cube.h \
    src/igeometryengine.h \
    src/mainwidget.h \
    src/frame.h \
    src/parameter.h \
    src/pyramide.h \
    colortextedit.h \
    src/colortextedit.h \
    src/shape.h

RESOURCES += \
    ressources/shaders.qrc \

DISTFILES +=
