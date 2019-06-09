#include "Frame.h"

using namespace std;

Frame::Frame()
{
    scene3D = new MainWidget(&myLight);
    scene3D->setFixedSize(900, 700);

    // Tab
    optionsTab = new QTabWidget();

    // Formes
    checkBoxCube = new QCheckBox("Cube");
    checkBoxCube->setCheckState(Qt::Checked);
    checkBoxArrow = new QCheckBox("Arrow");
    checkBoxArrow->setCheckState(Qt::Checked);
    checkBoxPlane = new QCheckBox("Plane");
    checkBoxPlane->setCheckState(Qt::Checked);
    checkBoxPyramide = new QCheckBox("Pyramide");
    checkBoxPyramide->setCheckState(Qt::Checked);
    checkBoxSphere = new QCheckBox("Sphere");
    checkBoxSphere->setCheckState(Qt::Checked);
    checkBoxTeapot = new QCheckBox("Teapot");
    checkBoxTeapot->setCheckState(Qt::Checked);
    checkBoxNormal = new QCheckBox("Normal");
    checkBoxNormal->setCheckState(Qt::Unchecked);
    checkBoxHideShape = new QCheckBox("Hide Shape");
    checkBoxHideShape->setCheckState(Qt::Unchecked);

    layoutBoutonsForme = new QVBoxLayout;
    layoutBoutonsForme->addWidget(checkBoxCube);
    layoutBoutonsForme->addWidget(checkBoxArrow);
    layoutBoutonsForme->addWidget(checkBoxPlane);
    layoutBoutonsForme->addWidget(checkBoxPyramide);
    layoutBoutonsForme->addWidget(checkBoxSphere);
    layoutBoutonsForme->addWidget(checkBoxTeapot);
    layoutBoutonsForme->addWidget(checkBoxHideShape);
    //layoutBoutonsForme->addWidget(checkBoxNormal);

    // Homothétie
    labelHomothetieX = new QLabel("X : ");
    labelHomothetieX->setFixedSize(100,30);
    sliderHomothetieX = new QSlider(Qt::Horizontal);
    sliderHomothetieX->setMinimum(1);
    sliderHomothetieX->setMaximum(4);
    layoutHomothetieX = new QHBoxLayout;
    layoutHomothetieX->insertSpacing(0, 10);
    layoutHomothetieX->addWidget(labelHomothetieX);
    layoutHomothetieX->addWidget(sliderHomothetieX);

    labelHomothetieY = new QLabel("Y : ");
    labelHomothetieY->setFixedSize(100,30);
    sliderHomothetieY = new QSlider(Qt::Horizontal);
    sliderHomothetieY->setMinimum(1);
    sliderHomothetieY->setMaximum(4);
    layoutHomothetieY = new QHBoxLayout;
    layoutHomothetieY->insertSpacing(0, 10);
    layoutHomothetieY->addWidget(labelHomothetieY);
    layoutHomothetieY->addWidget(sliderHomothetieY);

    labelHomothetieZ = new QLabel("Z : ");
    labelHomothetieZ->setFixedSize(100,30);
    sliderHomothetieZ = new QSlider(Qt::Horizontal);
    sliderHomothetieZ->setMinimum(1);
    sliderHomothetieZ->setMaximum(4);
    layoutHomothetieZ = new QHBoxLayout;
    layoutHomothetieZ->insertSpacing(0, 10);
    layoutHomothetieZ->addWidget(labelHomothetieZ);
    layoutHomothetieZ->addWidget(sliderHomothetieZ);

    labelHomothetie = new QLabel("Taille : ");
    labelHomothetie->setFixedSize(100,30);

    layoutHomothetie = new QVBoxLayout;
    layoutHomothetie->addWidget(labelHomothetie);
    layoutHomothetie->addLayout(layoutHomothetieX);
    layoutHomothetie->addLayout(layoutHomothetieY);
    layoutHomothetie->addLayout(layoutHomothetieZ);

    // Tesselation
    sliderTesselation = new QSlider(Qt::Horizontal);
    sliderTesselation->setMinimum(5);
    sliderTesselation->setMaximum(50);

    labelTesselation = new QLabel("Tesselation : ");
    labelTesselation->setFixedSize(100,30);

    layoutTesselation = new QHBoxLayout;
    layoutTesselation->addWidget(labelTesselation);
    layoutTesselation->addWidget(sliderTesselation);

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

    labelTranslationX = new QLabel("X : ");
    labelTranslationX->setFixedSize(30,30);
    sliderTranslationX = new QSlider(Qt::Horizontal);
    sliderTranslationX->setMinimum(-100.0);
    sliderTranslationX->setTickInterval(1);
    sliderTranslationX->setMaximum(100.0);
    sliderTranslationX->setValue(0);
    layoutTranslationX = new QHBoxLayout;
    layoutTranslationX->insertSpacing(0, 10);
    layoutTranslationX->addWidget(labelTranslationX);
    layoutTranslationX->addWidget(sliderTranslationX);

    labelTranslationY = new QLabel("Y : ");
    labelTranslationY->setFixedSize(30,30);
    sliderTranslationY = new QSlider(Qt::Horizontal);
    sliderTranslationY->setMinimum(-100.0);
    sliderTranslationY->setTickInterval(1);
    sliderTranslationY->setMaximum(100.0);
    sliderTranslationY->setValue(0);
    layoutTranslationY = new QHBoxLayout;
    layoutTranslationY->insertSpacing(0, 10);
    layoutTranslationY->addWidget(labelTranslationY);
    layoutTranslationY->addWidget(sliderTranslationY);

    labelTranslationZ = new QLabel("Z : ");
    labelTranslationZ->setFixedSize(30,30);
    sliderTranslationZ = new QSlider(Qt::Horizontal);
    sliderTranslationZ->setMinimum(-100.0);
    sliderTranslationZ->setTickInterval(1);
    sliderTranslationZ->setMaximum(100.0);
    sliderTranslationZ->setValue(0.0);
    layoutTranslationZ = new QHBoxLayout;
    layoutTranslationZ->insertSpacing(0, 10);
    layoutTranslationZ->addWidget(labelTranslationZ);
    layoutTranslationZ->addWidget(sliderTranslationZ);

    labelTranslation = new QLabel("Translation :");
    labelTranslation->setFixedSize(150,30);

    layoutTranslation->addWidget(labelTranslation);
    layoutTranslation->addLayout(layoutTranslationX);
    layoutTranslation->addLayout(layoutTranslationY);
    layoutTranslation->addLayout(layoutTranslationZ);

    // Rotation
    layoutRotation = new QVBoxLayout;

    labelRotation = new QLabel("Rotation :");
    labelRotation->setFixedSize(150,30);

    labelRotationX = new QLabel("X : ");
    labelRotationX->setFixedSize(30,30);
    sliderRotationX = new QSlider(Qt::Horizontal);
    sliderRotationX->setMinimum(-180.);
    sliderRotationX->setTickInterval(1);
    sliderRotationX->setMaximum(180.);
    sliderRotationX->setValue(0);
    layoutRotationX = new QHBoxLayout;
    layoutRotationX->insertSpacing(0, 10);
    layoutRotationX->addWidget(labelRotationX);
    layoutRotationX->addWidget(sliderRotationX);

    labelRotationY = new QLabel("Y : ");
    labelRotationY->setFixedSize(30,30);
    sliderRotationY = new QSlider(Qt::Horizontal);
    sliderRotationY->setMinimum(0.);
    sliderRotationY->setTickInterval(1);
    sliderRotationY->setMaximum(360.);
    sliderRotationY->setValue(0);
    layoutRotationY = new QHBoxLayout;
    layoutRotationY->insertSpacing(0, 10);
    layoutRotationY->addWidget(labelRotationY);
    layoutRotationY->addWidget(sliderRotationY);

    labelRotationZ = new QLabel("Z : ");
    labelRotationZ->setFixedSize(30,30);
    sliderRotationZ = new QSlider(Qt::Horizontal);
    sliderRotationZ->setMinimum(0.);
    sliderRotationZ->setTickInterval(1);
    sliderRotationZ->setMaximum(360.);
    sliderRotationZ->setValue(0.0);
    layoutRotationZ = new QHBoxLayout;
    layoutRotationZ->insertSpacing(0, 10);
    layoutRotationZ->addWidget(labelRotationZ);
    layoutRotationZ->addWidget(sliderRotationZ);

    layoutRotation->addWidget(labelRotation);
    layoutRotation->addLayout(layoutRotationX);
    layoutRotation->addLayout(layoutRotationY);
    layoutRotation->addLayout(layoutRotationZ);

    /*layoutRotation->addWidget(labelRotation);
    layoutRotation->addWidget(mouseRotation);
    layoutRotation->addWidget(xRotation);
    layoutRotation->addWidget(yRotation);
    layoutRotation->addWidget(zRotation);*/

    /*mouseRotation = new QRadioButton("Mouse");
    xRotation = new QRadioButton("X");
    yRotation = new QRadioButton("Y");
    zRotation = new QRadioButton("Z");

    labelRotation = new QLabel("Rotation :");
    labelRotation->setFixedSize(150,30);

    layoutRotation->addWidget(labelRotation);
    layoutRotation->addWidget(mouseRotation);
    layoutRotation->addWidget(xRotation);
    layoutRotation->addWidget(yRotation);
    layoutRotation->addWidget(zRotation);*/

    layoutVisuel = new QVBoxLayout;
    layoutVisuel->addLayout(layoutTesselation);
    layoutVisuel->addLayout(layoutHomothetie);
    layoutVisuel->addLayout(layoutTranslation);
    layoutVisuel->addLayout(layoutRotation);

    //Lumière
    layoutLight = new QHBoxLayout;
    layoutLight->addLayout(lightPositionLayout = new QHBoxLayout);
    lightPositionLayout->addWidget(sliderLightX = new DebugSlider);
    lightPositionLayout->addWidget(sliderLightY = new DebugSlider);
    lightPositionLayout->addWidget(sliderLightZ = new DebugSlider);

    // Général
    rbMur->setChecked(true);
    //mouseRotation->setChecked(true);
    colorWidget = new QWidget;
    formeWidget = new QWidget;
    lightWidget = new QWidget;
    visualisationWidget = new QWidget;
    formeWidget->setLayout(layoutBoutonsForme);
    colorWidget->setLayout(layoutCouleur);
    visualisationWidget->setLayout(layoutVisuel);
    lightWidget->setLayout(layoutLight);
    optionsTab->addTab(colorWidget, "Couleur");
    optionsTab->addTab(formeWidget, "Formes");
    optionsTab->addTab(visualisationWidget, "Visuel");
    optionsTab->addTab(lightWidget, "Lumière");

    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(scene3D);
    mainLayout->addWidget(optionsTab);

    this->setLayout(mainLayout);

    // Listener des boutons
    QObject::connect(sliderHomothetieX, SIGNAL(valueChanged(int)), this, SLOT(changeSize()));
    QObject::connect(sliderHomothetieY, SIGNAL(valueChanged(int)), this, SLOT(changeSize()));
    QObject::connect(sliderHomothetieZ, SIGNAL(valueChanged(int)), this, SLOT(changeSize()));

    QObject::connect(sliderTesselation, SIGNAL(valueChanged(int)), this, SLOT(changeShapeWithTesselation(int)));

    QObject::connect(checkBoxCube, SIGNAL(stateChanged(int)), this, SLOT(selectShape()));
    QObject::connect(checkBoxArrow, SIGNAL(stateChanged(int)), this, SLOT(selectShape()));
    QObject::connect(checkBoxPlane, SIGNAL(stateChanged(int)), this, SLOT(selectShape()));
    QObject::connect(checkBoxPyramide, SIGNAL(stateChanged(int)), this, SLOT(selectShape()));
    QObject::connect(checkBoxSphere, SIGNAL(stateChanged(int)), this, SLOT(selectShape()));
    QObject::connect(checkBoxTeapot, SIGNAL(stateChanged(int)), this, SLOT(selectShape()));
    QObject::connect(checkBoxNormal, SIGNAL(stateChanged(int)), this, SLOT(showNormal()));
    QObject::connect(checkBoxHideShape, SIGNAL(stateChanged(int)), this, SLOT(hideShape()));

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

    QObject::connect(sliderRotationX, SIGNAL(valueChanged(int)), this, SLOT(changeRotationX()));
    QObject::connect(sliderRotationY, SIGNAL(valueChanged(int)), this, SLOT(changeRotationY()));
    QObject::connect(sliderRotationZ, SIGNAL(valueChanged(int)), this, SLOT(changeRotationZ()));

    //QObject::connect(mouseRotation, SIGNAL(clicked()), this, SLOT(changeRotation()));
    //QObject::connect(xRotation, SIGNAL(clicked()), this, SLOT(changeRotation()));
    //QObject::connect(yRotation, SIGNAL(clicked()), this, SLOT(changeRotation()));
    //QObject::connect(zRotation, SIGNAL(clicked()), this, SLOT(changeRotation()));

    QObject::connect(sliderLightX, SIGNAL(valueChanged(float)),this, SLOT(changeLightPosition()));
    QObject::connect(sliderLightY, SIGNAL(valueChanged(float)),this, SLOT(changeLightPosition()));
    QObject::connect(sliderLightZ, SIGNAL(valueChanged(float)),this, SLOT(changeLightPosition()));

    // Affiche un cube avec la texture 'mur' par défault au lancement de l'application
    //createCube();
    //changeTexture();
}

