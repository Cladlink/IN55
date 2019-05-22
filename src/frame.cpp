#include "frame.h"

using namespace std;

Frame::Frame()
{
    scene3D = new MainWidget();
    scene3D->setFixedSize(700, 500);
//    parameter::setGeometries(scene3D);

    QPushButton *bouton = new QPushButton("Test");

    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(1);
    slider->setMaximum(4);

    QLabel *label = new QLabel();
    label->setText("Entrez texte :");
    label->setFixedSize(100,30);
    edit->setFixedSize(100,30);

    QLabel *label2 = new QLabel();
    label2->setText("Entrez texte :");
    label2->setFixedSize(100,30);
    QTextEdit *edit2 = new QTextEdit();
    edit2->setFixedSize(100,30);

    QHBoxLayout *test = new QHBoxLayout;
    test->addWidget(label);
    test->addWidget(edit);

    QHBoxLayout *test2 = new QHBoxLayout;
    test2->addWidget(label2);
    test2->addWidget(edit2);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    QVBoxLayout *paramsLayout = new QVBoxLayout;

    paramsLayout->addWidget(slider);
    paramsLayout->addLayout(test);
    paramsLayout->addLayout(test2);
    paramsLayout->addWidget(bouton);

    mainLayout->addWidget(scene3D);
    mainLayout->addLayout(paramsLayout);

    this->setLayout(mainLayout);

    QObject::connect(slider, SIGNAL(valueChanged(int)), this, SLOT(ouvrirMessageBox(int)));
}

void Frame::ouvrirMessageBox(int value) {
    edit->setText(QString::number(value));
    scene3D->setValue(value/2.0f);
};

