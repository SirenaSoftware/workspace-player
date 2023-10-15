#include "workspace.h"
#include "ui_workspace.h"


void Workspace::on_addModule_clicked()
{
    loadCategories("modules",ui->externalModulesCategories);

    ui->contentPager->setCurrentWidget(ui->addModulePage);
    hideChrome();
}


void Workspace::on_moduleOptions_clicked()
{

}


void Workspace::on_moduleList_itemClicked(QListWidgetItem *item)
{
    loadModule(item->data(40).toString());
}

