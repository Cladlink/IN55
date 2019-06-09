 #include "Pyramide.h"

Pyramide::Pyramide()
{
    initializeOpenGLFunctions();

    ShapeData pyramide = IGeometryEngine::makePyramide();
    //ShapeData pyramideNormal = IGeometryEngine::generateNormals(pyramide);

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
                      QVector3D _position, QQuaternion _rotation, bool _showNormal, int _hideShapeNumber){

    IGeometryEngine::update(program,verticesPyramide,indicesPyramide,verticesPyramideNormal,indicesPyramideNormal,
                            _color,_modelToProjectionMatrix,_shapeModelToWorldMatrix,
                            _position,_rotation, false,_hideShapeNumber);
}


//! [2]



