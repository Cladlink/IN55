#include "Sphere.h"

Sphere::Sphere(uint _tesselation) {

    this->tesselation = _tesselation;
    initializeOpenGLFunctions();

    ShapeData sphere = IGeometryEngine::makeSphere(tesselation);
    ShapeData sphereNormal = IGeometryEngine::generateNormals(sphere);

    verticesSphere = sphere.vertices;
    indicesSphere = sphere.indices;
    verticesSphereNormal = sphereNormal.vertices;
    indicesSphereNormal = sphereNormal.indices;

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
    // Initializes cube geometry and transfers it to VBOs
    nbrIndices = sphere.numIndices;
    nbrVertices = sphere.numVertices;
    nbrIndicesNormal = sphereNormal.numIndices;
    nbrVerticesNormal = sphereNormal.numVertices;
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
                  QVector3D _position, QQuaternion _rotation, bool _showNormal, int _hideShapeNumber){

    if (_position == QVector3D()) {
        _position = QVector3D(3.,3.,0.);
    }
    IGeometryEngine::update(program,verticesSphere,indicesSphere,verticesSphereNormal,indicesSphereNormal,
                            _color,_modelToProjectionMatrix,_shapeModelToWorldMatrix,
                            _position,_rotation,_showNormal, _hideShapeNumber);
}
