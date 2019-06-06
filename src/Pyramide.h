#ifndef PYRAMIDE_H
#define PYRAMIDE_H

#include "IGeometryEngine.h"

class Pyramide : public IGeometryEngine
{
public:
    Pyramide();
    ~Pyramide();
    void update(QOpenGLShaderProgram *program,QVector3D _color,
                QMatrix4x4 _modelToProjectionMatrix, QMatrix4x4 _shapeModelToWorldMatrix,
                QVector3D _position);
    void initGeometry();

    void drawGeometry(QOpenGLShaderProgram *program);



private :
    Vertex *verticesPyramide;
    unsigned short *indicesPyramide;
    /*Vertex verticesPyramide[16] = {
        {QVector3D(0.f, 1.f, 0.f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.5f, 1.0f)}, //0 -> 0
        {QVector3D(0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 0.0f)}, //2 -> 1
        {QVector3D(-0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 0.0f)}, //1 -> 2

        {QVector3D(0.f, 1.f, 0.f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.5f, 1.0f)}, //0 -> 3
        {QVector3D(-0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 0.0f)}, //4 -> 4
        {QVector3D(0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 0.0f)}, //3 -> 5

        {QVector3D(0.f, 1.f, 0.f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.5f, 1.0f)}, //0 -> 6
        {QVector3D(0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 0.0f)}, //3 -> 7
        {QVector3D(0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 0.0f)}, //2 -> 8

        {QVector3D(0.f, 1.f, 0.f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.5f, 1.0f)}, //0 -> 9
        {QVector3D(-0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 0.0f)}, //1 -> 10
        {QVector3D(-0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 0.0f)}, //4 -> 11

        {QVector3D(-0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 0.0f)}, //1 -> 12
        {QVector3D(0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 0.0f)}, //2 -> 13
        {QVector3D(0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 1.0f)}, //3 -> 14
        {QVector3D(-0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 1.0f)}, //4 -> 15
    };

    GLushort indicesPyramide[18] = {
        0,1,2,
        3,4,5,
        6,7,8,
        9,10,11,
        15,12,13,
        13,14,15
    };*/
};

#endif // PYRAMIDE_H
