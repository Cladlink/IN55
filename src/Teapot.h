#ifndef TEAPOT_H
#define TEAPOT_H

#include "IGeometryEngine.h"
#include <QtMath>

class Teapot : public IGeometryEngine
{
public:
    Teapot(uint _tesselation = 10, const QMatrix4x4 &_lidTransform = QMatrix4x4());
    ~Teapot() override;
    void update(QOpenGLShaderProgram *program,QVector3D _color,
                QMatrix4x4 _modelToProjectionMatrix, QMatrix4x4 _shapeModelToWorldMatrix,
                QVector3D _position, QQuaternion _rotation, bool showNormal, int _hideShapeNumber);
    void initGeometry();
    void drawGeometry(QOpenGLShaderProgram *program);

private :
    uint tesselation;
    const QMatrix4x4 *lidTransform;
    Vertex *verticesTeapot;
    unsigned short *indicesTeapot;
    Vertex *verticesTeapotNormal;
    unsigned short *indicesTeapotNormal;
};

#endif // TEAPOT_H
