#include "workspace.h"
#include "ui_workspace.h"
#include "components/CheckBox.h"
#include "components/Label.h"

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
        btn->setProperty("vpath",vpath+"/"+x+"/");
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

    QStringList colors;
    colors << "#55efc4" << "#81ecec" << "#00d2d3" << "#74b9ff" << "#54a0ff"
           << "#a29bfe" << "#dfe6e9" << "#c8d6e5" << "#ffeaa7" << "#feca57"
           << "#fab1a0" << "#ff7675" << "#fd79a8" << "#ff9ff3";

    if (file.open(QFile::ReadOnly)){
        QTextStream file_data(&file);
        while (!file_data.atEnd()) {
            QStringList line = processSAMLLine(file_data.readLine());

            QString property = line[0];
            QString value = line[1];

            if (property.startsWith("--")) {
                property = "type";
                value = "Label";
            }

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
                    continue;
                }

                if (value == "Label") {
                    control = new Label;
                    control->setProperty("text"," ");
                    continue;
                }

                if (value == "ColorBox") {
                    control = new QWidget;
                    control->setMaximumHeight(48);
                    control->setMinimumHeight(48);
                    control->setProperty("boxColorBox",true);
                    control->setLayout(new QHBoxLayout);
                    control->layout()->setContentsMargins(0,0,0,0);
                    control->layout()->setAlignment(Qt::AlignLeft);

                    for (QString color : colors) {
                        QPushButton *btn = new QPushButton;
                        btn->setCheckable(true);
                        btn->setAutoExclusive(true);
                        btn->setStyleSheet("QPushButton {"
                                           "   border-radius:12;"
                                           "   border: 1px solid rgba(0,0,0,128);"
                                           "   margin: 4;"
                                           "   background-color: "+color+";"
                                           "}"
                                           "QPushButton:hover {"
                                           "   border-radius:14;"
                                           "   border: 1px solid rgba(0,0,0,128);"
                                           "   margin: 2;"
                                           "}"
                                           "QPushButton:checked {"
                                           "   border-radius:16;"
                                           "   border: 1px solid #000000;"
                                           "   margin: 0;"
                                           "}");
                        btn->setMinimumSize(32,32);
                        btn->setProperty("data",color);
                        btn->setMaximumSize(32,32);
                        control->layout()->addWidget(btn);
                    }

                    control->layout()->itemAt(0)->widget()->setProperty("checked",true);

                    continue;
                }
            }

            if (control&&property == "label") {
                control->setProperty("label",value);
                continue;
            }

            if (control&&property == "text") {
                control->setProperty("text",value);
                continue;
            }

            if (control&&property == "default") {
                if (control->property("boxColorBox").toBool()){
                    control->layout()->itemAt(0)->widget()->setProperty("checked",false);
                    if (control->layout()->itemAt(value.toInt()-1))
                      control->layout()->itemAt(value.toInt()-1)->widget()->setProperty("checked",true);
                    continue;
                }
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

            ui->moduleName->setFocus();
            return;
        }
    }

    print("File '"+item->data(42).toString()+"/configuration.yml"+"' not found");
    ui->moduleName->setFocus();
}
