#include "frame.h"

using namespace std;

Frame::Frame()
{
    scene3D = new MainWidget();
    scene3D->setFixedSize(700, 500);
//    parameter::setGeometries(scene3D);

    // Boutons
    boutonCube = new QPushButton("Cube");
    boutonPyramide = new QPushButton("Pyramide");

    // Homothétie
    sliderHomothetie = new QSlider(Qt::Horizontal);
    sliderHomothetie->setMinimum(1);
    sliderHomothetie->setMaximum(4);

    QLabel *labelHomothetie = new QLabel("Taille : ");
    labelHomothetie->setFixedSize(100,30);

    QHBoxLayout *layoutHomothetie = new QHBoxLayout;
    layoutHomothetie->addWidget(labelHomothetie);
    layoutHomothetie->addWidget(sliderHomothetie);

    // Couleurs
    rbColor = new QRadioButton("Couleur", this);

    QLabel *labelRouge = new QLabel("Rouge : ");
    labelRouge->setFixedSize(100,30);
    rouge = new QSlider(Qt::Horizontal);
    rouge->setMinimum(0);
    rouge->setMaximum(255);
    rouge->setValue(255);
    QHBoxLayout *layoutRouge = new QHBoxLayout;
    layoutRouge->insertSpacing(0, 20);
    layoutRouge->addWidget(labelRouge);
    layoutRouge->addWidget(rouge);

    QLabel *labelVert = new QLabel("Vert : ");
    labelVert->setFixedSize(100,30);
    vert = new QSlider(Qt::Horizontal);
    vert->setMinimum(0);
    vert->setMaximum(255);
    vert->setValue(255);
    QHBoxLayout *layoutVert = new QHBoxLayout;
    layoutVert->insertSpacing(0, 20);
    layoutVert->addWidget(labelVert);
    layoutVert->addWidget(vert);

    QLabel *labelBleu = new QLabel("Bleu : ");
    labelBleu->setFixedSize(100,30);
    bleu = new QSlider(Qt::Horizontal);
    bleu->setMinimum(0);
    bleu->setMaximum(255);
    bleu->setValue(255);
    QHBoxLayout *layoutBleu = new QHBoxLayout;
    layoutBleu->insertSpacing(0, 20);
    layoutBleu->addWidget(labelBleu);
    layoutBleu->addWidget(bleu);

    rbMulticolorVertices = new QRadioButton("Multicolor vertices", this);
    rbMulticolorFragments = new QRadioButton("Multicolor fragments", this);
    rbMur = new QRadioButton("Mur en briques", this);
    rbMur->setChecked(true);
    rbNintendo = new QRadioButton("Nintendo", this);
    QLabel *labelCouleur = new QLabel("Couleurs et textures :");
    labelCouleur->setFixedSize(150,30);

    QVBoxLayout *layoutCouleur = new QVBoxLayout;
    layoutCouleur->addWidget(labelCouleur);
    layoutCouleur->addWidget(rbColor);
    layoutCouleur->addLayout(layoutRouge);
    layoutCouleur->addLayout(layoutVert);
    layoutCouleur->addLayout(layoutBleu);
    layoutCouleur->addWidget(rbMulticolorVertices);
    layoutCouleur->addWidget(rbMulticolorFragments);
    layoutCouleur->addWidget(rbMur);
    layoutCouleur->addWidget(rbNintendo);

    // Formes
    QHBoxLayout *layoutBoutonsForme = new QHBoxLayout;
    layoutBoutonsForme->addWidget(boutonCube);
    layoutBoutonsForme->addWidget(boutonPyramide);

    // Général
    QHBoxLayout *mainLayout = new QHBoxLayout;
    QVBoxLayout *paramsLayout = new QVBoxLayout;

    // Ajout des éléments au layout des paramètres
    paramsLayout->addLayout(layoutHomothetie);
    paramsLayout->addLayout(layoutCouleur);
    paramsLayout->addLayout(layoutBoutonsForme);

    mainLayout->addWidget(scene3D);
    mainLayout->addLayout(paramsLayout);

    this->setLayout(mainLayout);

    // Listener des boutons
    QObject::connect(sliderHomothetie, SIGNAL(valueChanged(int)), this, SLOT(ouvrirMessageBox(int)));
    QObject::connect(boutonCube, SIGNAL(clicked()), this, SLOT(createCube()));
    QObject::connect(boutonPyramide, SIGNAL(clicked()), this, SLOT(createPyramide()));
    QObject::connect(rbNintendo, SIGNAL(clicked()), this, SLOT(changeTextureNintendo()));
    QObject::connect(rbMur, SIGNAL(clicked()), this, SLOT(changeTextureMur()));
    QObject::connect(rbMulticolorVertices, SIGNAL(clicked()), this, SLOT(changeColor()));
    QObject::connect(rbMulticolorFragments, SIGNAL(clicked()), this, SLOT(changeColor()));
    QObject::connect(rbColor, SIGNAL(clicked()), this, SLOT(changeColor()));
    QObject::connect(rouge, SIGNAL(valueChanged(int)), this, SLOT(changeColor()));
    QObject::connect(vert, SIGNAL(valueChanged(int)), this, SLOT(changeColor()));
    QObject::connect(bleu, SIGNAL(valueChanged(int)), this, SLOT(changeColor()));

    // Affiche un cube avec la texture 'mur' par défault au lancement de l'application
    createCube();
    changeTextureMur();
}

void Frame::ouvrirMessageBox(int value) {
    scene3D->setValue(value/2.0f);
};

void Frame::createCube() {
    scene3D->setObject("cube");
    scene3D->setNbObjects(1);
};

void Frame::createPyramide() {
    scene3D->setObject("pyramide");
    scene3D->setNbObjects(1);
};

void Frame::changeTextureNintendo() {
    scene3D->setIsColor(0);
    scene3D->setNumberBufferTexture(1);
    scene3D->setPathTexture(":/nintendo.png");
};

void Frame::changeTextureMur() {
    scene3D->setIsColor(0);
    scene3D->setNumberBufferTexture(0);
    scene3D->setPathTexture(":/mur.png");
};

void Frame::changeColorRed() {
    scene3D->setIsColor(1);
    scene3D->setColor(QVector3D(1.f,0.f,0.f));
}

void Frame::changeColorGreen() {
    scene3D->setIsColor(1);
    scene3D->setColor(QVector3D(0.f,1.f,0.f));
}

void Frame::changeColorBlue() {
    scene3D->setIsColor(1);
    scene3D->setColor(QVector3D(0.f,0.f,1.f));
}

void Frame::changeColor() {
    if(rbColor->isChecked()){
        scene3D->setIsColor(1);
        float r = rouge->value() / 255.0f;
        float g = vert->value() / 255.0f;
        float b = bleu->value() / 255.0f;
        scene3D->setColor(QVector3D(r,g,b));
    } else if(rbMulticolorVertices->isChecked()) {
        scene3D->setIsColor(2);
    } else if(rbMulticolorFragments->isChecked()) {
        scene3D->setIsColor(3);
    }
}

