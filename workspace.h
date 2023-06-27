#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Workspace; }
QT_END_NAMESPACE

class Workspace : public QMainWindow
{
    Q_OBJECT

public:
    Workspace(QWidget *parent = nullptr);
    ~Workspace();

private slots:
    void on_actionF1_triggered();

    void on_actionF2_triggered();

    void on_actionF3_triggered();

    void on_actionF4_triggered();

    void on_actionF5_triggered();

    void on_actionF6_triggered();

    void on_actionF7_triggered();

    void on_actionF8_triggered();

    void on_actionF9_triggered();

    void on_actionF10_triggered();

    void on_actionF11_triggered();

    void on_actionF12_triggered();

    void on_actionEsc_triggered();

    void on_actionHome_triggered();

    void on_actionPageUp_triggered();

    void on_actionPageDown_triggered();

    void on_actionEnd_triggered();

    void on_actionMenu_triggered();

    void on_actionPrint_triggered();

private:
    Ui::Workspace *ui;
};
#endif // WORKSPACE_H
