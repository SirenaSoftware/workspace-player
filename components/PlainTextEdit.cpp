#include "PlainTextEdit.h"

PlainTextEdit::PlainTextEdit(QWidget *parent)
    : QPlainTextEdit{parent}
{
    setProperty("separated",true);
    connect(this,SIGNAL(textChanged()),this,SLOT(onchange()));
}

void PlainTextEdit::setData(QString value){
    setPlainText(value);
}

QString PlainTextEdit::data(){
    return toPlainText();
}


void PlainTextEdit::onchange(){
    setProperty("edited",true);

    QString event = property("onchange").toString();
    event = event.isEmpty()? this->objectName()+".onchange" : event;

    if (L) {
        luaL_dostring(L, (event+"("+this->objectName()+")").toStdString().c_str());
    }
}
