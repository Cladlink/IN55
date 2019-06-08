#ifndef SPHERE_H
#define SPHERE_H

#include "IGeometryEngine.h"

class Sphere : public IGeometryEngine
{
public:
    Sphere(uint _tesselation = 20);
    ~Sphere() override;
    void update(QOpenGLShaderProgram *program,QVector3D _color,
                QMatrix4x4 _modelToProjectionMatrix, QMatrix4x4 _shapeModelToWorldMatrix,
                QVector3D _position, QQuaternion _rotation);
    void initGeometry();
    void drawGeometry(QOpenGLShaderProgram *program);



private :
    uint tesselation;
    Vertex *verticesSphere;
    unsigned short *indicesSphere;
};

#endif // SPHERE_H
