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


const int NBR_TEXTURES = 10;
GLuint texId[NBR_TEXTURES];

const uint NUM_VERTICES_PER_TRI = 3;
const uint NUM_FLOATS_PER_VERTICE = 9;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE * sizeof(float);

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometriesCube(0),
    camera(new Camera()),
    angularSpeed(0)
{
    beginning = QDateTime::currentMSecsSinceEpoch();
    pixmap.append(QPixmap(":/mur.png"));
    pixmap.append(QPixmap(":/nintendo.png"));
}

MainWidget::MainWidget(Light* _myLight, QWidget *parent) :
    QOpenGLWidget(parent),
    geometriesCube(0),
    myLight(_myLight),
    camera(new Camera()),
    angularSpeed(0)
{
    beginning = QDateTime::currentMSecsSinceEpoch();
    rotation = QQuaternion(0,QVector3D(1.,0.,0.));
    itemsMapShape = QMap<QString, QString>();
    itemsMapShape.insert("Cube","Cube");
    itemsMapShape.insert("Arrow","Arrow");
    itemsMapShape.insert("Plane","Plane");
    itemsMapShape.insert("Sphere","Sphere");
    itemsMapShape.insert("Pyramide","Pyramide");
    itemsMapShape.insert("Teapot","Teapot");
    itemsMapHideShape = QMap<QString, int>();
    itemsMapHideShape.insert("Cube",0);
    itemsMapHideShape.insert("Arrow",0);
    itemsMapHideShape.insert("Plane",0);
    itemsMapHideShape.insert("Sphere",0);
    itemsMapHideShape.insert("Pyramide",0);
    itemsMapHideShape.insert("Teapot",0);
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

    geometriesCube = new Cube;
    cubeNormal = new Cube;
    geometriesLight = new Cube;
    //geometriesTorus = new Torus;
    geometriesPyramide = new Pyramide;
    geometriesArrow = new Arrow;
    geometriesTeapot = new Teapot;
    geometriesPlane = new Plane;
    geometriesSphere = new Sphere;
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

    QVector4D homothetie = QVector4D(getHomothetie(),1.);

    program.setUniformValue("homothetie", homothetie);

    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, texId[getNumberBufferTexture()]);

    launch = QDateTime::currentMSecsSinceEpoch();

    program.setUniformValue("time", (launch-beginning)/1000);
    program.setUniformValue("isColor",isColor);

    geometriesCube->update(&program,getColor(),modelToProjectionMatrix,shapeModelToWorldMatrix,
                           getPosition("Cube"), getRotation("Cube"), normal, itemsMapHideShape.value("Cube"));
    /*geometriesPlane->update(&program,getColor(),modelToProjectionMatrix,shapeModelToWorldMatrix,
                            getPosition("Plane"), getRotation("Plane"), normal, itemsMapHideShape.value("Plane"));
    //geometriesPlane->update(&program,getColor(),modelToProjectionMatrix,shapeModelToWorldMatrix, QVector3D(0.,0.,0.), getRotation());
    geometriesArrow->update(&program,getColor(),modelToProjectionMatrix,shapeModelToWorldMatrix,
                            getPosition("Arrow"), getRotation("Arrow"), normal, itemsMapHideShape.value("Arrow"));
    //geometriesArrow->update(&program,getColor(),modelToProjectionMatrix,shapeModelToWorldMatrix,QVector3D(-2.,2.,2.), getRotation());
    geometriesSphere->update(&program,getColor(),modelToProjectionMatrix,shapeModelToWorldMatrix,
                             getPosition("Sphere"), getRotation("Sphere"), normal, itemsMapHideShape.value("Sphere"));
    //geometriesSphere->update(&program,getColor(),modelToProjectionMatrix,shapeModelToWorldMatrix, QVector3D(-1.,2.,-1.), getRotation());
    geometriesPyramide->update(&program,getColor(),modelToProjectionMatrix,shapeModelToWorldMatrix,
                               getPosition("Pyramide"), getRotation("Pyramide"), normal, itemsMapHideShape.value("Pyramide"));
    //geometriesPyramide->update(&program,getColor(),modelToProjectionMatrix,shapeModelToWorldMatrix,QVector3D(1.,1.,1.), getRotation());

    modelToProjectionMatrix.rotate(-90,QVector3D(1.f,0.f,0.f));
    geometriesTeapot->update(&program,getColor(),modelToProjectionMatrix,shapeModelToWorldMatrix,
                             getPosition("Teapot"), getRotation("Teapot"), normal, itemsMapHideShape.value("Teapot"));
    //geometriesTeapot->update(&program,getColor(),modelToProjectionMatrix,shapeModelToWorldMatrix, QVector3D(3.,2.,3.), getRotation());
    modelToProjectionMatrix.rotate(90,QVector3D(1.f,0.f,0.f));*/

    //geometriesTorus->update(&program,getColor(),modelToProjectionMatrix,shapeModelToWorldMatrix, QVector3D(0.,4.,0.), getRotation());
}

QVector3D MainWidget::getHomothetie(){
    return homothetie;
}

void MainWidget::setHomothetie(QVector3D _homothetie){
    homothetie = _homothetie;
}

int MainWidget::getTesselation(){
    return tesselation;
}

void MainWidget::setTesselation(int _tesselation){
    if (itemsMapShape.contains("Sphere")) {
        geometriesSphere->~Sphere();
        geometriesSphere = new Sphere(_tesselation);
    }

    if (itemsMapShape.contains("Plane")) {
        geometriesPlane->~Plane();
        geometriesPlane = new Plane(_tesselation);
    }

    if (itemsMapShape.contains("Teapot")) {
        geometriesTeapot->~Teapot();
        geometriesTeapot = new Teapot(_tesselation);
    }
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
    // 4 = multi color par rapport aux normales;
    isColor = _isColor;
}

void MainWidget::selectShape(QString name) {
    if (itemsMapShape.contains(name)) {
        itemsMapShape.remove(name);
    } else {
        itemsMapShape.insert(name,name);
    }
}

void MainWidget::showNormal(bool _showNormal) {
    normal = _showNormal;
}

void MainWidget::hideShape(int _hideShapeNumber) {
    // 0 = on affiche l'objet;
    // 1 = on cache l'objet;
    itemsMapHideShape.insert("Cube",_hideShapeNumber);
}

bool MainWidget::isShapeInMap(QString name) {
    return itemsMapShape.contains(name);
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

QVector3D MainWidget::getPosition(QString name) {
    if (itemsMapShape.contains(name)){
        /*if (name == "Teapot") {
            return position = QVector3D(position.y(),position.z(),position.x());
        }*/
        return position;
    } else {
        return QVector3D(0.f,0.f,0.f);
    }
}

void MainWidget::setPosition(QVector3D _position) {
    position = _position;
}

QQuaternion MainWidget::getRotation(QString name) {
    if (itemsMapShape.contains(name)){
        return rotation;
    } else {
        return QQuaternion(0.f,QVector3D(1.f,0.f,0.f));
    }
}

void MainWidget::setRotation(QQuaternion _rotation) {
    rotation = _rotation;
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
    case Qt::Key::Key_Up:
        camera->moveForward();
        break;
    case Qt::Key::Key_S:
        camera->moveBackward();
        break;
    case Qt::Key::Key_Down:
        camera->moveBackward();
        break;
    case Qt::Key::Key_Q:
        camera->strafeLeft();
        break;
    case Qt::Key::Key_Left:
        camera->strafeLeft();
        break;
    case Qt::Key::Key_D:
        camera->strafeRight();
        break;
    case Qt::Key::Key_Right:
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

