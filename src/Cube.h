#ifndef CUBE_H
#define CUBE_H

#include "IGeometryEngine.h"

class Cube : public IGeometryEngine
{
public:
    Cube();
    ~Cube();
    void update(QOpenGLShaderProgram *program, QVector3D _color) override;
    void initGeometry() override;

    void drawGeometry(QOpenGLShaderProgram *program) override;

private :
    VertexData verticesCube[72] =
    {
        QVector3D(-1.0f, +1.0f, +1.0f),  // 0
        QVector3D(+1.0f, +0.0f, +0.0f),	// Color
        QVector3D(+0.0f, +1.0f, +0.0f),  // Normal
        QVector3D(+1.0f, +1.0f, +1.0f),  // 1
        QVector3D(+0.0f, +1.0f, +0.0f),	// Color
        QVector3D(+0.0f, +1.0f, +0.0f),  // Normal
        QVector3D(+1.0f, +1.0f, -1.0f),  // 2
        QVector3D(+0.0f, +0.0f, +1.0f),  // Color
        QVector3D(+0.0f, +1.0f, +0.0f),  // Normal
        QVector3D(-1.0f, +1.0f, -1.0f),  // 3
        QVector3D(+1.0f, +1.0f, +1.0f),  // Color
        QVector3D(+0.0f, +1.0f, +0.0f),  // Normal

        QVector3D(-1.0f, +1.0f, -1.0f),  // 4
        QVector3D(+1.0f, +0.0f, +1.0f),  // Color
        QVector3D(+0.0f, +0.0f, -1.0f),  // Normal
        QVector3D(+1.0f, +1.0f, -1.0f),  // 5
        QVector3D(+0.0f, +0.5f, +0.2f),  // Color
        QVector3D(+0.0f, +0.0f, -1.0f),  // Normal
        QVector3D(+1.0f, -1.0f, -1.0f),  // 6
        QVector3D(+0.8f, +0.6f, +0.4f),  // Color
        QVector3D(+0.0f, +0.0f, -1.0f),  // Normal
        QVector3D(-1.0f, -1.0f, -1.0f),  // 7
        QVector3D(+0.3f, +1.0f, +0.5f),  // Color
        QVector3D(+0.0f, +0.0f, -1.0f),  // Normal

        QVector3D(+1.0f, +1.0f, -1.0f),  // 8
        QVector3D(+0.2f, +0.5f, +0.2f),  // Color
        QVector3D(+1.0f, +0.0f, +0.0f),  // Normal
        QVector3D(+1.0f, +1.0f, +1.0f),  // 9
        QVector3D(+0.9f, +0.3f, +0.7f),  // Color
        QVector3D(+1.0f, +0.0f, +0.0f),  // Normal
        QVector3D(+1.0f, -1.0f, +1.0f),  // 10
        QVector3D(+0.3f, +0.7f, +0.5f),  // Color
        QVector3D(+1.0f, +0.0f, +0.0f),  // Normal
        QVector3D(+1.0f, -1.0f, -1.0f),  // 11
        QVector3D(+0.5f, +0.7f, +0.5f),  // Color
        QVector3D(+1.0f, +0.0f, +0.0f),  // Normal

        QVector3D(-1.0f, +1.0f, +1.0f),  // 12
        QVector3D(+0.7f, +0.8f, +0.2f),  // Color
        QVector3D(-1.0f, +0.0f, +0.0f),  // Normal
        QVector3D(-1.0f, +1.0f, -1.0f),  // 13
        QVector3D(+0.5f, +0.7f, +0.3f),  // Color
        QVector3D(-1.0f, +0.0f, +0.0f),  // Normal
        QVector3D(-1.0f, -1.0f, -1.0f),  // 14
        QVector3D(+0.4f, +0.7f, +0.7f),  // Color
        QVector3D(-1.0f, +0.0f, +0.0f),  // Normal
        QVector3D(-1.0f, -1.0f, +1.0f),  // 15
        QVector3D(+0.2f, +0.5f, +1.0f),  // Color
        QVector3D(-1.0f, +0.0f, +0.0f),  // Normal

        QVector3D(+1.0f, +1.0f, +1.0f),  // 16
        QVector3D(+0.6f, +1.0f, +0.7f),  // Color
        QVector3D(+0.0f, +0.0f, +1.0f),  // Normal
        QVector3D(-1.0f, +1.0f, +1.0f),  // 17
        QVector3D(+0.6f, +0.4f, +0.8f),  // Color
        QVector3D(+0.0f, +0.0f, +1.0f),  // Normal
        QVector3D(-1.0f, -1.0f, +1.0f),  // 18
        QVector3D(+0.2f, +0.8f, +0.7f),  // Color
        QVector3D(+0.0f, +0.0f, +1.0f),  // Normal
        QVector3D(+1.0f, -1.0f, +1.0f),  // 19
        QVector3D(+0.2f, +0.7f, +1.0f),  // Color
        QVector3D(+0.0f, +0.0f, +1.0f),  // Normal

        QVector3D(+1.0f, -1.0f, -1.0f),  // 20
        QVector3D(+0.8f, +0.3f, +0.7f),  // Color
        QVector3D(+0.0f, -1.0f, +0.0f),  // Normal
        QVector3D(-1.0f, -1.0f, -1.0f),  // 21
        QVector3D(+0.8f, +0.9f, +0.5f),  // Color
        QVector3D(+0.0f, -1.0f, +0.0f),  // Normal
        QVector3D(-1.0f, -1.0f, +1.0f),  // 22
        QVector3D(+0.5f, +0.8f, +0.5f),  // Color
        QVector3D(+0.0f, -1.0f, +0.0f),  // Normal
        QVector3D(+1.0f, -1.0f, +1.0f),  // 23
        QVector3D(+0.9f, +1.0f, +0.2f),  // Color
        QVector3D(+0.0f, -1.0f, +0.0f),  // Normal
    };

