#include "Button.h"
#include <QVariant>

Button::Button(QWidget *parent)
    : QPushButton{parent}
{
    setSizePolicy(sizePolicy().horizontalPolicy(),sizePolicy().horizontalPolicy());

    connect(this,SIGNAL(clicked(bool)),this,SLOT(onclick(bool)));
    connect(this,SIGNAL(pressed()),this,SLOT(onpress()));
    connect(this,SIGNAL(released()),this,SLOT(onrelease()));
    connect(this,SIGNAL(toggled(bool)),this,SLOT(ontoggle(bool)));
}

void Button::onclick(bool checked){
    QString onclick = property("onclick").toString();

    onclick = onclick.isEmpty()? this->objectName()+":onclick" : onclick;

    if (L) {
        luaL_dostring(L, (onclick+"("+(checked?"true":"false")+")").toStdString().c_str());
    }
}

void Button::onpress(){
    QString onpress = property("onpress").toString();

    onpress = onpress.isEmpty()? this->objectName()+":onpress" : onpress;

    if (L) {
        luaL_dostring(L, (onpress+"()").toStdString().c_str());
    }
}

void Button::onrelease(){
    QString onrelease = property("onrelease").toString();

    onrelease = onrelease.isEmpty()? this->objectName()+":onrelease" : onrelease;

    if (L) {
        luaL_dostring(L, (onrelease+"()").toStdString().c_str());
    }
}

void Button::ontoggle(bool checked){
    QString onclick = property("ontoggle").toString();

    onclick = onclick.isEmpty()? this->objectName()+":ontoggle" : onclick;

    if (L) {
        luaL_dostring(L, (onclick+"("+(checked?"true":"false")+")").toStdString().c_str());
    }
}
