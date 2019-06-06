#include "Plane.h"

Plane::Plane(uint _dimensions)
{
    initializeOpenGLFunctions();
    this->dimensions = _dimensions;

    ShapeData ret = makePlaneVerts(dimensions);
    ShapeData ret2 = makePlaneIndices(dimensions);
    ret.numIndices = ret2.numIndices;
    ret.indices = ret2.indices;

    verticesPlane = ret.vertices;
    indicesPlane = ret.indices;

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
    // Initializes cube geometry and transfers it to VBOs
    nbrIndices = ret.numIndices;
    nbrVertices = ret.numVertices;
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
                   QVector3D _position){

    IGeometryEngine::update(program,verticesPlane,indicesPlane,_color,_modelToProjectionMatrix,_shapeModelToWorldMatrix,_position);
}

QVector3D Plane::randomColor()
{
    QVector3D ret;
    ret.setX(rand() / (float)RAND_MAX);
    ret.setY(rand() / (float)RAND_MAX);
    ret.setZ(rand() / (float)RAND_MAX);
    return ret;
}

ShapeData Plane::makePlaneVerts(uint dimensions)
{
    ShapeData ret;
    ret.numVertices = dimensions * dimensions;
    int half = dimensions / 2;
    ret.vertices = new Vertex[ret.numVertices];
    for (int i = 0; i < dimensions; i++)
    {
        for (int j = 0; j < dimensions; j++)
        {
            Vertex& thisVert = ret.vertices[i * dimensions + j];
            thisVert.position.setX(j - half);
            thisVert.position.setZ(i - half);
            thisVert.position.setY(0);
            thisVert.normal = QVector3D(0.0f, 1.0f, 0.0f);
            thisVert.color = Plane::randomColor();
        }
    }
    return ret;
}

ShapeData Plane::makePlaneIndices(uint dimensions)
{
    ShapeData ret;
    ret.numIndices = (dimensions - 1) * (dimensions - 1) * 2 * 3; // 2 triangles per square, 3 indices per triangle
    ret.indices = new unsigned short[ret.numIndices];
    int runner = 0;
    for (int row = 0; row < dimensions - 1; row++)
    {
        for (int col = 0; col < dimensions - 1; col++)
        {
            ret.indices[runner++] = dimensions * row + col;
            ret.indices[runner++] = dimensions * row + col + dimensions;
            ret.indices[runner++] = dimensions * row + col + dimensions + 1;

            ret.indices[runner++] = dimensions * row + col;
            ret.indices[runner++] = dimensions * row + col + dimensions + 1;
            ret.indices[runner++] = dimensions * row + col + 1;
        }
    }
    assert(runner = ret.numIndices);
    return ret;
}



