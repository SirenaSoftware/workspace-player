#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <QProgressBar>
#include <lua.hpp>

class ProgressBar : public QProgressBar
{
    Q_OBJECT
    Q_PROPERTY(int data READ data WRITE setData)

public:
    explicit ProgressBar(QWidget *parent = nullptr);

    void setData(int value);
    int data();

    lua_State *L = nullptr;
signals:

private slots:
    void onchange(int value);
};

#endif // PROGRESS_BAR_H
