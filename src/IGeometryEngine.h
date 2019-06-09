/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <iostream>
#include <QVector2D>
#include <QVector3D>
#include <math.h>
#include "vertex.h"
#include "ShapeData.h"
#include <QtMath>
#include "TeapotData.h"

#define PI 3.14159265359
#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a)

using namespace std;

class IGeometryEngine : protected QOpenGLFunctions
{
public:
    IGeometryEngine();
    virtual ~IGeometryEngine();
    void update(QOpenGLShaderProgram *program,Vertex *verticesShape, unsigned short *indicesShape,
                Vertex *verticesNormal, unsigned short *indicesNormal,
                QVector3D _color,QMatrix4x4 _modelToProjectionMatrix, QMatrix4x4 _shapeModelToWorldMatrix,
                QVector3D _position, QQuaternion _rotation, bool showNormal, int _hideShapeNumber);
    void initGeometry(Vertex *verticesShape,unsigned short *indicesShape);
    void drawGeometry(QOpenGLShaderProgram *program);

    QVector3D randomColor();
    ShapeData makeArrow();
    ShapeData makeCube();
    ShapeData makePlaneVerts(uint dimensions);
    ShapeData makePlaneIndices(uint dimensions);
    ShapeData makePlaneUnseamedIndices(uint tesselation);
    ShapeData makePyramide();
    ShapeData makeSphere(uint tesselation = 20);
    ShapeData makeTeapot(uint tesselation = 10, const QMatrix4x4 &lidTransform = QMatrix4x4());
    ShapeData makeTorus(uint tesselation = 20);
    ShapeData generateNormals(const ShapeData& data);

    void generatePatches(float * v, float * n, float * tc, unsigned short* el, int grid);
    void moveLid(int grid, float *v, const QMatrix4x4 &lidTransform);
    void buildPatchReflect(int patchNum,
       float *B, float *dB,
       float *v, float *n,
       float *tc, unsigned short *el,
       int &index, int &elIndex, int &tcIndex, int grid,
       bool reflectX, bool reflectY);
    void buildPatch(QVector3D patch[][4],
       float *B, float *dB,
       float *v, float *n, float *tc,
       unsigned short *el,
       int &index, int &elIndex, int &tcIndex,
       int grid, QMatrix3x3 reflect,
       bool invertNormal);
    void getPatch(int patchNum, QVector3D patch[][4], bool reverseV);
    void computeBasisFunctions(float * B, float * dB, int grid);
    QVector3D evaluate(int gridU, int gridV, float *B, QVector3D patch[][4]);
    QVector3D evaluateNormal(int gridU, int gridV,
       float *B, float *dB, QVector3D patch[][4]);

protected :
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    QOpenGLBuffer arrayNormalBuf;
    QOpenGLBuffer indexNormalBuf;
    int nbrVertices;
    int nbrIndices;
    int nbrVerticesNormal;
    int nbrIndicesNormal;
};

#endif // GEOMETRYENGINE_H
