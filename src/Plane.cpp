#include "Plane.h"

Plane::Plane(uint _dimensions)
{
    initializeOpenGLFunctions();
    this->dimensions = _dimensions;

    ShapeData ret = IGeometryEngine::makePlaneVerts(dimensions);
    ShapeData ret2 = IGeometryEngine::makePlaneIndices(dimensions);
    ret.numIndices = ret2.numIndices;
    ret.indices = ret2.indices;
    ShapeData planeNormal = IGeometryEngine::generateNormals(ret);

    verticesPlane = ret.vertices;
    indicesPlane = ret.indices;
    verticesPlaneNormal = planeNormal.vertices;
    indicesPlaneNormal = planeNormal.indices;

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
    // Initializes cube geometry and transfers it to VBOs
    nbrIndices = ret.numIndices;
    nbrVertices = ret.numVertices;
    nbrIndicesNormal = planeNormal.numIndices;
    nbrVerticesNormal = planeNormal.numVertices;
    initGeometry();

}

Plane::~Plane()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]

void Plane::initGeometry()
{
    IGeometryEngine::initGeometry(verticesPlane,indicesPlane);
}

//! [2]
void Plane::drawGeometry(QOpenGLShaderProgram *program)
{
    IGeometryEngine::drawGeometry(program);
}

void Plane::update(QOpenGLShaderProgram *program,QVector3D _color,
                   QMatrix4x4 _modelToProjectionMatrix, QMatrix4x4 _shapeModelToWorldMatrix,
                   QVector3D _position, QQuaternion _rotation, bool _showNormal, int _hideShapeNumber){

    IGeometryEngine::update(program,verticesPlane,indicesPlane,verticesPlaneNormal,indicesPlaneNormal,
                            _color,_modelToProjectionMatrix,_shapeModelToWorldMatrix,
                            _position,_rotation, _showNormal, _hideShapeNumber);
}
