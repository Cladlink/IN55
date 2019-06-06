#include "Cube.h"

Cube::Cube() {

    initializeOpenGLFunctions();

    ShapeData cube = IGeometryEngine::makeCube();

    verticesCube = cube.vertices;
    indicesCube = cube.indices;

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
    // Initializes cube geometry and transfers it to VBOs
    nbrIndices = cube.numIndices;
    nbrVertices = cube.numVertices;
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
                  QVector3D _position){

    IGeometryEngine::update(program,verticesCube,indicesCube,_color,_modelToProjectionMatrix,_shapeModelToWorldMatrix,_position);
}



//! [2]



