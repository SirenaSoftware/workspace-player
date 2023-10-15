#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QWidget>
#include <lua.hpp>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>

class CheckBox : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString label READ label WRITE setLabel)
    Q_PROPERTY(bool data READ data WRITE setData)

public:
    explicit CheckBox(QWidget *parent = nullptr);

    void setLabel(QString value);
    QString label();

    void setData(bool value);
    bool data();

    lua_State *L = nullptr;
signals:
    void onclick(bool checked);
    void onpress();
    void onrelease();
    void ontoggle(bool checked);

signals:
private slots:
    void on_click(bool checked);
    void on_press();
    void on_release();
    void on_toggle(bool checked);

private:
    void mousePressEvent(QMouseEvent *event);
    QPushButton*btn;
};

#endif // CHECKBOX_H
