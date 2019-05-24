 #include "pyramide.h"

Pyramide::VertexData verticesPyramide[] = {
    {QVector3D(0.f, 1.f, 0.f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.5f, 1.0f)}, //0 -> 0
    {QVector3D(0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 0.0f)}, //2 -> 1
    {QVector3D(-0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 0.0f)}, //1 -> 2

    {QVector3D(0.f, 1.f, 0.f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.5f, 1.0f)}, //0 -> 3
    {QVector3D(-0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 0.0f)}, //4 -> 4
    {QVector3D(0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 0.0f)}, //3 -> 5

    {QVector3D(0.f, 1.f, 0.f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.5f, 1.0f)}, //0 -> 6
    {QVector3D(0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 0.0f)}, //3 -> 7
    {QVector3D(0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 0.0f)}, //2 -> 8

    {QVector3D(0.f, 1.f, 0.f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.5f, 1.0f)}, //0 -> 9
    {QVector3D(-0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 0.0f)}, //1 -> 10
    {QVector3D(-0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 0.0f)}, //4 -> 11

    {QVector3D(-0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 0.0f)}, //1 -> 12
    {QVector3D(0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 0.0f)}, //2 -> 13
    {QVector3D(0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 1.0f)}, //3 -> 14
    {QVector3D(-0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 1.0f)}, //4 -> 15

    /*{QVector3D(0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f)},
    {QVector3D(0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f)},
    {QVector3D(-0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f)},*/


    /*{QVector3D(-0.5f, 0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f)},
    {QVector3D(0.5f, 0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f)},
    {QVector3D(0.5f, 0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f)},
    {QVector3D(-0.5f, 0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f)},*/
};

GLushort indicesPyramide[] = {
    0,1,2,
    3,4,5,
    6,7,8,
    9,10,11,
    15,12,13,
    13,14,15
};

Pyramide::Pyramide()
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
    // Initializes cube geometry and transfers it to VBOs
    nbrIndices = 18;
    nbrVertices = 16;

    initGeometry();
}

Pyramide::~Pyramide()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]

void Pyramide::initGeometry()
{
////! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(verticesPyramide, nbrVertices * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indicesPyramide, nbrIndices * sizeof(GLushort));
//! [1]
}

//! [2]
void Pyramide::drawGeometry(QOpenGLShaderProgram *program)
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

void Pyramide::update(){
        /*vertices[0] = {QVector3D(-0.5f, -0.5f, 0.5f), QVector3D(0.0f, 1.0f,0.0f)};
        vertices[1] = {QVector3D(0.5f, -0.5f, 0.5f), QVector3D(0.0f, 1.0f,0.0f)};
        vertices[2] = {QVector3D(0.5f, -0.5f, -0.5f), QVector3D(0.0f, 1.0f,0.0f)};
        vertices[3] = {QVector3D(-0.5f, -0.5f, -0.5f), QVector3D(0.0f, 1.0f,0.0f)};
        vertices[4] = {QVector3D(-0.5f, 0.5f, 0.5f), QVector3D(0.0f, 1.0f,0.0f)};
        vertices[5] = {QVector3D(0.5f, 0.5f, 0.5f), QVector3D(0.0f, 1.0f,0.0f)};
        vertices[6] = {QVector3D(0.5f, 0.5f, -0.5f), QVector3D(0.0f, 1.0f,0.0f)};
        vertices[7] = {QVector3D(-0.5f, 0.5f, -0.5f), QVector3D(0.0f, 1.0f,0.0f)};*/
}
//! [2]



