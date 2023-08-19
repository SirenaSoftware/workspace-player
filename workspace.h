#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QResizeEvent>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include "helpers/common.h"

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
    // Function keys
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

    // Special keys
    void on_actionEsc_triggered();
    void on_actionHome_triggered();
    void on_actionPageUp_triggered();
    void on_actionPageDown_triggered();
    void on_actionEnd_triggered();
    void on_actionMenu_triggered();
    void on_actionPrint_triggered();

    // Top bar widgets
    void on_hamburguerButton_clicked(bool checked);
    void on_callWorkspaceViewer_clicked();
    void on_callExportOrPrint_clicked();
    void on_discardModifications_clicked();
    void on_clock_clicked();
    void _on_clock_update();
    void on_saveModifications_clicked();

    // Left bar widget
    void on_addModule_clicked();
    void on_moduleOptions_clicked();
    void on_moduleList_itemActivated(QListWidgetItem *item);

    // Edit bar buttons
    void on_gotoSecondBar_clicked();
    void on_undo_clicked();
    void on_redo_clicked();
    void on_cut_clicked();
    void on_copy_clicked();
    void on_paste_clicked();
    void on_delete__clicked();
    void on_find_clicked();
    void on_replace_clicked();
    void on_gotoLine_clicked();

    // Add module page
    void on_externalModulesCategories_itemActivated(QListWidgetItem *item);
    void on_externalModulesList_itemActivated(QListWidgetItem *item);

    // Export or print page
    void on_exportersCategories_itemActivated(QListWidgetItem *item);
    void on_exportersList_itemActivated(QListWidgetItem *item);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::Workspace *ui;

    void hideChrome();
    void showChrome();

    void loadCategories(QString type,QListWidget*list);

    void loadConfig();

    const QString LANG = QString(qgetenv("LANG")).remove(".UTF-8");
    const QString ROOT = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/.sirena/";
    QString WORKSPACE_ID = "sirena.demonstration";
    QString WORKSPACE_PATH = "sirena/demonstration";
    QString WORKSPACE_CLASS = "empty";

};
#endif // WORKSPACE_H
