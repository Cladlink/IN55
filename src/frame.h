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
//#include "parameter.h"

using namespace std;

class Frame : public QWidget
{
    Q_OBJECT

public:
    explicit Frame();

private:
    MainWidget *scene3D;
    QTextEdit *edit = new QTextEdit();

private slots:
    void ouvrirMessageBox(int value);
    void createCube();
    void createPyramide();
    void changeTextureNintendo();
    void changeTextureMur();
};

#endif // FRAME_H
