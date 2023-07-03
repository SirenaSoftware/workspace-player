#include "workspace.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("Fusion");

    Workspace w;
    /*w.setWindowFlags(Qt::FramelessWindowHint);
    w.setWindowState(Qt::WindowFullScreen);*/
    //w.setWindowFlags(Qt::FramelessWindowHint);
    w.resize(800,600);
    w.move(0,0);
    w.show();
    return a.exec();
}
