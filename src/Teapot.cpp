#include "Teapot.h"

Teapot::Teapot(uint _tesselation, const QMatrix4x4 &_lidTransform) {

    this->tesselation = _tesselation;
    this->lidTransform = &_lidTransform;
    initializeOpenGLFunctions();

    ShapeData teapot = IGeometryEngine::makeTeapot(tesselation,*lidTransform);
    ShapeData teapotNormal = IGeometryEngine::generateNormals(teapot);

    verticesTeapot = teapot.vertices;
    indicesTeapot = teapot.indices;
    verticesTeapotNormal = teapotNormal.vertices;
    indicesTeapotNormal = teapotNormal.indices;

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
    // Initializes cube geometry and transfers it to VBOs
    nbrIndices = teapot.numIndices;
    nbrVertices = teapot.numVertices;
    nbrIndicesNormal = teapotNormal.numIndices;
    nbrVerticesNormal = teapotNormal.numVertices;
    initGeometry();
}

Teapot::~Teapot()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]

void Teapot::initGeometry()
{
    IGeometryEngine::initGeometry(verticesTeapot,indicesTeapot);
}

//! [2]
void Teapot::drawGeometry(QOpenGLShaderProgram *program)
{
    IGeometryEngine::drawGeometry(program);
}

void Teapot::update(QOpenGLShaderProgram *program,QVector3D _color,
                  QMatrix4x4 _modelToProjectionMatrix, QMatrix4x4 _shapeModelToWorldMatrix,
                  QVector3D _position, QQuaternion _rotation, bool _showNormal, int _hideShapeNumber){

    if (_rotation == QQuaternion(0,QVector3D(1.,0.,0.))) {
        _rotation = QQuaternion(qDegreesToRadians(-90.),QVector3D(1.,0.,0.).normalized());
    }
    if (_position == QVector3D()) {
        _position = QVector3D(-3.,0.,0.);
    }
    IGeometryEngine::update(program,verticesTeapot,indicesTeapot,verticesTeapotNormal, indicesTeapotNormal,
                            _color,_modelToProjectionMatrix,_shapeModelToWorldMatrix,
                            _position,_rotation, _showNormal, _hideShapeNumber);
}

//! [2]



