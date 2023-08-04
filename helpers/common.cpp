#include "common.h"
#include <QDebug>

void print(QString message){
    qDebug() << message;
}

QStringList processSAMLLine(QString line){
    QStringList list;

    QString property = line.left(line.indexOf(":")).trimmed();
    QString value = line.mid(line.indexOf(":")+1).trimmed();

    if (value.left(1) == "\"" && value.right(1) == "\"") {
        value = value.mid(1,value.length()-2).toLocal8Bit();
    }

    list << property.remove(" ") << value;

    return list;
}
