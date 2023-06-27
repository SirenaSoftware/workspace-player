#include "workspace.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("Fusion");

    Workspace w;
    /*w.setWindowFlags(Qt::FramelessWindowHint);
    w.setWindowState(Qt::WindowFullScreen);*/
    w.setMaximumSize(800,600);
    w.show();
    return a.exec();
}
