#include "Label.h"

Label::Label(QWidget *parent)
    : QLabel{parent}
{
    connect(this,SIGNAL(textChanged(QString)),this,SLOT(onchange(QString)));
}

void Label::onopenlink(const QString text){
    Q_UNUSED(text);

    QString event = property("onchange").toString();

    event = event.isEmpty()? this->objectName()+".onchange" : event;

    if (L) {
        luaL_dostring(L, (event+"("+this->objectName()+",\""+
                          QString(text).replace("\\","\\\\").replace("\"\"","\\\"")+"\")").toStdString().c_str());
    }
}
