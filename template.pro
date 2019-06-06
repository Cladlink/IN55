QT       += opengl core gui widgets

TARGET = template
TEMPLATE = app

SOURCES += \
    src/Arrow.cpp \
    src/Camera.cpp \
    src/Colortextedit.cpp \
    src/Cube.cpp \
    src/DebugSlider.cpp \
    src/Frame.cpp \
    src/IGeometryEngine.cpp \
    src/MainWidget.cpp \
    src/Parameter.cpp \
    src/Plane.cpp \
    src/Pyramide.cpp \
    src/Shape.cpp \
    src/ShapeGenerator.cpp \
    src/Sphere.cpp \
    src/Teapot.cpp \
    src/Torus.cpp \
    src/main.cpp

HEADERS += \
    src/Arrow.h \
    src/Camera.h \
    src/Colortextedit.h \
    src/Cube.h \
    src/DebugSlider.h \
    src/Frame.h \
    src/IGeometryEngine.h \
    src/Light.h \
    src/MainWidget.h \
    src/Parameter.h \
    src/Plane.h \
    src/Pyramide.h \
    src/Shape.h \
    src/ShapeData.h \
    src/ShapeGenerator.h \
    src/Sphere.h \
    src/Teapot.h \
    src/TeapotData.h \
    src/Torus.h \
    src/Vertex.h \
    colortextedit.h

RESOURCES += \
    ressources/shaders.qrc \

DISTFILES += \
    ressources/fShaderThroughCode.glsl \
    ressources/vShaderThroughCode.glsl