    unsigned short indicesCube[36] = {
        0,   1,  2,  0,  2,  3, // Top
        4,   5,  6,  4,  6,  7, // Front
        8,   9, 10,  8, 10, 11, // Right
        12, 13, 14, 12, 14, 15, // Left
        16, 17, 18, 16, 18, 19, // Back
        20, 22, 21, 20, 23, 22, // Bottom
    };

    /*VertexData verticesCube[24] = {
        {QVector3D(-0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 1.0f), QVector3D(0.0f,0.0f,1.0f)}, //0
        {QVector3D(0.5f, -0.5f, 0.5f), QVector3D(0.0f, 1.0f,0.0f), QVector2D(1.0f, 1.0f), QVector3D(0.0f,0.0f,1.0f)}, //1
        {QVector3D(0.5f, 0.5f, 0.5f), QVector3D(1.0f, 0.0f,1.0f), QVector2D(1.0f, 0.0f), QVector3D(0.0f,0.0f,1.0f)}, //2
        {QVector3D(-0.5f, 0.5f, 0.5f), QVector3D(0.0f, 0.0f,1.0f), QVector2D(0.0f, 0.0f), QVector3D(0.0f,0.0f,1.0f)}, //3

        {QVector3D(-0.5f, -0.5f, -0.5f), QVector3D(0.0f, 0.0f,1.0f), QVector2D(1.0f, 1.0f), QVector3D(0.0f,0.0f,-1.0f)}, //4
        {QVector3D(0.5f, -0.5f, -0.5f), QVector3D(1.0f, 1.0f,0.0f), QVector2D(0.0f, 1.0f), QVector3D(0.0f,0.0f,-1.0f)}, //5
        {QVector3D(0.5f, 0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 0.0f), QVector3D(0.0f,0.0f,-1.0f)}, //6
        {QVector3D(-0.5f, 0.5f, -0.5f), QVector3D(1.0f, 1.0f,1.0f), QVector2D(1.0f, 0.0f), QVector3D(0.0f,0.0f,-1.0f)}, //7

        {QVector3D(-0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 0.0f), QVector3D(0.0f,-1.0f,0.0f)}, //0 -> 8
        {QVector3D(0.5f, -0.5f, 0.5f), QVector3D(0.0f, 1.0f,0.0f), QVector2D(1.0f, 0.0f),QVector3D(0.0f,-1.0f,0.0f)}, //1 -> 9
        {QVector3D(0.5f, -0.5f, -0.5f), QVector3D(1.0f, 1.0f,0.0f), QVector2D(1.0f, 1.0f),QVector3D(0.0f,-1.0f,0.0f)}, //4 -> 10
        {QVector3D(-0.5f, -0.5f, -0.5f), QVector3D(0.0f, 0.0f,1.0f), QVector2D(0.0f, 1.0f),QVector3D(0.0f,-1.0f,0.0f)}, //5 -> 11

        {QVector3D(-0.5f, 0.5f, 0.5f), QVector3D(0.0f, 0.0f,1.0f), QVector2D(0.0f, 1.0f),QVector3D(0.0f,1.0f,0.0f)}, //2 -> 12
        {QVector3D(0.5f, 0.5f, 0.5f), QVector3D(1.0f, 0.0f,1.0f), QVector2D(1.0f, 1.0f),QVector3D(0.0f,1.0f,0.0f)}, //3 -> 13
        {QVector3D(0.5f, 0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 0.0f),QVector3D(0.0f,1.0f,0.0f)}, //6 -> 14
        {QVector3D(-0.5f, 0.5f, -0.5f), QVector3D(1.0f, 1.0f,1.0f), QVector2D(0.0f, 0.0f),QVector3D(0.0f,1.0f,0.0f)}, //7 -> 15

        {QVector3D(0.5f, -0.5f, 0.5f), QVector3D(0.0f, 1.0f,0.0f), QVector2D(0.0f, 1.0f),QVector3D(1.0f,0.0f,0.0f)}, //1 -> 16
        {QVector3D(0.5f, 0.5f, 0.5f), QVector3D(1.0f, 0.0f,1.0f), QVector2D(0.0f, 0.0f),QVector3D(1.0f,0.0f,0.0f)}, //2 -> 17
        {QVector3D(0.5f, -0.5f, -0.5f), QVector3D(1.0f, 1.0f,0.0f), QVector2D(1.0f, 1.0f),QVector3D(1.0f,0.0f,0.0f)}, //5 -> 18
        {QVector3D(0.5f, 0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 0.0f),QVector3D(1.0f,0.0f,0.0f)}, //6 -> 19

        {QVector3D(-0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 1.0f),QVector3D(-1.0f,0.0f,0.0f)}, //0 -> 20
        {QVector3D(-0.5f, 0.5f, 0.5f), QVector3D(0.0f, 0.0f,1.0f), QVector2D(0.0f, 0.0f),QVector3D(-1.0f,0.0f,0.0f)}, //3 -> 21
        {QVector3D(-0.5f, -0.5f, -0.5f), QVector3D(0.0f, 0.0f,1.0f), QVector2D(1.0f, 1.0f),QVector3D(-1.0f,0.0f,0.0f)}, //4 -> 22
        {QVector3D(-0.5f, 0.5f, -0.5f), QVector3D(1.0f, 1.0f,1.0f), QVector2D(1.0f, 0.0f),QVector3D(-1.0f,0.0f,0.0f)}, //7 -> 23
    };*/

