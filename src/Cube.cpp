#include "Cube.h"

Cube::Cube()
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
    // Initializes cube geometry and transfers it to VBOs
    nbrIndices = 36;
    nbrVertices = 72;
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
////! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(verticesCube, nbrVertices * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indicesCube, nbrIndices * sizeof(GLushort));

//! [1]
}

//! [2]
void Cube::drawGeometry(QOpenGLShaderProgram *program)
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

void Cube::update(QOpenGLShaderProgram *program, QVector3D _color){

    arrayBuf.bind();
    for (int i=0; i<nbrVertices-1; i++) {
        verticesCube[i].color = _color;
    }

    arrayBuf.allocate(verticesCube, nbrVertices * sizeof(VertexData));

    indexBuf.bind();
    indexBuf.allocate(indicesCube, nbrIndices * sizeof(GLushort));

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

//! [2]



