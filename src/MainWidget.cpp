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

#include "MainWidget.h"

#include <QMouseEvent>
#include <QTime>
#include <QGuiApplication>
#include <QOpenGLContext>
#include <QWindow>
#include <QOpenGLVertexArrayObject>
#include <math.h>

const int NBR_TEXTURES = 10;
GLuint texId[NBR_TEXTURES];

const uint NUM_VERTICES_PER_TRI = 3;
const uint NUM_FLOATS_PER_VERTICE = 9;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE * sizeof(float);

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometriesSquare(0),
    camera(new Camera()),
    angularSpeed(0)
{
    beginning = QDateTime::currentMSecsSinceEpoch();
    pixmap.append(QPixmap(":/mur.png"));
    pixmap.append(QPixmap(":/nintendo.png"));
}

MainWidget::MainWidget(Light* _myLight, QWidget *parent) :
    QOpenGLWidget(parent),
    geometriesSquare(0),
    myLight(_myLight),
    camera(new Camera()),
    angularSpeed(0)
{
    beginning = QDateTime::currentMSecsSinceEpoch();
    //pixmap.append(QPixmap(":/mur.png"));
    //pixmap.append(QPixmap(":/nintendo.png"));
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();

    doneCurrent();
}

//! [0]
void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    //mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    /*if(getAxeRotation() == 0){
        // Mouse release position - mouse press position
        QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

        // Rotation axis is perpendicular to the mouse position difference
        // vector
        QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

        // Accelerate angular speed relative to the length of the mouse sweep
        qreal acc = diff.length() / 100.0;

        // Calculate new rotation axis as weighted sum
        rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

        // Increase angular speed
        angularSpeed += acc;
    }*/
}
//! [0]

//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{
    if(getAxeRotation() == 1){
        rotationAxis = QVector3D(1.0, 0.0, 0.0).normalized();
    } else if(getAxeRotation() == 2){
        rotationAxis = QVector3D(0.0, 1.0, 0.0).normalized();
    } else if(getAxeRotation() == 3){
        rotationAxis = QVector3D(0.0, 0.0, 1.0).normalized();
    }

    if(getAxeRotation() != 0){
        angularSpeed = 5;
    } else {
        // Decrease angular speed (friction)
        angularSpeed *= 0.99;
    }

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
        // Request an update
    }

    update();
}
//! [1]

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
//! [2]

    geometriesSquare = new Cube;
    geometriesLight = new Cube;
    geometriesPyramide = new Pyramide;
    geometriesPlane = new Plane(20);
    //geometriesPyramide = new Pyramide;
    /*geometriesPyramide = new Pyramide;
    geometriesSphere = new Shape("IN55/ressources/sphere.obj");
    geometriesTorus = new Shape("IN55/ressources/torus.obj");
    geometriesSuzanne = new Shape("IN55/ressources/suzanne.obj");*/

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

//! [3]
void MainWidget::initShaders()
{
    /*glGenTextures(NBR_TEXTURES, texId);
    for (int i = 0; i < pixmap.size(); ++i) {
        glBindTexture(GL_TEXTURE_2D, texId[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pixmap[i].width(), pixmap[i].height(),0,GL_RGBA, GL_UNSIGNED_BYTE, pixmap[i].toImage().bits());
    }*/

    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
//! [3]


//! [5]
void MainWidget::resizeGL(int w, int h)
{
}
//! [5]

void MainWidget::repaint() {
    paintGL();
}

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, width(), height());

    QMatrix4x4 modelToProjectionMatrix;

    QVector3D lightPositionWorld = myLight->lightPosition;

    QVector4D ambientLight(0.05f, 0.05f, 0.05f, 1.0f);
    program.setUniformValue("ambientLight", ambientLight);

    QVector3D eyePosition = camera->getPosition();
    program.setUniformValue("eyePosition", eyePosition);

    program.setUniformValue("lightPositionWorld", lightPositionWorld);
