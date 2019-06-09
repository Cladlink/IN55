#ifndef FRAME_H
#define FRAME_H

#include <QPushButton>
#include <QCheckBox>
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
#include <QQuaternion>

#include "MainWidget.h"
#include "Colortextedit.h"
#include "DebugSlider.h"
#include "Light.h"

using namespace std;

class Frame : public QWidget
{
    Q_OBJECT

public:
    explicit Frame();

private:
    Light myLight;

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
    QSlider *sliderTesselation;
    QSlider *sliderRouge;
    QSlider *sliderVert;
    QSlider *sliderBleu;
    QSlider *sliderTranslationX;
    QSlider *sliderTranslationY;
    QSlider *sliderTranslationZ;
    QSlider *sliderRotationX;
    QSlider *sliderRotationY;
    QSlider *sliderRotationZ;

    //DebugSlider
    DebugSlider *sliderLightX;
    DebugSlider *sliderLightY;
    DebugSlider *sliderLightZ;

    //QCheckBox
    QCheckBox *checkBoxCube;
    QCheckBox *checkBoxArrow;
    QCheckBox *checkBoxPlane;
    QCheckBox *checkBoxPyramide;
    QCheckBox *checkBoxSphere;
    QCheckBox *checkBoxTorus;
    QCheckBox *checkBoxTeapot;
    QCheckBox *checkBoxNormal;
    QCheckBox *checkBoxHideShape;

    //QLabel
    QLabel *labelHomothetie;
    QLabel *labelTesselation;
    QLabel *labelRouge;
    QLabel *labelVert;
    QLabel *labelBleu;
    QLabel *labelCouleur;
    QLabel *labelTranslation;
    QLabel *labelTranslationX;
    QLabel *labelTranslationY;
    QLabel *labelTranslationZ;
    QLabel *labelRotation;
    QLabel *labelRotationX;
    QLabel *labelRotationY;
    QLabel *labelRotationZ;

    //QHBoxLayout
    QHBoxLayout *layoutHomothetie;
    QHBoxLayout *layoutTesselation;
    QHBoxLayout *layoutTranslationX;
    QHBoxLayout *layoutTranslationY;
    QHBoxLayout *layoutTranslationZ;
    QHBoxLayout *layoutRotationX;
    QHBoxLayout *layoutRotationY;
    QHBoxLayout *layoutRotationZ;
    QHBoxLayout *layoutRouge;
    QHBoxLayout *layoutVert;
    QHBoxLayout *layoutBleu;
    QHBoxLayout *lightPositionLayout;
    QHBoxLayout *layoutLight;
    QHBoxLayout *mainLayout;

    //QVBoxLayout
    QVBoxLayout *layoutRotation;
    QVBoxLayout *layoutBoutonsForme;
    QVBoxLayout *layoutTranslation;
    QVBoxLayout *layoutCouleur;
    QVBoxLayout *layoutVisuel;
    QVBoxLayout *paramsLayout;

    //QWidget
    QWidget *colorWidget;
    QWidget *formeWidget;
    QWidget *visualisationWidget;
    QWidget *lightWidget;

private slots:
    void changeSize(int value);
    void changeShapeWithTesselation(int value);
    void createCube();
    void createPyramide();
    void changeTexture();
    void createSphere();
    void createTorus();
    void createSuzanne();
    void changeColor();
    void changeRotationX();
    void changeRotationY();
    void changeRotationZ();
    void changePosition();
    void changeLightPosition();
    void showNormal();
    void hideShape();
    void selectShape();
};

#endif // FRAME_H
