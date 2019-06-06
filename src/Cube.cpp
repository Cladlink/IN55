#include "Cube.h"

Cube::Cube() {

    initializeOpenGLFunctions();

    ShapeData cube = makeCube();

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

ShapeData Cube::makeCube() {
    ShapeData ret;
    Vertex stackVerts[] =
    {
        QVector3D(-1.0f, +1.0f, +1.0f),  // 0
        QVector3D(+1.0f, +0.0f, +0.0f),	// Color
        QVector3D(+0.0f, +1.0f, +0.0f),  // Normal
        QVector3D(+1.0f, +1.0f, +1.0f),  // 1
        QVector3D(+0.0f, +1.0f, +0.0f),	// Color
        QVector3D(+0.0f, +1.0f, +0.0f),  // Normal
        QVector3D(+1.0f, +1.0f, -1.0f),  // 2
        QVector3D(+0.0f, +0.0f, +1.0f),  // Color
        QVector3D(+0.0f, +1.0f, +0.0f),  // Normal
        QVector3D(-1.0f, +1.0f, -1.0f),  // 3
        QVector3D(+1.0f, +1.0f, +1.0f),  // Color
        QVector3D(+0.0f, +1.0f, +0.0f),  // Normal

        QVector3D(-1.0f, +1.0f, -1.0f),  // 4
        QVector3D(+1.0f, +0.0f, +1.0f),  // Color
        QVector3D(+0.0f, +0.0f, -1.0f),  // Normal
        QVector3D(+1.0f, +1.0f, -1.0f),  // 5
        QVector3D(+0.0f, +0.5f, +0.2f),  // Color
        QVector3D(+0.0f, +0.0f, -1.0f),  // Normal
        QVector3D(+1.0f, -1.0f, -1.0f),  // 6
        QVector3D(+0.8f, +0.6f, +0.4f),  // Color
        QVector3D(+0.0f, +0.0f, -1.0f),  // Normal
        QVector3D(-1.0f, -1.0f, -1.0f),  // 7
        QVector3D(+0.3f, +1.0f, +0.5f),  // Color
        QVector3D(+0.0f, +0.0f, -1.0f),  // Normal

        QVector3D(+1.0f, +1.0f, -1.0f),  // 8
        QVector3D(+0.2f, +0.5f, +0.2f),  // Color
        QVector3D(+1.0f, +0.0f, +0.0f),  // Normal
        QVector3D(+1.0f, +1.0f, +1.0f),  // 9
        QVector3D(+0.9f, +0.3f, +0.7f),  // Color
        QVector3D(+1.0f, +0.0f, +0.0f),  // Normal
        QVector3D(+1.0f, -1.0f, +1.0f),  // 10
        QVector3D(+0.3f, +0.7f, +0.5f),  // Color
        QVector3D(+1.0f, +0.0f, +0.0f),  // Normal
        QVector3D(+1.0f, -1.0f, -1.0f),  // 11
        QVector3D(+0.5f, +0.7f, +0.5f),  // Color
        QVector3D(+1.0f, +0.0f, +0.0f),  // Normal

        QVector3D(-1.0f, +1.0f, +1.0f),  // 12
        QVector3D(+0.7f, +0.8f, +0.2f),  // Color
        QVector3D(-1.0f, +0.0f, +0.0f),  // Normal
        QVector3D(-1.0f, +1.0f, -1.0f),  // 13
        QVector3D(+0.5f, +0.7f, +0.3f),  // Color
        QVector3D(-1.0f, +0.0f, +0.0f),  // Normal
        QVector3D(-1.0f, -1.0f, -1.0f),  // 14
        QVector3D(+0.4f, +0.7f, +0.7f),  // Color
        QVector3D(-1.0f, +0.0f, +0.0f),  // Normal
        QVector3D(-1.0f, -1.0f, +1.0f),  // 15
        QVector3D(+0.2f, +0.5f, +1.0f),  // Color
        QVector3D(-1.0f, +0.0f, +0.0f),  // Normal

        QVector3D(+1.0f, +1.0f, +1.0f),  // 16
        QVector3D(+0.6f, +1.0f, +0.7f),  // Color
        QVector3D(+0.0f, +0.0f, +1.0f),  // Normal
        QVector3D(-1.0f, +1.0f, +1.0f),  // 17
        QVector3D(+0.6f, +0.4f, +0.8f),  // Color
        QVector3D(+0.0f, +0.0f, +1.0f),  // Normal
        QVector3D(-1.0f, -1.0f, +1.0f),  // 18
        QVector3D(+0.2f, +0.8f, +0.7f),  // Color
        QVector3D(+0.0f, +0.0f, +1.0f),  // Normal
        QVector3D(+1.0f, -1.0f, +1.0f),  // 19
        QVector3D(+0.2f, +0.7f, +1.0f),  // Color
        QVector3D(+0.0f, +0.0f, +1.0f),  // Normal

        QVector3D(+1.0f, -1.0f, -1.0f),  // 20
        QVector3D(+0.8f, +0.3f, +0.7f),  // Color
        QVector3D(+0.0f, -1.0f, +0.0f),  // Normal
        QVector3D(-1.0f, -1.0f, -1.0f),  // 21
        QVector3D(+0.8f, +0.9f, +0.5f),  // Color
        QVector3D(+0.0f, -1.0f, +0.0f),  // Normal
        QVector3D(-1.0f, -1.0f, +1.0f),  // 22
        QVector3D(+0.5f, +0.8f, +0.5f),  // Color
        QVector3D(+0.0f, -1.0f, +0.0f),  // Normal
        QVector3D(+1.0f, -1.0f, +1.0f),  // 23
        QVector3D(+0.9f, +1.0f, +0.2f),  // Color
        QVector3D(+0.0f, -1.0f, +0.0f),  // Normal
    };

    ret.numVertices = NUM_ARRAY_ELEMENTS(stackVerts);
    ret.vertices = new Vertex[ret.numVertices];
    memcpy(ret.vertices, stackVerts, sizeof(stackVerts));

    unsigned short stackIndices[] = {
        0,   1,  2,  0,  2,  3, // Top
        4,   5,  6,  4,  6,  7, // Front
        8,   9, 10,  8, 10, 11, // Right
        12, 13, 14, 12, 14, 15, // Left
        16, 17, 18, 16, 18, 19, // Back
        20, 22, 21, 20, 23, 22, // Bottom
    };
    ret.numIndices = NUM_ARRAY_ELEMENTS(stackIndices);
    ret.indices = new GLushort[ret.numIndices];
    memcpy(ret.indices, stackIndices, sizeof(stackIndices));

    return ret;
}

//! [2]



