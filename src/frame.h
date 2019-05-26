#ifndef FRAME_H
#define FRAME_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QSlider>
#include <QStackedWidget>
#include <QTextEdit>
#include <QLabel>
#include <QSize>
#include <QMessageBox>
#include <iostream>
#include <QDebug>

#include "mainwidget.h"
#include "colortextedit.h"

using namespace std;

class Frame : public QWidget
{
    Q_OBJECT

public:
    explicit Frame();

private:
    MainWidget *scene3D;
    QRadioButton *rbColor;
    QSlider *rouge;
    QSlider *vert;
    QSlider *bleu;
    QRadioButton *rbMulticolorVertices;
    QRadioButton *rbMulticolorFragments;
    QRadioButton *rbMur;
    QRadioButton *rbNintendo;
    QPushButton *boutonCube;
    QPushButton *boutonPyramide;
    QPushButton *boutonSphere;
    QPushButton *boutonTorus;
    QPushButton *boutonSuzanne;
    QSlider *sliderHomothetie;
    QRadioButton *mouseRotation;
    QRadioButton *xRotation;
    QRadioButton *yRotation;
    QRadioButton *zRotation;
    //colorTextEdit *bleu;

private slots:
    void ouvrirMessageBox(int value);
    void createCube();
    void createPyramide();
    void createSphere();
    void createTorus();
    void createSuzanne();
    void changeTextureNintendo();
    void changeTextureMur();
    void changeColorRed();
    void changeColorGreen();
    void changeColorBlue();
    void changeColor();
    void changeRotation();
};

#endif // FRAME_H
