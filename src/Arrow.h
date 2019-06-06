#ifndef ARROW_H
#define ARROW_H

#include "IGeometryEngine.h"

class Arrow : public IGeometryEngine
{
public:
    Arrow();
    ~Arrow() override;
    void update(QOpenGLShaderProgram *program,QVector3D _color,
                QMatrix4x4 _modelToProjectionMatrix, QMatrix4x4 _shapeModelToWorldMatrix,
                QVector3D _position);
    void initGeometry();
    void drawGeometry(QOpenGLShaderProgram *program);



private :
    Vertex *verticesArrow;
    unsigned short *indicesArrow;
};

#endif // ARROW_H
