#include "workspace.h"
#include "ui_workspace.h"


void Workspace::on_exportersCategories_itemActivated(QListWidgetItem *item)
{
    loadItems(item->data(42).toString(),ui->exportersList);
}


void Workspace::on_exportersList_itemActivated(QListWidgetItem *item)
{

}
