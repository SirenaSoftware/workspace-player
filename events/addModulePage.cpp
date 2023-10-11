#include "workspace.h"
#include "ui_workspace.h"


void Workspace::on_externalModulesCategories_itemActivated(QListWidgetItem *item)
{
    ui->externalModulesList->clear();

    for (const QString &source : QList<QString> { "_common", WORKSPACE_CLASS, WORKSPACE_PATH} ) {
        QString dpath = ROOT+"/modules/"+source+"/"+item->data(42).toString()+"/";

        for (const QString &module : QDir(dpath).entryList(QDir::Dirs|QDir::NoDotAndDotDot)) {
            dpath = dpath+module+"/";

            QFile label(dpath+"/label."+LANG);

            if (!label.exists()){
                label.setFileName(dpath+"/label");
                if (!label.exists()) continue;
            }

            label.open(QFile::ReadOnly);

            QListWidgetItem*item = new QListWidgetItem;
            item->setText(QString(label.readAll()).remove("\n").remove("\r"));
            item->setIcon(QIcon(dpath+"/icon.svg"));
            item->setData(42,dpath);
            item->setSizeHint(QSize(48,60));

            ui->externalModulesList->addItem(item);

            label.close();
        }
    }
}


void Workspace::on_externalModulesList_itemActivated(QListWidgetItem *item)
{

}
