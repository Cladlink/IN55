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
////! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(verticesPlane, nbrVertices * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indicesPlane, nbrIndices * sizeof(GLushort));

//! [1]
}

//! [2]
void Plane::drawGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int colorLocation = program->attributeLocation("color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int uvLocation = program->attributeLocation("vertexUV");
    program->enableAttributeArray(uvLocation);
    program->setAttributeBuffer(uvLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, nbrIndices, GL_UNSIGNED_SHORT, 0);
}

void Plane::update(QOpenGLShaderProgram *program, QVector3D _color){

    arrayBuf.bind();
    for (int i=0; i<nbrVertices-1; i++) {
        verticesPlane[i].color = _color;
    }

    arrayBuf.allocate(verticesPlane, nbrVertices * sizeof(VertexData));

    indexBuf.bind();
    indexBuf.allocate(indicesPlane, nbrIndices * sizeof(GLushort));

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int colorLocation = program->attributeLocation("color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int normalLocation = program->attributeLocation("normal");
    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, nbrIndices, GL_UNSIGNED_SHORT, 0);
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



