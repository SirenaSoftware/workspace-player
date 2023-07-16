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

    ui->exportersCategories->clear();

    for (const QString &source : QList<QString> { "_common", WORKSPACE_PATH} ) {
        for (const QString &category : QDir(ROOT+"exporters/"+source).entryList(QDir::Dirs)) {
            if (category=="."||category=="..") continue;

            if (source!="_common"&&QFile(ROOT+"exporters/_common/"+category+"/label").exists()) {
                continue;
            }

            QFile label(ROOT+"exporters/"+source+"/"+category+"/label."+LANG);

            if (!label.exists()){
                label.setFileName(ROOT+"exporters/"+source+"/"+category+"/label");
                if (!label.exists()) continue;
            }

            label.open(QFile::ReadOnly);

            QListWidgetItem*item = new QListWidgetItem;
            item->setText(QString(label.readAll()).remove("\n").remove("\r"));
            item->setIcon(QIcon(ROOT+"exporters/"+source+"/"+category+"/icon.svg"));
            item->setData(42,category);

            ui->exportersCategories->addItem(item);

            label.close();
        }
    }

    ui->exportersCategories->sortItems();

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

