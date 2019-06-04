#ifndef COLORTEXTEDIT_H
#define COLORTEXTEDIT_H

#include <QTextEdit>
#include <QDebug>
#include <QKeyEvent>
#include <iostream>
#include <string>

using namespace std;

class colorTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    colorTextEdit(QString _value);
    void keyPressEvent(QKeyEvent *e);
};

#endif // COLORTEXTEDIT_H
