#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <lua.hpp>

class Button : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QString label READ label WRITE setLabel)

public:
    explicit Button(QWidget *parent = nullptr);

    void setLabel(QString value);
    QString label();

    lua_State *L = nullptr;
signals:

private slots:
    void onclick(bool checked);
    void onpress();
    void onrelease();
    void ontoggle(bool checked);
};

#endif // BUTTON_H
