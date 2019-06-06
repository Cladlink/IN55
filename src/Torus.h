#ifndef TORUS_H
#define TORUS_H

#include "IGeometryEngine.h"

class Torus : public IGeometryEngine
{
public:
    Torus(uint tesselation = 20);
    ~Torus() override;
    void update(QOpenGLShaderProgram *program,QVector3D _color,
                QMatrix4x4 _modelToProjectionMatrix, QMatrix4x4 _shapeModelToWorldMatrix,
                QVector3D _position);
    void initGeometry();
    void drawGeometry(QOpenGLShaderProgram *program);

private :
    uint tesselation;
    Vertex *verticesTorus;
    unsigned short *indicesTorus;
};

#endif // TORUS_H
