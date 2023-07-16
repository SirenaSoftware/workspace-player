#include "workspace.h"
#include "ui_workspace.h"
#include <QDateTime>


void Workspace::on_hamburguerButton_clicked(bool checked)
{
    if (checked)
    {
        ui->leftBar->show();
        return;
    }

    ui->leftBar->hide();
}


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

    loadCategories("exporters",ui->exportersCategories);

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


void Workspace::_on_clock_update(){
    QDateTime time = QDateTime::currentDateTime();
    QString text = time.toString("hh:mm");

    ui->clock->setText(text);
}


void Workspace::on_saveModifications_clicked()
{
    close();
}

