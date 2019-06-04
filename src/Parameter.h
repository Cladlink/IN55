#ifndef PARAMETER_H
#define PARAMETER_H

#include "MainWidget.h"

class parameter
{
public:
    parameter();
    static void setGeometries(MainWidget *scene3D);
    static void setValue(int value);

private:
    static MainWidget *scene3D;
};

MainWidget *parameter::scene3D;

#endif // PARAMETER_H
