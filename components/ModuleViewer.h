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

    lua_State *L = nullptr;
signals:

private:
    void paintEvent(QPaintEvent *event);
    void dumpComponents(QWidget * parent, QFile *file);
};

#endif // MODULEVIEWER_H
