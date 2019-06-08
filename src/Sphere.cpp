#include "Sphere.h"

Sphere::Sphere(uint _tesselation) {

    this->tesselation = _tesselation;
    initializeOpenGLFunctions();

    ShapeData sphere = IGeometryEngine::makeSphere(tesselation);

    verticesSphere = sphere.vertices;
    indicesSphere = sphere.indices;

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
    // Initializes cube geometry and transfers it to VBOs
    nbrIndices = sphere.numIndices;
    nbrVertices = sphere.numVertices;
    initGeometry();
}

Sphere::~Sphere()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]

void Sphere::initGeometry()
{
    IGeometryEngine::initGeometry(verticesSphere,indicesSphere);
}

//! [2]
void Sphere::drawGeometry(QOpenGLShaderProgram *program)
{
    IGeometryEngine::drawGeometry(program);
}

void Sphere::update(QOpenGLShaderProgram *program,QVector3D _color,
                  QMatrix4x4 _modelToProjectionMatrix, QMatrix4x4 _shapeModelToWorldMatrix,
                  QVector3D _position, QQuaternion _rotation){

    IGeometryEngine::update(program,verticesSphere,indicesSphere,_color,_modelToProjectionMatrix,_shapeModelToWorldMatrix,_position,_rotation);
}
