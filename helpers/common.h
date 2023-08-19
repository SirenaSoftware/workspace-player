#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QStringList>
#include <QWidget>

extern void print(QString message);
extern QStringList processSAMLLine(QString line);

extern QWidget*string2widget(QString id,QString type);

#endif // COMMON_H
