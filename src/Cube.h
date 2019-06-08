#ifndef CUBE_H
#define CUBE_H

#include "IGeometryEngine.h"

class Cube : public IGeometryEngine
{
public:
    Cube();
    ~Cube() override;
    void update(QOpenGLShaderProgram *program,QVector3D _color,
                QMatrix4x4 _modelToProjectionMatrix, QMatrix4x4 _shapeModelToWorldMatrix,
                QVector3D _position, QQuaternion _rotation);
    void initGeometry();
    void drawGeometry(QOpenGLShaderProgram *program);



private :
    Vertex *verticesCube;
    unsigned short *indicesCube;
};

#endif // CUBE_H
