 #include "Pyramide.h"

Pyramide::Pyramide()
{
    initializeOpenGLFunctions();

    ShapeData pyramide = makePyramide();

    verticesPyramide = pyramide.vertices;
    indicesPyramide = pyramide.indices;

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
    // Initializes cube geometry and transfers it to VBOs
    nbrIndices = pyramide.numIndices;
    nbrVertices = pyramide.numVertices;
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
    IGeometryEngine::initGeometry(verticesPyramide,indicesPyramide);
}

//! [2]
void Pyramide::drawGeometry(QOpenGLShaderProgram *program)
{
    IGeometryEngine::drawGeometry(program);
}

void Pyramide::update(QOpenGLShaderProgram *program,QVector3D _color,
                      QMatrix4x4 _modelToProjectionMatrix, QMatrix4x4 _shapeModelToWorldMatrix,
                      QVector3D _position){

    IGeometryEngine::update(program,verticesPyramide,indicesPyramide,_color,_modelToProjectionMatrix,_shapeModelToWorldMatrix,_position);
}

ShapeData Pyramide::makePyramide()
{
    ShapeData ret;

    Vertex myPyr[] =
    {
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
        {QVector3D(-0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 1.0f)}
    };
    ret.numVertices = NUM_ARRAY_ELEMENTS(myPyr);
    ret.vertices = new Vertex[ret.numVertices];
    memcpy(ret.vertices, myPyr, sizeof(myPyr));

    GLushort indices[] = { 0,1,2,
                           3,4,5,
                           6,7,8,
                           9,10,11,
                           15,12,13,
                           13,14,15};
    ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
    ret.indices = new GLushort[ret.numIndices];
    memcpy(ret.indices, indices, sizeof(indices));

    return ret;
}
//! [2]