//! [6]
    // Calculate model view transformation
    QMatrix4x4 viewToProjectionMatrix;
    // Calculate aspect ratio
    float aspect = width() / height();
    // Set near plane to 0.1, far plane to 50.0, field of view 60 degrees
    float zNear = 0.1f, zFar = 50.0f, fov = 60.0f;

    viewToProjectionMatrix.perspective(fov, aspect, zNear, zFar);

    QMatrix4x4 worldToViewMatrix = camera->getWorldToViewMatrix();

    QMatrix4x4 worldToProjectionMatrix = viewToProjectionMatrix * worldToViewMatrix;

    QMatrix4x4 shapeModelToWorldMatrix;
    modelToProjectionMatrix = worldToProjectionMatrix * shapeModelToWorldMatrix;
    program.setUniformValue("modelToProjectionMatrix", modelToProjectionMatrix);

    program.setUniformValue("modelToWorldMatrix", shapeModelToWorldMatrix);

    QVector4D homotethie = QVector4D(this->getHomotethie(),this->getHomotethie(),this->getHomotethie(),1.);

    program.setUniformValue("homotethie", homotethie);

    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, texId[getNumberBufferTexture()]);

    launch = QDateTime::currentMSecsSinceEpoch();

    program.setUniformValue("time", (launch-beginning)/1000);
    program.setUniformValue("isColor",isColor);

    geometriesSquare->update(&program,getColor(),modelToProjectionMatrix,shapeModelToWorldMatrix, getPositionCube());
    geometriesPyramide->update(&program,getColor(),modelToProjectionMatrix,shapeModelToWorldMatrix,QVector3D(1.,1.,1.));
    geometriesPlane->update(&program,getColor(),modelToProjectionMatrix,shapeModelToWorldMatrix, QVector3D(0.,0.,0.));


//! [6]
    /*if (getObject() == "cube") {
        geometriesSquare->update(&program,getColor());
    } else if (getObject() == "pyramide") {
        geometriesPyramide->update(&program,getColor());
    } else if (getObject() == "sphere") {
        geometriesSphere->update(&program,getColor());
    } else if (getObject() == "torus") {
        geometriesTorus->update(&program,getColor());
    } else if (getObject() == "suzanne") {
        geometriesSuzanne->update(&program,getColor());
    }*/
}

float MainWidget::getHomotethie(){
    return homotethie;
}

void MainWidget::setHomotethie(float _homotethie){
    homotethie = _homotethie;
}

string MainWidget::getObject(){
    return object;
}

void MainWidget::setObject(string _object){
    object = _object;
}

int MainWidget::getNbObjects(){
    return nbObjects;
}

void MainWidget::setNbObjects(int _nbObject){
    nbObjects = _nbObject;
}

string MainWidget::getPathTexture(){
    return pathTexture;
}

void MainWidget::setPathTexture(string _pathTexture){
    pathTexture = _pathTexture;
}

QVector3D MainWidget::getColor() {
    return color;
}

void MainWidget::setColor(QVector3D _color) {
    color = _color;
}

int MainWidget::getIsColor() {
    return isColor;
}

void MainWidget::setIsColor(int _isColor) {
    // 0 = texture;
    // 1 = couleur choisie par l'utilisateur;
    // 2 = multi color par rapport aux vertices;
    // 3 = multi color par rapport aux fragments;
    isColor = _isColor;
}

int MainWidget::getNumberBufferTexture() {
    return indexBufferArrayTexture;
}

void MainWidget::setNumberBufferTexture(int _index) {
    indexBufferArrayTexture = _index;
}

int MainWidget::getAxeRotation() {
    return axeRotation;
}

void MainWidget::setAxeRotation(int _axeRotation) {
    axeRotation = _axeRotation;
}

QVector3D MainWidget::getPositionCube() {
    return position;
}

void MainWidget::setPositionCube(QVector3D _position) {
    position = _position;
}

void MainWidget::mouseMoveEvent(QMouseEvent* e)
{
    setFocus();
    camera->mouseUpdate(QVector2D(e->x(),e->y()));
    update();
}

void MainWidget::keyPressEvent(QKeyEvent* e)
{
    setFocus();
    switch (e->key())
    {
    case Qt::Key::Key_Z:
        camera->moveForward();
        break;
    case Qt::Key::Key_S:
        camera->moveBackward();
        break;
    case Qt::Key::Key_Q:
        camera->strafeLeft();
        break;
    case Qt::Key::Key_D:
        camera->strafeRight();
        break;
    case Qt::Key::Key_R:
        camera->moveUp();
        break;
    case Qt::Key::Key_F:
        camera->moveDown();
        break;
    }
    update();
}

