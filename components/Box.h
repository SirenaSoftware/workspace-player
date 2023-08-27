#ifndef BOX_H
#define BOX_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>

class Box : public QWidget
{
    Q_OBJECT
public:
    explicit Box(QWidget *parent = nullptr);

signals:

private:
    void paintEvent(QPaintEvent *event);
};

#endif // BOX_H
