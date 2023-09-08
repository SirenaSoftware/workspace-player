#include "Button.h"
#include <QVariant>

Button::Button(QWidget *parent)
    : QPushButton{parent}
{
    setSizePolicy(sizePolicy().horizontalPolicy(),sizePolicy().horizontalPolicy());

    connect(this,SIGNAL(clicked(bool)),this,SLOT(onclick(bool)));
}

void Button::onclick(bool checked){
    QString onclick = property("onclick").toString();

    onclick = onclick.isEmpty()? this->objectName()+":onclick" : onclick;

    if (L) {
        luaL_dostring(L, (onclick+"("+(checked?"true":"false")+")").toStdString().c_str());
    }
}
