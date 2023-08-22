#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QStringList>
#include <QWidget>
#include <QVariant>

extern void print(QString message);
extern QStringList processSAMLLine(QString line);

extern QWidget*string2widget(QString id,QString type);
extern void loadLayout(QString layout_file,QWidget*page);
extern void assingProperty(QWidget*widget,QString property, QString value);
extern void buildStyleSheet(QWidget*widget);

#endif // COMMON_H
