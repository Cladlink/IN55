#include "cube.h"

/*Cube::VertexData verticesCube[] = {
    {QVector3D(-0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 1.0f)}, //0
    {QVector3D(0.5f, -0.5f, 0.5f), QVector3D(0.0f, 1.0f,0.0f), QVector2D(1.0f, 1.0f)}, //1
    {QVector3D(0.5f, 0.5f, 0.5f), QVector3D(1.0f, 0.0f,1.0f), QVector2D(1.0f, 0.0f)}, //2
    {QVector3D(-0.5f, 0.5f, 0.5f), QVector3D(0.0f, 0.0f,1.0f), QVector2D(0.0f, 0.0f)}, //3

    {QVector3D(-0.5f, -0.5f, -0.5f), QVector3D(0.0f, 0.0f,1.0f), QVector2D(1.0f, 1.0f)}, //4
    {QVector3D(0.5f, -0.5f, -0.5f), QVector3D(1.0f, 1.0f,0.0f), QVector2D(0.0f, 1.0f)}, //5
    {QVector3D(0.5f, 0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 0.0f)}, //6
    {QVector3D(-0.5f, 0.5f, -0.5f), QVector3D(1.0f, 1.0f,1.0f), QVector2D(1.0f, 0.0f)}, //7

    {QVector3D(-0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 0.0f)}, //0 -> 8
    {QVector3D(0.5f, -0.5f, 0.5f), QVector3D(0.0f, 1.0f,0.0f), QVector2D(1.0f, 0.0f)}, //1 -> 9
    {QVector3D(0.5f, -0.5f, -0.5f), QVector3D(1.0f, 1.0f,0.0f), QVector2D(1.0f, 1.0f)}, //4 -> 10
    {QVector3D(-0.5f, -0.5f, -0.5f), QVector3D(0.0f, 0.0f,1.0f), QVector2D(0.0f, 1.0f)}, //5 -> 11

    {QVector3D(-0.5f, 0.5f, 0.5f), QVector3D(0.0f, 0.0f,1.0f), QVector2D(0.0f, 1.0f)}, //2 -> 12
    {QVector3D(0.5f, 0.5f, 0.5f), QVector3D(1.0f, 0.0f,1.0f), QVector2D(1.0f, 1.0f)}, //3 -> 13
    {QVector3D(0.5f, 0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 0.0f)}, //6 -> 14
    {QVector3D(-0.5f, 0.5f, -0.5f), QVector3D(1.0f, 1.0f,1.0f), QVector2D(0.0f, 0.0f)}, //7 -> 15

    {QVector3D(0.5f, -0.5f, 0.5f), QVector3D(0.0f, 1.0f,0.0f), QVector2D(0.0f, 1.0f)}, //1 -> 16
    {QVector3D(0.5f, 0.5f, 0.5f), QVector3D(1.0f, 0.0f,1.0f), QVector2D(0.0f, 0.0f)}, //2 -> 17
    {QVector3D(0.5f, -0.5f, -0.5f), QVector3D(1.0f, 1.0f,0.0f), QVector2D(1.0f, 1.0f)}, //5 -> 18
    {QVector3D(0.5f, 0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 0.0f)}, //6 -> 19

    {QVector3D(-0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 1.0f)}, //0 -> 20
    {QVector3D(-0.5f, 0.5f, 0.5f), QVector3D(0.0f, 0.0f,1.0f), QVector2D(0.0f, 0.0f)}, //3 -> 21
    {QVector3D(-0.5f, -0.5f, -0.5f), QVector3D(0.0f, 0.0f,1.0f), QVector2D(1.0f, 1.0f)}, //4 -> 22
    {QVector3D(-0.5f, 0.5f, -0.5f), QVector3D(1.0f, 1.0f,1.0f), QVector2D(1.0f, 0.0f)}, //7 -> 23
};

GLushort indicesCube[] = {
    0,1,2,
    0,2,3,

    5,4,7,
    5,7,6,

    11,10,9,
    11,9,8,

    12,13,14,
    12,14,15,

    16,18,19,
    16,19,17,

    22,20,21,
    22,21,23
};
*/

Cube::Cube()
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
    // Initializes cube geometry and transfers it to VBOs
    nbrIndices = 36;
    nbrVertices = 24;
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

//void Cube::update(QOpenGLShaderProgram *program, QVector3D _color){

//    arrayBuf.bind();
//    for (int i=0; i<nbrVertices-1; i++) {
//        verticesCube[i].color = _color;
//    }

//    arrayBuf.allocate(verticesCube, nbrVertices * sizeof(VertexData));

//    indexBuf.bind();
//    indexBuf.allocate(indicesCube, nbrIndices * sizeof(GLushort));

//    // Offset for position
//    quintptr offset = 0;

//    // Tell OpenGL programmable pipeline how to locate vertex position data
//    int vertexLocation = program->attributeLocation("position");
//    program->enableAttributeArray(vertexLocation);
//    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

//    // Offset for texture coordinate
//    offset += sizeof(QVector3D);

//    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
//    int colorLocation = program->attributeLocation("color");
//    program->enableAttributeArray(colorLocation);
//    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

//    offset += sizeof(QVector3D);

//    int uvLocation = program->attributeLocation("vertexUV");
//    program->enableAttributeArray(uvLocation);
//    program->setAttributeBuffer(uvLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

//    // Draw cube geometry using indices from VBO 1
//    glDrawElements(GL_TRIANGLES, nbrIndices, GL_UNSIGNED_SHORT, 0);
//}

QVector<QVector3D> Cube::getPosition() {
    QVector<QVector3D> retour;
    for (int i=0; i<nbrVertices-1; i++) {
        retour.append(QVector3D(verticesCube[i].position));
    }
    return retour;
}
//! [2]



