#include "workspace.h"
#include "ui_workspace.h"

void Workspace::on_addModuleToWorkspace_clicked(){
    QString path = "";

    QString module_descriptor = "";

    QLayoutItem* control_item;
    while ( ( control_item = ui->moduleVariations->layout()->takeAt( 0 ) ) != nullptr ){
        if (control_item->widget()) {
            if (control_item->widget()->property("checked").toBool()) {
                path = control_item->widget()->property("vpath").toString()+"/";
            }
            delete control_item->widget();
        }
        delete control_item;
    }

    while ( ( control_item = ui->aditionalModuleOptions->layout()->takeAt( 0 ) ) != nullptr ){
        if (control_item->widget()) {
            QString property = control_item->widget()->property("property").toString();
            QString widget = control_item->widget()->property("component").toString();
            QString data = control_item->widget()->property("data").toString();

            module_descriptor += widget+"@"+property+": "+data+"\n";

            delete control_item->widget();
        }
        delete control_item;
    }

    while (path.contains("//")) path.replace("//","/");

    QStringList path_slices = path.split("/");

    QString variation = path_slices[path_slices.count()-2];
    QString name = path_slices[path_slices.count()-4];
    QString class_name = path_slices[path_slices.count()-6];
    class_name = class_name == "_common"?"_common":WORKSPACE_ID;

    QString common_id = class_name+"_"+name+"_"+variation;
    const QString module_id = common_id+"_"+QString::number(QDateTime::currentMSecsSinceEpoch()-1649289600000);

    module_descriptor += "layout: "+common_id;

    // Let's copy the module


    if (!QFile(ROOT+"/workspaces/"+WORKSPACE_PATH+"/modules/"+module_id+".yml").exists()) {
        QDir().mkdir(ROOT+"/workspaces/"+WORKSPACE_PATH+"/modules/");

        QFile file(ROOT+"/workspaces/"+WORKSPACE_PATH+"/modules/"+module_id+".yml");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.resize(0);
        file.write(module_descriptor.toLocal8Bit());
        file.close();

        remove_on_discard.append(ROOT+"/workspaces/"+WORKSPACE_PATH+"/modules/"+module_id+".yml");
    }

    if (!QFile(ROOT+"/workspaces/"+WORKSPACE_PATH+"/scripts/"+common_id+".lua").exists()) {
        QDir().mkdir(ROOT+"/workspaces/"+WORKSPACE_PATH+"/scripts/");
        QFile::copy(path+"/script.lua",ROOT+"/workspaces/"+WORKSPACE_PATH+"/scripts/"+common_id+".lua");
        remove_on_discard.append(ROOT+"/workspaces/"+WORKSPACE_PATH+"/scripts/"+common_id+".lua");
    }

    if (!QFile(ROOT+"/workspaces/"+WORKSPACE_PATH+"/layouts/"+common_id+".yml").exists()) {
        QDir().mkdir(ROOT+"/workspaces/"+WORKSPACE_PATH+"/scripts/");
        QFile::copy(path+"/layout.yml",ROOT+"/workspaces/"+WORKSPACE_PATH+"/layouts/"+common_id+".yml");

        remove_on_discard.append(ROOT+"/workspaces/"+WORKSPACE_PATH+"/layouts/"+common_id+".yml");
    }

    if (!QFile(ROOT+"/workspaces/"+WORKSPACE_PATH+"/assets/icons/"+common_id+".svg").exists()) {
        QDir().mkdir(ROOT+"/workspaces/"+WORKSPACE_PATH+"/assets/");
        QDir().mkdir(ROOT+"/workspaces/"+WORKSPACE_PATH+"/assets/icons/");

        QFile::copy(path+"/icon.svg",ROOT+"/workspaces/"+WORKSPACE_PATH+"/assets/icons/"+common_id+".svg");

        remove_on_discard.append(ROOT+"/workspaces/"+WORKSPACE_PATH+"/assets/icons/"+common_id+".svg");
    }

    QString module_name = ui->moduleName->text().simplified();

    QListWidgetItem*item = new QListWidgetItem;
    item->setText(module_name.isEmpty()?"No title":module_name);
    item->setIcon(QIcon(ROOT+"/workspaces/"+WORKSPACE_PATH+"/assets/icons/"+common_id+".svg"));
    item->setData(40,module_id);
    item->setData(41,"/assets/icons/"+common_id+".svg");
    item->setSizeHint(QSize(40,40));

    ui->moduleList->addItem(item);
    ui->moduleList->setProperty("modified",true);

    ui->contentPager->setCurrentWidget(ui->modulesPage);
    showChrome();
}
