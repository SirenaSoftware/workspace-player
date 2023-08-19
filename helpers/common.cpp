#include "common.h"
#include <QDebug>

void print(QString message){
    qDebug() << message;
}

QStringList processSAMLLine(QString line){
    QString property = line.left(line.indexOf(":"));
    QString value = line.mid(line.indexOf(":")+1).trimmed();

    int i = 0;
    for(i = 0; i < property.size() && property[i] == ' '; ++i);

    if (value.left(1) == "\"" && value.right(1) == "\"") {
        value = value.mid(1,value.length()-2).toLocal8Bit();
    }

    return QStringList() << property.trimmed().remove(" ") << value << QString::number(i/2);
}

#include <QLabel>

QWidget*string2widget(QString id,QString type){
    QWidget*wdg = nullptr;

    if (type == "Label") {
        wdg = new QLabel;
        goto finalize;
    }

    wdg = new QWidget;

finalize:
    wdg->setObjectName(id);
    return wdg;
}
