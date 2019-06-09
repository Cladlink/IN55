#include "Torus.h"

Torus::Torus(uint _tesselation) {

    this->tesselation = _tesselation;
    initializeOpenGLFunctions();

    ShapeData torus = IGeometryEngine::makeTorus(this->tesselation);
    ShapeData torusNormal = IGeometryEngine::generateNormals(torus);

    verticesTorus = torus.vertices;
    indicesTorus = torus.indices;
    verticesTorusNormal = torusNormal.vertices;
    indicesTorusNormal = torusNormal.indices;

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
    // Initializes cube geometry and transfers it to VBOs
    nbrIndices = torus.numIndices;
    nbrVertices = torus.numVertices;
    nbrIndicesNormal = torusNormal.numIndices;
    nbrVerticesNormal = torusNormal.numVertices;
    initGeometry();
}

Torus::~Torus()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]

void Torus::initGeometry()
{
    IGeometryEngine::initGeometry(verticesTorus,indicesTorus);
}

//! [2]
void Torus::drawGeometry(QOpenGLShaderProgram *program)
{
    IGeometryEngine::drawGeometry(program);
}

void Torus::update(QOpenGLShaderProgram *program,QVector3D _color,
                   QMatrix4x4 _modelToProjectionMatrix, QMatrix4x4 _shapeModelToWorldMatrix,
                   QVector3D _position, QQuaternion _rotation, bool _showNormal, int _hideShapeNumber){

    IGeometryEngine::update(program,verticesTorus,indicesTorus,verticesTorusNormal, indicesTorusNormal,
                            _color,_modelToProjectionMatrix,_shapeModelToWorldMatrix,
                            _position,_rotation, _showNormal, _hideShapeNumber);
}
