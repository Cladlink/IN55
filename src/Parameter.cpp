#include "Parameter.h"

parameter::parameter()
{

}

void parameter::setGeometries(MainWidget *_scene3D) {
    parameter::scene3D = new MainWidget();
    scene3D = _scene3D;
}
