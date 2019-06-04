#ifndef PLANE_H
#define PLANE_H

#include "IGeometryEngine.h"
#include "ShapeData.h"

class Plane : public IGeometryEngine
{
public:
    Plane(uint _dimensions = 10);
    ~Plane();
    void update(QOpenGLShaderProgram *program, QVector3D _color) override;
    void initGeometry() override;

    void drawGeometry(QOpenGLShaderProgram *program) override;
    ShapeData makePlaneVerts(uint dimensions);
    ShapeData makePlaneIndices(uint dimensions);
    QVector3D randomColor();
private :
    uint dimensions;
    Vertex *verticesPlane;
    unsigned short *indicesPlane;
};

#endif // PLANE_H
