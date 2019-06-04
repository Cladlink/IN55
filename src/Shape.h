#ifndef Shape_H
#define Shape_H

#include "IGeometryEngine.h"
#include <iostream>
#include <fstream>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <sstream>
#include <regex>
#include <QCoreApplication>

using namespace std;

class Shape : public IGeometryEngine
{
public:
    Shape();
    Shape(string _path);
    ~Shape();
    void update(QOpenGLShaderProgram *program, QVector3D _color) override;
    void initGeometry() override;

    void drawGeometry(QOpenGLShaderProgram *program) override;

    void load_obj();
    void setPath(string _path);
    string getPath();

    struct VertexData
    {
        QVector3D position;
        QVector3D color;
    };

    Shape::VertexData *verticesShape;
    GLushort *indicesShape;
private:
    string path;

};

#endif // Shape_H
