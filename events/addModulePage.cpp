#include "workspace.h"
#include "ui_workspace.h"


void Workspace::on_externalModulesCategories_itemActivated(QListWidgetItem *item)
{  
    loadItems(item->data(42).toString(),ui->externalModulesList);
}


void Workspace::on_externalModulesList_itemActivated(QListWidgetItem *item)
{

}
