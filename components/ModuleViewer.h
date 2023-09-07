#ifndef MODULEVIEWER_H
#define MODULEVIEWER_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <lua.hpp>


class ModuleViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ModuleViewer(QWidget *parent = nullptr);
    void loadScript(QString fname);
    lua_State *L = nullptr;
signals:

private:
    void paintEvent(QPaintEvent *event);
};

#endif // MODULEVIEWER_H
