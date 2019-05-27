#include "frame.h"

using namespace std;

Frame::Frame()
{
    scene3D = new MainWidget();
    scene3D->setFixedSize(900, 700);

    // Boutons
    boutonCube = new QPushButton("Cube");
    boutonPyramide = new QPushButton("Pyramide");
    boutonSphere = new QPushButton("Sphere");
    boutonTorus = new QPushButton("Torus");
    boutonSuzanne = new QPushButton("Suzanne");

    // Homothétie
    sliderHomothetie = new QSlider(Qt::Horizontal);
    sliderHomothetie->setMinimum(1);
    sliderHomothetie->setMaximum(4);

    labelHomothetie = new QLabel("Taille : ");
    labelHomothetie->setFixedSize(100,30);

    layoutHomothetie = new QHBoxLayout;
    layoutHomothetie->addWidget(labelHomothetie);
    layoutHomothetie->addWidget(sliderHomothetie);

    // Couleurs
    rbColor = new QRadioButton("Couleur", this);

    labelRouge = new QLabel("Rouge : ");
    labelRouge->setFixedSize(100,30);
    sliderRouge = new QSlider(Qt::Horizontal);
    sliderRouge->setMinimum(0);
    sliderRouge->setMaximum(255);
    sliderRouge->setValue(255);
    layoutRouge = new QHBoxLayout;
    layoutRouge->insertSpacing(0, 20);
    layoutRouge->addWidget(labelRouge);
    layoutRouge->addWidget(sliderRouge);

    labelVert = new QLabel("Vert : ");
    labelVert->setFixedSize(100,30);
    sliderVert = new QSlider(Qt::Horizontal);
    sliderVert->setMinimum(0);
    sliderVert->setMaximum(255);
    sliderVert->setValue(255);
    layoutVert = new QHBoxLayout;
    layoutVert->insertSpacing(0, 20);
    layoutVert->addWidget(labelVert);
    layoutVert->addWidget(sliderVert);

    labelBleu = new QLabel("Bleu : ");
    labelBleu->setFixedSize(100,30);
    sliderBleu = new QSlider(Qt::Horizontal);
    sliderBleu->setMinimum(0);
    sliderBleu->setMaximum(255);
    sliderBleu->setValue(255);
    layoutBleu = new QHBoxLayout;
    layoutBleu->insertSpacing(0, 20);
    layoutBleu->addWidget(labelBleu);
    layoutBleu->addWidget(sliderBleu);

    rbMulticolorVertices = new QRadioButton("Multicolor vertices", this);
    rbMulticolorFragments = new QRadioButton("Multicolor fragments", this);
    rbColorNormal = new QRadioButton("Couleur en fonction des normales", this);
    rbMur = new QRadioButton("Mur en briques", this);
    rbMur->setChecked(true);
    rbNintendo = new QRadioButton("Nintendo", this);
    labelCouleur = new QLabel("Couleurs et textures :");
    labelCouleur->setFixedSize(150,30);

    layoutCouleur = new QVBoxLayout;
    layoutCouleur->addWidget(labelCouleur);
    layoutCouleur->addWidget(rbColor);
    layoutCouleur->addLayout(layoutRouge);
    layoutCouleur->addLayout(layoutVert);
    layoutCouleur->addLayout(layoutBleu);
    layoutCouleur->addWidget(rbMulticolorVertices);
    layoutCouleur->addWidget(rbMulticolorFragments);
    layoutCouleur->addWidget(rbColorNormal);
    layoutCouleur->addWidget(rbMur);
    layoutCouleur->addWidget(rbNintendo);

    // Translation
    layoutTranslation = new QVBoxLayout;

    rbTranslation = new QRadioButton("Translation", this);
    rbTranslation->setChecked(true);

    labelTranslationX = new QLabel("X : ");
    labelTranslationX->setFixedSize(30,30);
    sliderTranslationX = new QSlider(Qt::Horizontal);
    sliderTranslationX->setMinimum(-5.0);
    sliderTranslationX->setMaximum(5.0);
    sliderTranslationX->setValue(0);
    layoutTranslationX = new QHBoxLayout;
    layoutTranslationX->insertSpacing(0, 10);
    layoutTranslationX->addWidget(labelTranslationX);
    layoutTranslationX->addWidget(sliderTranslationX);

    labelTranslationY = new QLabel("Y : ");
    labelTranslationY->setFixedSize(30,30);
    sliderTranslationY = new QSlider(Qt::Horizontal);
    sliderTranslationY->setMinimum(-5.0);
    sliderTranslationY->setMaximum(5.0);
    sliderTranslationY->setValue(0);
    layoutTranslationY = new QHBoxLayout;
    layoutTranslationY->insertSpacing(0, 10);
    layoutTranslationY->addWidget(labelTranslationY);
    layoutTranslationY->addWidget(sliderTranslationY);

    labelTranslationZ = new QLabel("Z : ");
    labelTranslationZ->setFixedSize(30,30);
    sliderTranslationZ = new QSlider(Qt::Horizontal);
    sliderTranslationZ->setMinimum(-10.0);
    sliderTranslationZ->setMaximum(0.0);
    sliderTranslationZ->setValue(-5.0);
    layoutTranslationZ = new QHBoxLayout;
    layoutTranslationZ->insertSpacing(0, 10);
    layoutTranslationZ->addWidget(labelTranslationZ);
    layoutTranslationZ->addWidget(sliderTranslationZ);

    labelTranslation = new QLabel("Translation :");
    labelTranslation->setFixedSize(150,30);

    layoutTranslation->addWidget(labelTranslation);
    layoutTranslation->addWidget(rbTranslation);
    layoutTranslation->addLayout(layoutTranslationX);
    layoutTranslation->addLayout(layoutTranslationY);
    layoutTranslation->addLayout(layoutTranslationZ);

    // Rotation
    layoutRotation = new QHBoxLayout;

    mouseRotation = new QRadioButton("Mouse");
    xRotation = new QRadioButton("X");
    yRotation = new QRadioButton("Y");
    zRotation = new QRadioButton("Z");

    layoutCouleur->addWidget(mouseRotation);
    layoutCouleur->addWidget(xRotation);
    layoutCouleur->addWidget(yRotation);
    layoutCouleur->addWidget(zRotation);

    // Formes
    layoutBoutonsForme = new QHBoxLayout;
    layoutBoutonsForme->addWidget(boutonCube);
    layoutBoutonsForme->addWidget(boutonPyramide);
    QHBoxLayout *layoutBoutonsForme2 = new QHBoxLayout;
    layoutBoutonsForme2->addWidget(boutonSphere);
    layoutBoutonsForme2->addWidget(boutonTorus);
    QHBoxLayout *layoutBoutonsForme3 = new QHBoxLayout;
    layoutBoutonsForme3->addWidget(boutonSuzanne);

    // Général
    mainLayout = new QHBoxLayout;
    paramsLayout = new QVBoxLayout;

    // Ajout des éléments au layout des paramètres
    paramsLayout->addLayout(layoutHomothetie);
    paramsLayout->addLayout(layoutTranslation);
    paramsLayout->addLayout(layoutCouleur);
    paramsLayout->addLayout(layoutBoutonsForme);
    paramsLayout->addLayout(layoutBoutonsForme2);
    paramsLayout->addLayout(layoutBoutonsForme3);
    paramsLayout->addLayout(layoutRotation);

    mainLayout->addWidget(scene3D);
    mainLayout->addLayout(paramsLayout);

    this->setLayout(mainLayout);

    // Listener des boutons
    QObject::connect(sliderHomothetie, SIGNAL(valueChanged(int)), this, SLOT(changeSize(int)));

    QObject::connect(boutonCube, SIGNAL(clicked()), this, SLOT(createCube()));
    QObject::connect(boutonPyramide, SIGNAL(clicked()), this, SLOT(createPyramide()));
    QObject::connect(boutonSphere, SIGNAL(clicked()), this, SLOT(createSphere()));
    QObject::connect(boutonTorus, SIGNAL(clicked()), this, SLOT(createTorus()));
    QObject::connect(boutonSuzanne, SIGNAL(clicked()), this, SLOT(createSuzanne()));

    QObject::connect(rbNintendo, SIGNAL(clicked()), this, SLOT(changeTexture()));
    QObject::connect(rbMur, SIGNAL(clicked()), this, SLOT(changeTexture()));

    QObject::connect(rbMulticolorVertices, SIGNAL(clicked()), this, SLOT(changeColor()));
    QObject::connect(rbMulticolorFragments, SIGNAL(clicked()), this, SLOT(changeColor()));
    QObject::connect(rbColorNormal, SIGNAL(clicked()), this, SLOT(changeColor()));
    QObject::connect(rbColor, SIGNAL(clicked()), this, SLOT(changeColor()));
    QObject::connect(sliderRouge, SIGNAL(valueChanged(int)), this, SLOT(changeColor()));
    QObject::connect(sliderVert, SIGNAL(valueChanged(int)), this, SLOT(changeColor()));
    QObject::connect(sliderBleu, SIGNAL(valueChanged(int)), this, SLOT(changeColor()));

    QObject::connect(sliderTranslationX, SIGNAL(valueChanged(int)), this, SLOT(changePosition()));
    QObject::connect(sliderTranslationY, SIGNAL(valueChanged(int)), this, SLOT(changePosition()));
    QObject::connect(sliderTranslationZ, SIGNAL(valueChanged(int)), this, SLOT(changePosition()));

    QObject::connect(mouseRotation, SIGNAL(clicked()), this, SLOT(changeRotation()));
    QObject::connect(xRotation, SIGNAL(clicked()), this, SLOT(changeRotation()));
    QObject::connect(yRotation, SIGNAL(clicked()), this, SLOT(changeRotation()));
    QObject::connect(zRotation, SIGNAL(clicked()), this, SLOT(changeRotation()));

    // Affiche un cube avec la texture 'mur' par défault au lancement de l'application
    createCube();
    changeTexture();
}

