#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include <lua.hpp>

class Label : public QLabel
{
    Q_OBJECT
public:
    explicit Label(QWidget *parent = nullptr);
    lua_State *L = nullptr;
signals:
private slots:
    void onopenlink(const QString link);
};

#endif // LABEL_H
