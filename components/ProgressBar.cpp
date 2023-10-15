#include "ProgressBar.h"
#include <QVariant>

ProgressBar::ProgressBar(QWidget *parent)
    : QProgressBar{parent}
{
    setProperty("widget_","border: 0;");

    connect(this,SIGNAL(clicked(bool)),this,SLOT(onchange(int)));
}

void ProgressBar::onchange(int value){
    QString onclick = property("onchange").toString();

    onclick = onclick.isEmpty()? this->objectName()+".onchange" : onclick;

    if (L) {
        luaL_dostring(L, (onclick+"("+this->objectName()+","+QString::number(value)+")").toStdString().c_str());
    }
}

void ProgressBar::setData(int value){
    setValue(value);
}

int ProgressBar::data(){
    return value();
}
