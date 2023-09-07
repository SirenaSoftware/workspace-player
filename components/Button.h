#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <lua.hpp>

class Button : public QPushButton
{
    Q_OBJECT
public:
    explicit Button(QWidget *parent = nullptr);
    lua_State *L = nullptr;
signals:

private slots:
    void onclick(bool checked);

};

#endif // BUTTON_H
