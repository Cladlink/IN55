#ifndef PYRAMIDE_H
#define PYRAMIDE_H

#include "igeometryengine.h"

class Pyramide : public IGeometryEngine
{
public:
    Pyramide();
    ~Pyramide();
    void update(QOpenGLShaderProgram *program, QVector3D _color) override;
    void initGeometry() override;

    void drawGeometry(QOpenGLShaderProgram *program) override;

//    struct VertexData
//    {
//        QVector3D position;
//        QVector3D color;
//    };

};

#endif // PYRAMIDE_H
