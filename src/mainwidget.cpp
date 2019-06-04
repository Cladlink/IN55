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

#include "mainwidget.h"

#include <QMouseEvent>
#include <QTime>

#include <math.h>

const int NBR_TEXTURES = 10;
GLuint texId[NBR_TEXTURES];

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometriesSquare(0),
    angularSpeed(0)
{
    beginning = QDateTime::currentMSecsSinceEpoch();
    pixmap.append(QPixmap(":/mur.png"));
    pixmap.append(QPixmap(":/nintendo.png"));
    camera = new Camera;

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
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if(getAxeRotation() == 0){
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
    }
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
    //glEnable(GL_CULL_FACE);
//! [2]

    geometriesSquare = new Cube;
    geometriesPyramide = new Pyramide;
    geometriesSphere = new Shape("IN55/ressources/sphere.obj");
    geometriesTorus = new Shape("IN55/ressources/torus.obj");
    geometriesSuzanne = new Shape("IN55/ressources/suzanne.obj");

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

//! [3]
void MainWidget::initShaders()
{
    glGenTextures(NBR_TEXTURES, texId);
    for (int i = 0; i < pixmap.size(); ++i) {
        glBindTexture(GL_TEXTURE_2D, texId[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pixmap[i].width(), pixmap[i].height(),0,GL_RGBA, GL_UNSIGNED_BYTE, pixmap[i].toImage().bits());
    }

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
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 1.0, zFar = 10.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]

void MainWidget::repaint() {
    paintGL();
}

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QVector3D lightPositionWorld = myLight->lightPosition;

//! [6]
    // Calculate model view transformation
    QMatrix4x4 viewToProjectionMatrix;
    viewToProjectionMatrix.perspective(60.0f, ((float)width()) / height(), 0.1f, 20.0f);
    QMatrix4x4 worldToViewMatrix = camera->getWorldToViewMatrix();
    QMatrix4x4 worldToProjectionMatrix = viewToProjectionMatrix * worldToViewMatrix;

    QVector4D ambientLight(0.05f, 0.05f, 0.05f, 1.0f);
    program.setUniformValue("ambientLightUniformLocation", ambientLight);

    QVector3D color(0.f, 1.f, 0.05f);
    program.setUniformValue("colorUniformLocation", color);

    QVector3D eyePosition = camera->getPosition();
    program.setUniformValue("eyePosition", eyePosition);

    program.setUniformValue("lightPositionWorld", lightPositionWorld);

    //fullTransformationUniformLocation = glGetUniformLocation(programID, "modelToProjectionMatrix");
    //modelToWorldMatrixUniformLocation = glGetUniformLocation(programID, "modelToWorldMatrix");

    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);

    // Calculate normal matrix
    QMatrix4x4 normal;

    normal = matrix.inverted();
    normal = normal.transposed();

    program.setUniformValue("normal", normal);

    QVector4D homotethie = QVector4D(this->getHomotethie(),this->getHomotethie(),this->getHomotethie(),1.);

    // Set modelview-projection matrix
    program.setUniformValue("mvp", projection * matrix);
    program.setUniformValue("homotethie", homotethie);
    program.setUniformValue("translation", QVector4D(getPosition(),0.));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texId[getNumberBufferTexture()]);
    //glBindTexture(GL_TEXTURE_2D, texId[0]);
    //glBindTexture(GL_TEXTURE_2D, texId[1]);

    launch = QDateTime::currentMSecsSinceEpoch();

    program.setUniformValue("time", (launch-beginning)/1000);
    program.setUniformValue("isColor",isColor);

//! [6]
    if (getObject() == "cube") {
        geometriesSquare->update(&program,getColor());
    } else if (getObject() == "pyramide") {
        geometriesPyramide->update(&program,getColor());
    } else if (getObject() == "sphere") {
        geometriesSphere->update(&program,getColor());
    } else if (getObject() == "torus") {
        geometriesTorus->update(&program,getColor());
    } else if (getObject() == "suzanne") {
        geometriesSuzanne->update(&program,getColor());
    }
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

QVector3D MainWidget::getPosition() {
    return position;
}

void MainWidget::setPosition(QVector3D _position) {
    position = _position;
}

void MainWidget::mouseMoveEvent(QMouseEvent* e)
{
    //setFocus();
    QVector2D mouse;
    mouse.setX(e->x());
    mouse.setY(e->y());
    camera->mouseUpdate(mouse);
    update();
}

void MainWidget::keyPressEvent(QKeyEvent* e)
{
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
