#ifndef MODULEVIEWER_H
#define MODULEVIEWER_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <lua.hpp>
#include <QFile>

class ModuleViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ModuleViewer(QWidget *parent = nullptr);
    void loadScript(QString fname);
    void writeData(QString fname);
    void loadData(QString fname);

    lua_State *L = nullptr;
signals:

private:
    void paintEvent(QPaintEvent *event);
    void dumpComponentData(QWidget * parent, QFile *file);
    void loadComponentData(QWidget * parent, QMap<QString,QString>*data);

    QString PATH = "";
};

#endif // MODULEVIEWER_H