    /*VertexData verticesCube2[24] = {
        {QVector3D(0.5f, 0.5f, 1.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 1.0f)}, //0
        {QVector3D(1.5f, 0.5f, 1.5f), QVector3D(0.0f, 1.0f,0.0f), QVector2D(1.0f, 1.0f)}, //1
        {QVector3D(1.5f, 1.5f, 1.5f), QVector3D(1.0f, 0.0f,1.0f), QVector2D(1.0f, 0.0f)}, //2
        {QVector3D(0.5f, 1.5f, 1.5f), QVector3D(0.0f, 0.0f,1.0f), QVector2D(0.0f, 0.0f)}, //3

        {QVector3D(0.5f, 0.5f, 0.5f), QVector3D(0.0f, 0.0f,1.0f), QVector2D(1.0f, 1.0f)}, //4
        {QVector3D(1.5f, 0.5f, 0.5f), QVector3D(1.0f, 1.0f,0.0f), QVector2D(0.0f, 1.0f)}, //5
        {QVector3D(1.5f, 1.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 0.0f)}, //6
        {QVector3D(0.5f, 1.5f, 0.5f), QVector3D(1.0f, 1.0f,1.0f), QVector2D(1.0f, 0.0f)}, //7

        {QVector3D(0.5f, 0.5f, 1.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 0.0f)}, //0 -> 8
        {QVector3D(1.5f, 0.5f, 1.5f), QVector3D(0.0f, 1.0f,0.0f), QVector2D(1.0f, 0.0f)}, //1 -> 9
        {QVector3D(1.5f, 0.5f, 0.5f), QVector3D(1.0f, 1.0f,0.0f), QVector2D(1.0f, 1.0f)}, //4 -> 10
        {QVector3D(0.5f, 0.5f, 0.5f), QVector3D(0.0f, 0.0f,1.0f), QVector2D(0.0f, 1.0f)}, //5 -> 11

        {QVector3D(0.5f, 1.5f, 1.5f), QVector3D(0.0f, 0.0f,1.0f), QVector2D(0.0f, 1.0f)}, //2 -> 12
        {QVector3D(1.5f, 1.5f, 1.5f), QVector3D(1.0f, 0.0f,1.0f), QVector2D(1.0f, 1.0f)}, //3 -> 13
        {QVector3D(1.5f, 1.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 0.0f)}, //6 -> 14
        {QVector3D(0.5f, 1.5f, 0.5f), QVector3D(1.0f, 1.0f,1.0f), QVector2D(0.0f, 0.0f)}, //7 -> 15

        {QVector3D(1.5f, 0.5f, 1.5f), QVector3D(0.0f, 1.0f,0.0f), QVector2D(0.0f, 1.0f)}, //1 -> 16
        {QVector3D(1.5f, 1.5f, 1.5f), QVector3D(1.0f, 0.0f,1.0f), QVector2D(0.0f, 0.0f)}, //2 -> 17
        {QVector3D(1.5f, 0.5f, 0.5f), QVector3D(1.0f, 1.0f,0.0f), QVector2D(1.0f, 1.0f)}, //5 -> 18
        {QVector3D(1.5f, 1.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 0.0f)}, //6 -> 19

        {QVector3D(0.5f, 0.5f, 1.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 1.0f)}, //0 -> 20
        {QVector3D(0.5f, 1.5f, 1.5f), QVector3D(0.0f, 0.0f,1.0f), QVector2D(0.0f, 0.0f)}, //3 -> 21
        {QVector3D(0.5f, 0.5f, 0.5f), QVector3D(0.0f, 0.0f,1.0f), QVector2D(1.0f, 1.0f)}, //4 -> 22
        {QVector3D(0.5f, 1.5f, 0.5f), QVector3D(1.0f, 1.0f,1.0f), QVector2D(1.0f, 0.0f)}, //7 -> 23
    };*/

    /*GLushort indicesCube[36] = {
        0,1,2,
        0,2,3,

        5,4,7,
        5,7,6,

        11,10,9,
        11,9,8,

        12,13,14,
        12,14,15,

        16,18,19,
        16,19,17,

        22,20,21,
        22,21,23
    };*/
};

#endif // CUBE_H
