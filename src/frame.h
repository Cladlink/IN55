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

    //QRadiotButton
    QRadioButton *rbColor;
    QRadioButton *rbMulticolorVertices;
    QRadioButton *rbMulticolorFragments;
    QRadioButton *rbColorNormal;
    QRadioButton *rbMur;
    QRadioButton *rbNintendo;
    QRadioButton *rbTranslation;
    QRadioButton *mouseRotation;
    QRadioButton *xRotation;
    QRadioButton *yRotation;
    QRadioButton *zRotation;

    //QSlider
    QSlider *sliderHomothetie;
    QSlider *sliderRouge;
    QSlider *sliderVert;
    QSlider *sliderBleu;
    QSlider *sliderTranslationX;
    QSlider *sliderTranslationY;
    QSlider *sliderTranslationZ;

    //QPushButton
    QPushButton *boutonCube;
    QPushButton *boutonPyramide;

    //QLabel
    QLabel *labelHomothetie;
    QLabel *labelRouge;
    QLabel *labelVert;
    QLabel *labelBleu;
    QLabel *labelCouleur;
    QLabel *labelTranslation;
    QLabel *labelTranslationX;
    QLabel *labelTranslationY;
    QLabel *labelTranslationZ;

    //QHBoxLayout
    QHBoxLayout *layoutHomothetie;
    QHBoxLayout *layoutTranslationX;
    QHBoxLayout *layoutTranslationY;
    QHBoxLayout *layoutTranslationZ;
    QHBoxLayout *layoutRouge;
    QHBoxLayout *layoutVert;
    QHBoxLayout *layoutBleu;
    QHBoxLayout *layoutRotation;
    QHBoxLayout *layoutBoutonsForme;
    QHBoxLayout *mainLayout;

    //QVBoxLayout
    QVBoxLayout *layoutTranslation;
    QVBoxLayout *layoutCouleur;
    QVBoxLayout *paramsLayout;

private slots:
    void changeSize(int value);
    void createCube();
    void createPyramide();
    void changeTexture();
    void changeColor();
    void changeRotation();
    void changePosition();
};

#endif // FRAME_H
