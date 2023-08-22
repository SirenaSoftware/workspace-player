#include "common.h"
#include <QDebug>
#include <QFile>

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

#include <QVBoxLayout>
#include <QHBoxLayout>

QWidget*string2widget(QString id,QString type){
    QWidget*wdg = nullptr;

    if (type == "HBox") {
        wdg = new QWidget;
        wdg->setLayout(new QHBoxLayout);
        wdg->layout()->setContentsMargins(0,0,0,0);
        goto finalize;
    }

    if (type == "VBox") {
        wdg = new QWidget;
        wdg->setLayout(new QVBoxLayout);
        wdg->layout()->setContentsMargins(0,0,0,0);
        goto finalize;
    }

    wdg = new QWidget;

finalize:
    wdg->setObjectName(id);
    return wdg;
}

void assingProperty(QWidget*widget,QString property, QString value) {
    widget->setProperty(property.toLocal8Bit(),value);
}

void buildStyleSheet(QWidget*widget){

}

void loadLayout(QString layout_file,QWidget*page){
    QFile file(layout_file);

    if (file.open(QFile::ReadOnly)){
        QTextStream file_data(&file);

        QMap<int,QWidget*>list;
        list[0] = page;

        QWidget*current_widget = nullptr;
        QWidget*parent_widget = page;

        QString id = "";

        while (!file_data.atEnd()) {
            QStringList line = processSAMLLine(file_data.readLine());

            QString property = line[0];
            QString value = line[1];
            int indent = line[2].toInt();

            parent_widget = list[indent];
            if (!parent_widget) continue;

            if (property == "id") {
                id = value;
                continue;
            }

            if (property == "type") {
                if (current_widget) {
                    buildStyleSheet(current_widget);
                }

                current_widget = string2widget(id,value);
                list[indent+1] = current_widget;

                if (parent_widget->layout()) {
                    parent_widget->layout()->addWidget(current_widget);
                    continue;
                }

                current_widget->setParent(parent_widget);
                continue;
            }

            if (property.startsWith("@")){
                assingProperty(page,property.mid(1),value);
                continue;
            }

            if (current_widget) {
                assingProperty(current_widget,property,value);
            }
        }

        if (current_widget) {
            buildStyleSheet(current_widget);
        }

        buildStyleSheet(page);

        file.close();
        return;
    }

    print("File '"+layout_file+"' not found");
}
