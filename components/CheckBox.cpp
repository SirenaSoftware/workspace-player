#include "CheckBox.h"

CheckBox::CheckBox(QWidget *parent)
    : QWidget{parent}
{
    btn = new QPushButton;
    QFont btn_fnt = QFont(btn->font());
    btn_fnt.setPointSize(14);
    btn_fnt.setBold(true);

    btn->setMaximumSize(32,32);
    btn->setMaximumSize(32,32);
    btn->setText("");
    btn->setFont(btn_fnt);
    btn->setCheckable(true);

    QLabel*lbl = new QLabel;
    lbl->setText("");

    setLayout(new QHBoxLayout);
    layout()->setContentsMargins(0,0,0,0);
    layout()->addWidget(btn);
    layout()->addWidget(lbl);

    connect(btn,SIGNAL(clicked(bool)),this,SLOT(on_click(bool)));
    connect(btn,SIGNAL(toggled(bool)),this,SLOT(on_toggle(bool)));
}

void CheckBox::setLabel(QString value){
    layout()->itemAt(1)->widget()->setProperty("text",value);
}

QString CheckBox::label(){
    return layout()->itemAt(1)->widget()->property("text").toString();
}

void CheckBox::on_click(bool checked){
    emit onclick(checked);
}

void CheckBox::on_press(){
    emit onpress();
}

void CheckBox::on_release(){
    emit onrelease();
}

void CheckBox::on_toggle(bool checked){
    layout()->itemAt(0)->widget()->setProperty("checked",checked);
    layout()->itemAt(0)->widget()->setProperty("text",checked?"✓":"");

    emit ontoggle(checked);
}

void CheckBox::setData(bool value){
    layout()->itemAt(0)->widget()->setProperty("checked",value);
}

bool CheckBox::data(){
    return layout()->itemAt(0)->widget()->property("checked").toBool();
}

void CheckBox::mousePressEvent(QMouseEvent *event){
    QWidget::mousePressEvent(event);
    btn->click();
}
