#include "Box.h"

Box::Box(QWidget *parent)
    : QWidget{parent}
{

}

void Box::paintEvent(QPaintEvent *event){
    Q_UNUSED(event)

    QStyleOption option;
    option.initFrom(this);

    QPainter painter(this);

    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}
