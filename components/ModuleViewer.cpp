#include "ModuleViewer.h"
#include <QVBoxLayout>

ModuleViewer::ModuleViewer(QWidget *parent)
    : QWidget{parent}
{
    setLayout(new QVBoxLayout);
    layout()->setContentsMargins(0,0,0,0);
    layout()->setSpacing(0);

    L = luaL_newstate();
    luaL_openlibs(L);
}

void ModuleViewer::loadScript(QString fname){
    luaL_dofile(L,fname.toStdString().c_str());
}

void ModuleViewer::paintEvent(QPaintEvent *event){
    Q_UNUSED(event)

    QStyleOption option;
    option.initFrom(this);

    QPainter painter(this);

    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}
