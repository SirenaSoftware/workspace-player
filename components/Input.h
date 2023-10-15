#ifndef INPUT_H
#define INPUT_H

#include <QLineEdit>
#include <lua.hpp>

class Input : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(QString data READ data WRITE setData)

public:
    explicit Input(QWidget *parent = nullptr);

    void setData(QString value);
    QString data();

    lua_State *L = nullptr;
signals:
private slots:
    void onedited();
    void onchange(const QString &text);
    void onpressreturn();
    void onreject();
};

#endif // INPUT_H
