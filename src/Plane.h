#ifndef PLANE_H
#define PLANE_H

#include "IGeometryEngine.h"


class Plane : public IGeometryEngine
{
public:
    Plane(uint _dimensions = 10);
    ~Plane();
    void update(QOpenGLShaderProgram *program,QVector3D _color,
                QMatrix4x4 _modelToProjectionMatrix, QMatrix4x4 _shapeModelToWorldMatrix,
                QVector3D _position);
    void initGeometry();

    void drawGeometry(QOpenGLShaderProgram *program);

    ShapeData makePlaneVerts(uint dimensions);
    ShapeData makePlaneIndices(uint dimensions);
    QVector3D randomColor();
private :
    uint dimensions;
    Vertex *verticesPlane;
    unsigned short *indicesPlane;
};

#endif // PLANE_H
