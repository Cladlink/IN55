#include "frame.h"

using namespace std;

Frame::Frame()
{
    scene3D = new MainWidget();
    scene3D->setFixedSize(700, 500);
//    parameter::setGeometries(scene3D);

    // Boutons
    QPushButton *boutonCube = new QPushButton("Cube");
    QPushButton *boutonPyramide = new QPushButton("Pyramide");

    // Homothétie
    QSlider *sliderHomothetie = new QSlider(Qt::Horizontal);
    sliderHomothetie->setMinimum(1);
    sliderHomothetie->setMaximum(4);

    QLabel *labelHomothetie = new QLabel("Entrez texte :");
    labelHomothetie->setFixedSize(100,30);
    edit->setFixedSize(100,30);

    QHBoxLayout *layoutHomothetie = new QHBoxLayout;
    layoutHomothetie->addWidget(labelHomothetie);
    layoutHomothetie->addWidget(edit);

    // Couleurs
    QRadioButton *rbRouge = new QRadioButton("Rouge", this);
    QRadioButton *rbVert = new QRadioButton("Vert", this);
    QRadioButton *rbBleu = new QRadioButton("Bleu", this);
    QRadioButton *rbMulticolor = new QRadioButton("Multicolor", this);
    QRadioButton *rbMur = new QRadioButton("Mur en briques", this);
    rbMur->setChecked(true);
    QRadioButton *rbNintendo = new QRadioButton("Nintendo", this);
    QLabel *labelCouleur = new QLabel("Couleurs et textures :");
    labelCouleur->setFixedSize(100,30);

    QVBoxLayout *layoutCouleur = new QVBoxLayout;
    layoutCouleur->addWidget(labelCouleur);
    layoutCouleur->addWidget(rbRouge);
    layoutCouleur->addWidget(rbVert);
    layoutCouleur->addWidget(rbBleu);
    layoutCouleur->addWidget(rbMulticolor);
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
    paramsLayout->addWidget(sliderHomothetie);
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

    // Affiche un cube avec la texture 'mur' par défault au lancement de l'application
    createCube();
    changeTextureMur();
}

void Frame::ouvrirMessageBox(int value) {
    edit->setText(QString::number(value));
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
    scene3D->setPathTexture(":/nintendo.png");
};

void Frame::changeTextureMur() {
    scene3D->setPathTexture(":/mur.png");
};

