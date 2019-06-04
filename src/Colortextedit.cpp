#include "Colortextedit.h"

colorTextEdit::colorTextEdit(QString _value)
{
    this->setText(_value);
}

void colorTextEdit::keyPressEvent(QKeyEvent *e){
    if ((e->key() == Qt::Key_0 ||
            e->key() == Qt::Key_1 ||
            e->key() == Qt::Key_2 ||
            e->key() == Qt::Key_3 ||
            e->key() == Qt::Key_4 ||
            e->key() == Qt::Key_5 ||
            e->key() == Qt::Key_6 ||
            e->key() == Qt::Key_7 ||
            e->key() == Qt::Key_8 ||
            e->key() == Qt::Key_9) && (this->toPlainText().length() < 3)){
        QTextEdit::keyPressEvent(e);
     }

     if (e->key() == Qt::Key_Backspace ||
            e->key() == Qt::Key_Delete ||
            e->key() == Qt::Key_Left ||
            e->key() == Qt::Key_Right){
        QTextEdit::keyPressEvent(e);
     }

     if (e->key() == Qt::Key_Up){
         int buff = this->toPlainText().toInt() + 1;
        this->setText(QString::number(buff));
     }

     if(e->key() == Qt::Key_Down) {
         int buff = this->toPlainText().toInt() - 1;
         this->setText(QString::number(buff));
     }

     if(this->toPlainText().toInt() > 255){
         this->setText("255");
     }

     if(this->toPlainText().toInt() < 0){
         this->setText("0");
     }
}