void Frame::changeSize(int value) {
    scene3D->setHomotethie(value/2.0f);
};

void Frame::createCube() {
    scene3D->setObject("cube");
    scene3D->setNbObjects(1);
};

void Frame::createPyramide() {
    scene3D->setObject("pyramide");
    scene3D->setNbObjects(1);
};

void Frame::createSphere() {
    scene3D->setObject("sphere");
    scene3D->setNbObjects(1);
};

void Frame::createTorus() {
    scene3D->setObject("torus");
    scene3D->setNbObjects(1);
};

void Frame::createSuzanne() {
    scene3D->setObject("suzanne");
    scene3D->setNbObjects(1);
};

void Frame::changeTexture() {
    scene3D->setIsColor(0);
    if (rbMur->isChecked()) {
        scene3D->setNumberBufferTexture(0);
        scene3D->setPathTexture(":/mur.png");
    } else if(rbNintendo->isChecked()) {
        scene3D->setNumberBufferTexture(1);
        scene3D->setPathTexture(":/nintendo.png");
    } else {
        scene3D->setNumberBufferTexture(0);
        scene3D->setPathTexture(":/mur.png");
    }
};

void Frame::changeColor() {
    if(rbColor->isChecked()){
        scene3D->setIsColor(1);
        float r = sliderRouge->value() / 255.0f;
        float g = sliderVert->value() / 255.0f;
        float b = sliderBleu->value() / 255.0f;
        scene3D->setColor(QVector3D(r,g,b));
    } else if(rbMulticolorVertices->isChecked()) {
        scene3D->setIsColor(2);
    } else if(rbMulticolorFragments->isChecked()) {
        scene3D->setIsColor(3);
    } else if(rbColorNormal->isChecked()) {
        scene3D->setIsColor(4);
    }
}

void Frame::changePosition() {
    if(rbTranslation->isChecked()){
        float x = sliderTranslationX->value();
        float y = sliderTranslationY->value();
        float z = sliderTranslationZ->value();
        scene3D->setPosition(QVector3D(x,y,z));
    }
}

void Frame::changeRotation() {
    if(mouseRotation->isChecked()){
        scene3D->setAxeRotation(0);
    } else if(xRotation->isChecked()){
        scene3D->setAxeRotation(1);
    } else if(yRotation->isChecked()){
        scene3D->setAxeRotation(2);
    } else if(zRotation->isChecked()){
        scene3D->setAxeRotation(3);
    }
}
