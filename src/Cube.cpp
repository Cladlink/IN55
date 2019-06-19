#include "Cube.h"

Cube::Cube() {

    initializeOpenGLFunctions();

    ShapeData cube = IGeometryEngine::makeCube();
    ShapeData cubeNormal = IGeometryEngine::generateNormals(cube);
    verticesCube = cube.vertices;
    indicesCube = cube.indices;
    verticesCubeNormal = cubeNormal.vertices;
    indicesCubeNormal = cubeNormal.indices;

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
    // Initializes cube geometry and transfers it to VBOs
    nbrIndices = cube.numIndices;
    nbrVertices = cube.numVertices;
    nbrIndicesNormal = cubeNormal.numIndices;
    nbrVerticesNormal = cubeNormal.numVertices;
    initGeometry();
}

Cube::~Cube()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]

void Cube::initGeometry()
{
    IGeometryEngine::initGeometry(verticesCube,indicesCube);
}

//! [2]
void Cube::drawGeometry(QOpenGLShaderProgram *program)
{
    IGeometryEngine::drawGeometry(program);
}

void Cube::update(QOpenGLShaderProgram *program,QVector3D _color,
                  QMatrix4x4 _modelToProjectionMatrix, QMatrix4x4 _shapeModelToWorldMatrix,
                  QVector3D _position, QQuaternion _rotation, bool _showNormal, int _hideShapeNumber){

    if (_position == QVector3D()) {
        _position = QVector3D(2.,2.,-3.);
    }
    IGeometryEngine::update(program,verticesCube,indicesCube,verticesCubeNormal,indicesCubeNormal,
                            _color,_modelToProjectionMatrix,_shapeModelToWorldMatrix,
                            _position,_rotation,_showNormal, _hideShapeNumber);
}

//! [2]



