#include "workspace.h"
#include "ui_workspace.h"


void Workspace::on_callWorkspaceViewer_clicked()
{

}


void Workspace::on_callExportOrPrint_clicked()
{
    if (ui->workspaceHeader->height()==0){
        ui->contentPager->setCurrentWidget(ui->modulesPage);
        showChrome();
        return;
    }

    ui->contentPager->setCurrentWidget(ui->printPage);
    hideChrome();
}


void Workspace::on_discardModifications_clicked()
{
    close();
}


void Workspace::on_clock_clicked()
{

}


void Workspace::on_saveModifications_clicked()
{
    close();
}

