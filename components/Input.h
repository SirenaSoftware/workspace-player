#ifndef INPUT_H
#define INPUT_H

#include <QLineEdit>
#include <lua.hpp>

class Input : public QLineEdit
{
    Q_OBJECT
public:
    explicit Input(QWidget *parent = nullptr);
    lua_State *L = nullptr;
signals:
private slots:
    void onedited();
    void onchange(const QString &text);
    void onpressreturn();
    void onreject();
};

#endif // INPUT_H
