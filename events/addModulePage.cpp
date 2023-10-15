#include "workspace.h"
#include "ui_workspace.h"
#include "components/CheckBox.h"

void Workspace::on_externalModulesCategories_itemClicked(QListWidgetItem *item)
{
    loadItems(item->data(42).toString(),ui->externalModulesList);
}


void Workspace::on_externalModulesList_itemClicked(QListWidgetItem *item)
{
    ui->contentPager->setCurrentWidget(ui->configureModule);
    ui->moduleName->setText("");
    ui->moduleVariationsLabel->hide();
    ui->moduleVariations->hide();
    ui->aditionalModuleOptionsLabel->hide();

    ui->configureModule->setProperty("module_path",item->data(42).toString());

    QLayoutItem* variation;
    while ( ( variation = ui->moduleVariations->layout()->takeAt( 0 ) ) != nullptr ){
        delete variation->widget();
        delete variation;
    }

    QString vpath = item->data(42).toString()+"/variations/";

    QPushButton*first = nullptr;

    for (QString x : QDir(vpath).entryList(QDir::Dirs|QDir::NoDotAndDotDot)) {
        QPushButton*btn = new QPushButton;
        btn->setIcon(QIcon(vpath+"/"+x+"/icon.svg"));
        btn->setIconSize(QSize(32,32));
        btn->setMinimumSize(QSize(48,48));
        btn->setMaximumSize(QSize(48,48));
        btn->setAutoExclusive(true);
        btn->setCheckable(true);
        btn->setProperty("vpath",vpath);
        btn->setProperty("boxButton",true);

        ui->moduleVariations->layout()->addWidget(btn);

        if (first) continue;

        btn->setChecked(true);
        first = btn;
    }

    if (first) {
        ui->moduleVariationsLabel->show();
        ui->moduleVariations->show();
    }

    QFile file(item->data(42).toString()+"/configuration.yml");

    QWidget*control = nullptr;

    QLayoutItem* control_item;
    while ( ( control_item = ui->aditionalModuleOptions->layout()->takeAt( 0 ) ) != nullptr ){
        if (control_item->widget()) delete control_item->widget();
        delete control_item;
    }

    if (file.open(QFile::ReadOnly)){
        QTextStream file_data(&file);
        while (!file_data.atEnd()) {
            QStringList line = processSAMLLine(file_data.readLine());

            QString property = line[0];
            QString value = line[1];

            if (property == "type") {
                if (control) {
                    ui->aditionalModuleOptions->layout()->addWidget(control);
                    control = nullptr;
                }
                if (value == "CheckBox") {
                    control = new CheckBox;
                    control->setMaximumHeight(48);
                    control->setMinimumHeight(48);
                    control->setProperty("boxCheckBox",true);
                }
                continue;
            }

            if (control&&property == "label") {
                control->setProperty("label",value);
                continue;
            }

            if (control&&property == "default") {
                control->setProperty("data",value);
                continue;
            }

            if (control&&property == "property") {
                control->setProperty("property",value);
                continue;
            }

            if (control&&property == "component") {
                control->setProperty("component",value);
                continue;
            }
        }
        file.close();

        if (control) {
            ui->aditionalModuleOptions->layout()->setAlignment(Qt::AlignTop);
            ui->aditionalModuleOptions->layout()->addWidget(control);
            ui->aditionalModuleOptionsLabel->show();

            ui->moduleName->setFocus();
            return;
        }
    }

    print("File '"+item->data(42).toString()+"/configuration.yml"+"' not found");
    ui->moduleName->setFocus();
}
