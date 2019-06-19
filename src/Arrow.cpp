#include "Arrow.h"

Arrow::Arrow() {

    initializeOpenGLFunctions();

    ShapeData arrow = IGeometryEngine::makeArrow();
    ShapeData arrowNormal = IGeometryEngine::generateNormals(arrow);
    verticesArrow = arrow.vertices;
    indicesArrow = arrow.indices;
    verticesArrowNormal = arrowNormal.vertices;
    indicesArrowNormal = arrowNormal.indices;

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
    // Initializes cube geometry and transfers it to VBOs
    nbrIndices = arrow.numIndices;
    nbrVertices = arrow.numVertices;
    nbrIndicesNormal = arrowNormal.numIndices;
    nbrVerticesNormal = arrowNormal.numVertices;
    initGeometry();
}

Arrow::~Arrow()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]

void Arrow::initGeometry()
{
    IGeometryEngine::initGeometry(verticesArrow,indicesArrow);
}

//! [2]
void Arrow::drawGeometry(QOpenGLShaderProgram *program)
{
    IGeometryEngine::drawGeometry(program);
}

void Arrow::update(QOpenGLShaderProgram *program,QVector3D _color,
                  QMatrix4x4 _modelToProjectionMatrix, QMatrix4x4 _shapeModelToWorldMatrix,
                  QVector3D _position, QQuaternion _rotation, bool _showNormal, int _hideShapeNumber){

    if (_position == QVector3D()) {
        _position = QVector3D(0.,1.,1.);
    }
    IGeometryEngine::update(program,verticesArrow,indicesArrow,verticesArrowNormal, indicesArrowNormal,
                            _color,_modelToProjectionMatrix,_shapeModelToWorldMatrix,
                            _position, _rotation, _showNormal, _hideShapeNumber);
}

//! [2]



