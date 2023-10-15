#ifndef PLAINTEXTEDIT_H
#define PLAINTEXTEDIT_H

#include <QPlainTextEdit>
#include <lua.hpp>

class PlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT
    Q_PROPERTY(QString data READ data WRITE setData)

public:
    explicit PlainTextEdit(QWidget *parent = nullptr);
    lua_State *L = nullptr;

    void setData(QString value);
    QString data();

private slots:
    void onchange();
};

#endif // PLAINTEXTEDIT_H
