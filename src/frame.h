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
#include <QTabWidget>
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

    //QTabWidget
    QTabWidget *optionsTab;

    //QRadiotButton
    QRadioButton *rbColor;
    QRadioButton *rbMulticolorVertices;
    QRadioButton *rbMulticolorFragments;
    QRadioButton *rbColorNormal;
    QRadioButton *rbMur;
    QRadioButton *rbNintendo;
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
    QPushButton *boutonSphere;
    QPushButton *boutonTorus;
    QPushButton *boutonSuzanne;

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
    QLabel *labelRotation;

    //QHBoxLayout
    QHBoxLayout *layoutHomothetie;
    QHBoxLayout *layoutTranslationX;
    QHBoxLayout *layoutTranslationY;
    QHBoxLayout *layoutTranslationZ;
    QHBoxLayout *layoutRouge;
    QHBoxLayout *layoutVert;
    QHBoxLayout *layoutBleu;
    QHBoxLayout *mainLayout;

    //QVBoxLayout
    QVBoxLayout *layoutRotation;
    QVBoxLayout *layoutBoutonsForme;
    QVBoxLayout *layoutTranslation;
    QVBoxLayout *layoutCouleur;
    QVBoxLayout *paramsLayout;

private slots:
    void changeSize(int value);
    void createCube();
    void createPyramide();
    void changeTexture();
    void createSphere();
    void createTorus();
    void createSuzanne();
    void changeColor();
    void changeRotation();
    void changePosition();
};

#endif // FRAME_H
