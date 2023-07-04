#include "workspace.h"
#include "ui_workspace.h"


void Workspace::on_addModule_clicked()
{
    ui->contentPager->setCurrentWidget(ui->addModulePage);
    hideChrome();
}


void Workspace::on_moduleOptions_clicked()
{

}


void Workspace::on_moduleList_itemActivated(QListWidgetItem *item)
{
    Q_UNUSED(item);
}

