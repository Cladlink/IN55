#include "Torus.h"

Torus::Torus(uint _tesselation) {

    this->tesselation = _tesselation;
    initializeOpenGLFunctions();

    ShapeData torus = IGeometryEngine::makeTorus(this->tesselation);

    verticesTorus = torus.vertices;
    indicesTorus = torus.indices;

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
    // Initializes cube geometry and transfers it to VBOs
    nbrIndices = torus.numIndices;
    nbrVertices = torus.numVertices;
    initGeometry();
}

Torus::~Torus()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]

void Torus::initGeometry()
{
    IGeometryEngine::initGeometry(verticesTorus,indicesTorus);
}

//! [2]
void Torus::drawGeometry(QOpenGLShaderProgram *program)
{
    IGeometryEngine::drawGeometry(program);
}

void Torus::update(QOpenGLShaderProgram *program,QVector3D _color,
                  QMatrix4x4 _modelToProjectionMatrix, QMatrix4x4 _shapeModelToWorldMatrix,
                  QVector3D _position){

    IGeometryEngine::update(program,verticesTorus,indicesTorus,_color,_modelToProjectionMatrix,_shapeModelToWorldMatrix,_position);
}
