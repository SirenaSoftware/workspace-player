#include "Input.h"

Input::Input(QWidget *parent)
    : QLineEdit{parent}
{
    setProperty("widget_","border: 0; padding: 12;");

    connect(this,SIGNAL(editingFinished()),this,SLOT(onedited()));
    connect(this,SIGNAL(returnPressed()),this,SLOT(onpressreturn()));
    connect(this,SIGNAL(textChanged(QString)),this,SLOT(onchange(QString)));
}

void Input::setData(QString value){
    setText(value);
}

QString Input::data(){
    return text();
}

void Input::onedited(){
    QString event = property("onedited").toString();

    event = event.isEmpty()? this->objectName()+".onedited" : event;

    if (L) {
        luaL_dostring(L, (event+"("+this->objectName()+")").toStdString().c_str());
    }
}

void Input::onchange(const QString &text){
    Q_UNUSED(text);

    QString event = property("onchange").toString();

    event = event.isEmpty()? this->objectName()+".onchange" : event;

    if (L) {
        luaL_dostring(L, (event+"("+this->objectName()+")").toStdString().c_str());
    }
}

void Input::onpressreturn(){
    QString event = property("onpressreturn").toString();

    event = event.isEmpty()? this->objectName()+".onpressreturn" : event;

    if (L) {
        luaL_dostring(L, (event+"("+this->objectName()+")").toStdString().c_str());
    }
}

void Input::onreject(){
    QString event = property("onreject").toString();

    event = event.isEmpty()? this->objectName()+".onreject" : event;

    if (L) {
        luaL_dostring(L, (event+"("+this->objectName()+")").toStdString().c_str());
    }
}
