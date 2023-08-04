#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QStringList>

extern void print(QString message);
extern QStringList processSAMLLine(QString line);

#endif // COMMON_H
