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

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "IGeometryEngine.h"
#include "Cube.h"
#include "Pyramide.h"
#include "Shape.h"
#include "Camera.h"
#include "Plane.h"
#include "Light.h"
#include "ShapeData.h"
#include "ShapeGenerator.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QVector3D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class GeometryEngine;

class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    explicit MainWidget(Light* _myLight, QWidget *parent = 0);

    ~MainWidget();
    void repaint();

    float getHomotethie();
    void setHomotethie(float _omotethie);
    string getObject();
    void setObject(string _object);
    string getPathTexture();
    void setPathTexture(string _pathTexture);
    int getNbObjects();
    void setNbObjects(int _nbObject);
    QVector3D getColor();
    void setColor(QVector3D _color);
    int getIsColor();
    void setIsColor(int _isColor);
    int getNumberBufferTexture();
    void setNumberBufferTexture(int _index);
    int getAxeRotation();
    void setAxeRotation(int _axeRotation);
    QVector3D getPosition();
    void setPosition(QVector3D _position);

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void keyPressEvent(QKeyEvent *e) override;
    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();
    void initTextures();

private:
    QBasicTimer timer;
    QOpenGLShaderProgram program;
    QVector<QPixmap> pixmap;
    Cube *geometriesSquare;
    Pyramide *geometriesPyramide;
    Plane *geometriesPlane;
    Shape *geometriesSphere;
    Shape *geometriesTorus;
    Shape *geometriesSuzanne;
    float valueSlider = 0.5;
    float homotethie = 0.5;
    int nbObjects;
    string object;
    float beginning;
    float launch;
    string pathTexture;
    int isColor;
    int indexBufferArrayTexture;
    int axeRotation;

    QMatrix4x4 projection;
    QMatrix4x4 matrix;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    QVector3D color;
    QVector3D position;

    Light *myLight;

    int nbrVertices;
    int nbrIndices;

    Camera* camera;

    qreal angularSpeed;
    QQuaternion rotation;
};

#endif // MAINWIDGET_H