void Frame::changeSize() {
    float x = (sliderHomothetieX->value());
    float y = (sliderHomothetieY->value());
    float z = (sliderHomothetieZ->value());
    scene3D->setHomothetie(QVector3D(x,y,z));
};

void Frame::changeShapeWithTesselation(int value) {
    scene3D->setTesselation(value);
};

void Frame::selectShape() {
    if ((!checkBoxCube->isChecked() && scene3D->isShapeInMap("Cube")) || (checkBoxCube->isChecked() && !scene3D->isShapeInMap("Cube"))) {
        scene3D->selectShape("Cube");
    }

    if ((!checkBoxPyramide->isChecked() && scene3D->isShapeInMap("Pyramide")) || (checkBoxPyramide->isChecked() && !scene3D->isShapeInMap("Pyramide"))) {
        scene3D->selectShape("Pyramide");
    }

    if ((!checkBoxPlane->isChecked() && scene3D->isShapeInMap("Plane")) || (checkBoxPlane->isChecked() && !scene3D->isShapeInMap("Plane"))) {
        scene3D->selectShape("Plane");
    }

    if ((!checkBoxSphere->isChecked() && scene3D->isShapeInMap("Sphere")) || (checkBoxSphere->isChecked() && !scene3D->isShapeInMap("Sphere"))) {
        scene3D->selectShape("Sphere");
    }

    if ((!checkBoxTeapot->isChecked() && scene3D->isShapeInMap("Teapot")) || (checkBoxTeapot->isChecked() && !scene3D->isShapeInMap("Teapot"))) {
        scene3D->selectShape("Teapot");
    }

    if ((!checkBoxArrow->isChecked() && scene3D->isShapeInMap("Arrow")) || (checkBoxArrow->isChecked() && !scene3D->isShapeInMap("Arrow"))) {
        scene3D->selectShape("Arrow");
    }
}

