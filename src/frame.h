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
    QTextEdit *edit = new QTextEdit();
    QRadioButton *rbColor;
    colorTextEdit *rouge;
    colorTextEdit *vert;
    colorTextEdit *bleu;
    QRadioButton *rbMulticolorVertices;
    QRadioButton *rbMulticolorFragments;
    QRadioButton *rbMur;
    QRadioButton *rbNintendo;
    QPushButton *boutonCube;
    QPushButton *boutonPyramide;
    QSlider *sliderHomothetie;
    //colorTextEdit *bleu;

private slots:
    void ouvrirMessageBox(int value);
    void createCube();
    void createPyramide();
    void changeTextureNintendo();
    void changeTextureMur();
    void changeColorRed();
    void changeColorGreen();
    void changeColorBlue();
    void changeColor();
};

#endif // FRAME_H
