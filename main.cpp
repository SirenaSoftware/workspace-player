#include "workspace.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("Fusion");

    Workspace w;
    w.move(0,0);
    w.resize(800,600);
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.setWindowState(Qt::WindowFullScreen);
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.updateGeometry();
    w.showMaximized();
    return a.exec();
}
