#ifndef CUBE_H
#define CUBE_H

#include "igeometryengine.h"

class Cube : public IGeometryEngine
{
public:
    Cube();
    ~Cube();
    void update() override;
    void initGeometry() override;

    void drawGeometry(QOpenGLShaderProgram *program) override;
};

#endif // CUBE_H
