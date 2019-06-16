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
#include <QtMath>

#include "MainWidget.h"
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
    QRadioButton *rbColorNormal;
    QRadioButton *rbBandeNoireBlanche;
    QRadioButton *rbDamier;
    QRadioButton *rbBallonPlage;
    QRadioButton *rbBallonEtoile;

    //QSlider
    QSlider *sliderHomothetieX;
    QSlider *sliderHomothetieY;
    QSlider *sliderHomothetieZ;
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
    QSlider *sliderLightX;
    QSlider *sliderLightY;
    QSlider *sliderLightZ;
    QSlider *sliderLightColorRed;
    QSlider *sliderLightColorGreen;
    QSlider *sliderLightColorBlue;
    QSlider *sliderNear;
    QSlider *sliderFar;
    QSlider *sliderCameraInclinaison;

    //QCheckBox
    QCheckBox *checkBoxSelectionCube;
    QCheckBox *checkBoxSelectionArrow;
    QCheckBox *checkBoxSelectionPlane;
    QCheckBox *checkBoxSelectionPyramide;
    QCheckBox *checkBoxSelectionSphere;
    QCheckBox *checkBoxSelectionTorus;
    QCheckBox *checkBoxSelectionTeapot;
    QCheckBox *checkBoxShowCube;
    QCheckBox *checkBoxShowArrow;
    QCheckBox *checkBoxShowPlane;
    QCheckBox *checkBoxShowPyramide;
    QCheckBox *checkBoxShowSphere;
    QCheckBox *checkBoxShowTorus;
    QCheckBox *checkBoxShowTeapot;
    QCheckBox *checkBoxNormalsCube;
    QCheckBox *checkBoxNormalsArrow;
    QCheckBox *checkBoxNormalsPlane;
    QCheckBox *checkBoxNormalsPyramide;
    QCheckBox *checkBoxNormalsSphere;
    QCheckBox *checkBoxNormalsTorus;
    QCheckBox *checkBoxNormalsTeapot;

    //QLabel
    QLabel *labelSelectionForms;
    QLabel *labelForms;
    QLabel *labelCube;
    QLabel *labelArrow;
    QLabel *labelPlane;
    QLabel *labelPyramide;
    QLabel *labelSphere;
    QLabel *labelTorus;
    QLabel *labelTeapot;
    QLabel *labelNormal;
    QLabel *labelHideShape;
    QLabel *labelHomothetie;
    QLabel *labelHomothetieX;
    QLabel *labelHomothetieY;
    QLabel *labelHomothetieZ;
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
    QLabel *labelLightX;
    QLabel *labelLightY;
    QLabel *labelLightZ;
    QLabel *labelLightColorRed;
    QLabel *labelLightColorBlue;
    QLabel *labelLightColorGreen;
    QLabel *labelLightColor;
    QLabel *labelLightPosition;
    QLabel *labelNear;
    QLabel *labelFar;
    QLabel *labelCameraInclinaison;

    //QHBoxLayout
    QHBoxLayout *layoutTesselation;
    QHBoxLayout *layoutTranslationX;
    QHBoxLayout *layoutTranslationY;
    QHBoxLayout *layoutTranslationZ;
    QHBoxLayout *layoutHomothetieX;
    QHBoxLayout *layoutHomothetieY;
    QHBoxLayout *layoutHomothetieZ;
    QHBoxLayout *layoutRotationX;
    QHBoxLayout *layoutRotationY;
    QHBoxLayout *layoutRotationZ;
    QHBoxLayout *layoutRouge;
    QHBoxLayout *layoutVert;
    QHBoxLayout *layoutBleu;
    QHBoxLayout *lightPositionLayout;
    QHBoxLayout *mainLayout;
    QHBoxLayout *layoutLightX;
    QHBoxLayout *layoutLightY;
    QHBoxLayout *layoutLightZ;
    QHBoxLayout *layoutLightColorRed;
    QHBoxLayout *layoutLightColorGreen;
    QHBoxLayout *layoutLightColorBlue;
    QHBoxLayout *layoutNear;
    QHBoxLayout *layoutFar;
    QHBoxLayout *layoutCameraInclinaison;

    //QVBoxLayout
    QVBoxLayout *layoutHomothetie;
    QVBoxLayout *layoutRotation;
    QVBoxLayout *layoutTranslation;
    QVBoxLayout *layoutCouleur;
    QVBoxLayout *layoutVisuel;
    QVBoxLayout *paramsLayout;
    QVBoxLayout *layoutLight;
    QVBoxLayout *layoutCamera;

    //QGridLayout
    QGridLayout *layoutShapes;

    //QWidget
    QWidget *colorWidget;
    QWidget *formeWidget;
    QWidget *visualisationWidget;
    QWidget *lightWidget;
    QWidget *cameraWidget;

private slots:
    void changeSize();
    void changeShapeWithTesselation(int value);
    void changeColor();
    void changeRotationX();
    void changeRotationY();
    void changeRotationZ();
    void changePosition();
    void changeLightPosition();
    void changeAmbientColor();
    void changeCameraPositionNear();
    void changeCameraPositionFar();
    void changeCameraPositionFov();
    void showNormal();
    void hideShape();
    void selectShape();
};

#endif // FRAME_H
