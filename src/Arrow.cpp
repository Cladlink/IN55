#include "Arrow.h"

Arrow::Arrow() {

    initializeOpenGLFunctions();

    ShapeData arrow = IGeometryEngine::makeArrow();

    verticesArrow = arrow.vertices;
    indicesArrow = arrow.indices;

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
    // Initializes cube geometry and transfers it to VBOs
    nbrIndices = arrow.numIndices;
    nbrVertices = arrow.numVertices;
    initGeometry();
}

Arrow::~Arrow()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]

void Arrow::initGeometry()
{
    IGeometryEngine::initGeometry(verticesArrow,indicesArrow);
}

//! [2]
void Arrow::drawGeometry(QOpenGLShaderProgram *program)
{
    IGeometryEngine::drawGeometry(program);
}

void Arrow::update(QOpenGLShaderProgram *program,QVector3D _color,
                  QMatrix4x4 _modelToProjectionMatrix, QMatrix4x4 _shapeModelToWorldMatrix,
                  QVector3D _position){

    IGeometryEngine::update(program,verticesArrow,indicesArrow,_color,_modelToProjectionMatrix,_shapeModelToWorldMatrix,_position);
}

//! [2]



