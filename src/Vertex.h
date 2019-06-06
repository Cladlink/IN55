#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>
#include <QMatrix4x4>

struct Vertex
{
    QVector3D position;
    QVector3D color;
    QVector3D normal;
};

#endif // VERTEX_H