void Frame::showNormal() {
    if (checkBoxNormal->isChecked()) {
        scene3D->showNormal(true);
    } else {
        scene3D->showNormal(false);
    }
}

void Frame::hideShape() {
    if (checkBoxHideShape->isChecked()) {
        scene3D->hideShape(1);
    } else {
        scene3D->hideShape(0);
    }
}

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
    float x = (sliderTranslationX->value()/100.f)*5.f;
    float y = (sliderTranslationY->value()/100.f)*5.f;
    float z = (sliderTranslationZ->value()/100.f)*5.f;
    scene3D->setPosition(QVector3D(x,y,z));
}

void Frame::changeRotationX() {
    float angle = (sliderRotationX->value()/360.0f);
    scene3D->setRotation(QQuaternion(angle,QVector3D(1.,0.,0.).normalized()));
}

void Frame::changeRotationY() {
    float angle = (sliderRotationY->value()/360.f);
    scene3D->setRotation(QQuaternion(angle,QVector3D(0.,1.,0.).normalized()));
}

void Frame::changeRotationZ() {
    float angle = (sliderRotationZ->value()/360.f);
    scene3D->setRotation(QQuaternion(angle,QVector3D(0.,0.,1.).normalized()));
}


/*if(mouseRotation->isChecked()){
    scene3D->setAxeRotation(0);
} else if(xRotation->isChecked()){
    scene3D->setAxeRotation(1);
} else if(yRotation->isChecked()){
    scene3D->setAxeRotation(2);
} else if(zRotation->isChecked()){
    scene3D->setAxeRotation(3);
}*/

void Frame::changeLightPosition()
{
    myLight.lightPosition.setX(sliderLightX->value());
    myLight.lightPosition.setY(sliderLightY->value());
    myLight.lightPosition.setZ(sliderLightZ->value());
    scene3D->repaint();
}
