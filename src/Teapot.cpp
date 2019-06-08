#include "Teapot.h"

Teapot::Teapot(uint _tesselation, const QMatrix4x4 &_lidTransform) {

    this->tesselation = _tesselation;
    this->lidTransform = &_lidTransform;
    initializeOpenGLFunctions();

    ShapeData teapot = IGeometryEngine::makeTeapot(tesselation,*lidTransform);

    verticesTeapot = teapot.vertices;
    indicesTeapot = teapot.indices;

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
    // Initializes cube geometry and transfers it to VBOs
    nbrIndices = teapot.numIndices;
    nbrVertices = teapot.numVertices;
    initGeometry();
}

Teapot::~Teapot()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]

void Teapot::initGeometry()
{
    IGeometryEngine::initGeometry(verticesTeapot,indicesTeapot);
}

//! [2]
void Teapot::drawGeometry(QOpenGLShaderProgram *program)
{
    IGeometryEngine::drawGeometry(program);
}

void Teapot::update(QOpenGLShaderProgram *program,QVector3D _color,
                  QMatrix4x4 _modelToProjectionMatrix, QMatrix4x4 _shapeModelToWorldMatrix,
                  QVector3D _position, QQuaternion _rotation){

    IGeometryEngine::update(program,verticesTeapot,indicesTeapot,_color,_modelToProjectionMatrix,_shapeModelToWorldMatrix,_position,_rotation);
}

//! [2]



