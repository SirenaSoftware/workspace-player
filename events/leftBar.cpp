#include "workspace.h"
#include "ui_workspace.h"


void Workspace::on_addModule_clicked()
{
    hideChrome();
    ui->contentPager->setCurrentWidget(ui->addModulePage);
}


void Workspace::on_moduleOptions_clicked()
{

}


void Workspace::on_moduleList_itemActivated(QListWidgetItem *item)
{
    Q_UNUSED(item);
}

