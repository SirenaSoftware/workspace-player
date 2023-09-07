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

    if (onclick.isEmpty()){
        onclick = this->objectName()+":onclick()";
        return;
    }

    if (L) {
        luaL_dostring(L, onclick.toStdString().c_str());
    }
}
