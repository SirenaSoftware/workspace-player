#include "workspace.h"
#include "ui_workspace.h"
#include "components/ModuleViewer.h"
#include <QTimer>
#include <QFile>

Workspace::Workspace(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Workspace)
{
    ui->setupUi(this);
    ui->contentPager->setCurrentWidget(ui->modulesPage);

    ui->contentArea->removeWidget(ui->leftBar);
    ui->leftBar->setParent(this);
    ui->leftBar->move(0,ui->topBar->height());
    ui->leftBar->resize(ui->leftBar->width(),height()-ui->leftBar->y());
    ui->leftBar->hide();

    loadConfig();
    loadModule("welcome");

    if (QFile(ROOT+"/workspaces/"+WORKSPACE_PATH+"/icon.svg").exists()) {
        ui->callWorkspaceViewer->setIcon(QIcon(ROOT+"/workspaces/"+WORKSPACE_PATH+"/icon.svg"));
    }

    _on_clock_update();
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Workspace::_on_clock_update);
    timer->start(1000);
}


Workspace::~Workspace()
{
    delete ui;
}


void Workspace::resizeEvent(QResizeEvent *event)
{
    if (event->size().width()<1024)
    {
        ui->contentArea->removeWidget(ui->leftBar);
        ui->leftBar->setParent(this);
        ui->leftBar->move(0,ui->topBar->height());
        ui->leftBar->resize(ui->leftBar->width(),event->size().height()-ui->leftBar->y());
        ui->hamburguerButton->show();

        if (ui->hamburguerButton->isChecked()&&ui->contentPager->currentWidget() == ui->modulesPage) {
            ui->leftBar->show();
        }

        return;
    }

    if (ui->contentPager->currentWidget() == ui->modulesPage) {
        ui->leftBar->show();
    }

    ui->contentArea->insertWidget(0,ui->leftBar);
    ui->hamburguerButton->hide();
}


void Workspace::showChrome()
{
    int topBarButtonHeight = ui->callExportOrPrint->height();

    ui->workspaceHeader->setMaximumHeight(topBarButtonHeight);
    ui->discardModifications->setMaximumHeight(topBarButtonHeight);
    ui->saveModifications->setMaximumHeight(topBarButtonHeight);
    ui->callExportOrPrint->setText("Export or Print");

    if (width()>=1024||ui->hamburguerButton->isChecked()) {
        ui->leftBar->show();
    }

    ui->rightBar->show();

    if (ui->contentPager->currentWidget() == ui->modulesPage) {
        ui->horizontalSpacer->show();
        ui->workspaceHeader->show();
    }
}


void Workspace::hideChrome(){
    ui->workspaceHeader->setMaximumHeight(0);
    ui->discardModifications->setMaximumHeight(0);
    ui->saveModifications->setMaximumHeight(0);
    ui->callExportOrPrint->setText("Cancel");
    ui->leftBar->hide();
    ui->rightBar->hide();

    if (ui->contentPager->currentWidget() == ui->addModulePage) {
        ui->horizontalSpacer->hide();
        ui->workspaceHeader->hide();
    }
}


void Workspace::loadCategories(QString type,QListWidget*list){

    for (const QString &source : QList<QString> { "_common", WORKSPACE_CLASS, WORKSPACE_PATH} ) {
        for (const QString &category : QDir(ROOT+type+"/"+source).entryList(QDir::Dirs)) {
            if (category=="."||category=="..") continue;

            if ((source!="_common")&&QFile(ROOT+type+"/_common/"+category+"/label").exists()) {
                continue;
            }

            QFile label(ROOT+type+"/"+source+"/"+category+"/label."+LANG);

            if (!label.exists()){
                label.setFileName(ROOT+type+"/"+source+"/"+category+"/label");
                if (!label.exists()) continue;
            }

            label.open(QFile::ReadOnly);

            QListWidgetItem*item = new QListWidgetItem;
            item->setText(QString(label.readAll()).remove("\n").remove("\r"));
            item->setIcon(QIcon(ROOT+type+"/"+source+"/"+category+"/icon.svg"));
            item->setData(42,category);
            item->setSizeHint(QSize(48,38));

            list->addItem(item);

            label.close();
        }
    }

    list->sortItems();

    if (list->item(0)) {
        list->itemActivated(list->item(0));
    }
}

void Workspace::loadConfig(){
    QFile file(ROOT+"/workspaces/"+WORKSPACE_PATH+"/config");

    if (file.open(QFile::ReadOnly)){
        QTextStream file_data(&file);
        while (!file_data.atEnd()) {
            QStringList line = processSAMLLine(file_data.readLine());

            QString property = line[0];
            QString value = line[1];

            if (property == "title") {
                ui->workspaceName->setText(value);
                continue;
            }

            if (property == "forbid[addModule]") {
                ui->addModule->setHidden(value == "true");
                ui->moduleOptions->setHidden(value == "true");
                ui->line->setHidden(value == "true");
                continue;
            }

            if (property == "forbid[export]") {
                ui->callExportOrPrint->setHidden(value == "true");
                continue;
            }

            if (property == "forbid[saveChanges]") {
                ui->discardModifications->setHidden(value == "true");
                ui->saveModifications->setProperty("forceDiscard",true);
                ui->saveModifications->setText(value == "true"?"Exit":"Save");
                continue;
            }

            if (property == "forbid[changeTitle]") {
                ui->workspaceName->setStyleSheet(value == "true"?"border:0;":"");
                ui->workspaceName->setReadOnly(value == "true");
                ui->workspaceName->setAttribute(Qt::WA_TransparentForMouseEvents);
                continue;
            }

            if (property == "class") {
                WORKSPACE_CLASS = value;
                continue;
            }

            if (property == "topbar[background]") {
                setStyleSheet(styleSheet().replace("#65ffff; /**/",value+";"));
                continue;
            }

            if (property == "leftbar[background]") {
                setStyleSheet(styleSheet().replace("#aa55ff; /**/",value+";"));
                continue;
            }

            if (property == "topbutton->normal[background]") {
                setStyleSheet(styleSheet().replace("#aaffff; /**/",value+";"));
                continue;
            }

            if (property == "topbutton->hover[background]") {
                setStyleSheet(styleSheet().replace("#c8ffff; /**/",value+";"));
                continue;
            }

            if (property == "topbutton->pressed[background]") {
                setStyleSheet(styleSheet().replace("#96e1e1; /**/",value+";"));
                continue;
            }

            if (property == "workspacename[background]") {
                setStyleSheet(styleSheet().replace("#c9ffff; /**/",value+";"));
                continue;
            }

            if (property == "savebutton->normal[background]") {
                setStyleSheet(styleSheet().replace("#00AA00; /**/",value+";"));
                continue;
            }

            if (property == "savebutton->hover[background]") {
                setStyleSheet(styleSheet().replace("#14BE14; /**/",value+";"));
                continue;
            }

            if (property == "savebutton->pressed[background]") {
                setStyleSheet(styleSheet().replace("#009600; /**/",value+";"));
                continue;
            }

            if (property == "discardbutton->normal[background]") {
                setStyleSheet(styleSheet().replace("#FF7C89; /**/",value+";"));
                continue;
            }

            if (property == "discardbutton->hover[background]") {
                setStyleSheet(styleSheet().replace("#FF907F; /**/",value+";"));
                continue;
            }

            if (property == "discardbutton->pressed[background]") {
                setStyleSheet(styleSheet().replace("#EB5E75; /**/",value+";"));
                continue;
            }

            if (property == "toolbutton->normal[background]") {
                setStyleSheet(styleSheet().replace("#41eb6b; /**/",value+";"));
                continue;
            }

            if (property == "toolbutton->hover[background]") {
                setStyleSheet(styleSheet().replace("#69ff89; /**/",value+";"));
                continue;
            }

            if (property == "toolbutton->pressed[background]") {
                setStyleSheet(styleSheet().replace("#23cd4d; /**/",value+";"));
                continue;
            }

            if (property == "rightbar[background]") {
                setStyleSheet(styleSheet().replace("#55ff7f; /**/",value+";"));
                continue;
            }

            if (property == "modulearea[background]") {
                setStyleSheet(styleSheet().replace("#aa0000; /**/",value+";"));
                continue;
            }

            if (property == "modulelist[background]") {
                setStyleSheet(styleSheet().replace("#ffff00; /**/",value+";"));
                continue;
            }

            if (property == "separator[color]") {
                setStyleSheet(styleSheet().replace("rgba(0, 0, 0, 128); /**/",value+";"));
                continue;
            }

            if (property == "addmodulebutton->normal[background]") {
                setStyleSheet(styleSheet().replace("#ebeb00; /**/",value+";"));
                continue;
            }

            if (property == "addmodulebutton->hover[background]") {
                setStyleSheet(styleSheet().replace("#d7d700; /**/",value+";"));
                continue;
            }

            if (property == "addmodulebutton->pressed[background]") {
                setStyleSheet(styleSheet().replace("#cdcd00; /**/",value+";"));
                continue;
            }

            if (property == "space[background]") {
                setStyleSheet(
                  styleSheet().replace("rgb(255, 170, 0)/**/",value+";")
                              .replace("#aa0000; /**/",value+";")
                              .replace("#00007f; /**/",value+";")
                              .replace("#005500; /**/",value+";")
                );
                continue;
            }

            if (property == "box[background]") {
                setStyleSheet(
                  styleSheet().replace("#00aa7f; /**/",value+";")
                              .replace("#00aaff; /**/",value+";")
                );
                continue;
            }

            if (property == "box_lists_item->hover[background]") {
                setStyleSheet(
                  styleSheet().replace("#00966b; /**/",value+";")
                              .replace("#008ce1; /**/",value+";")
                );
                continue;
            }

            if (property == "box_lists_item->pressed[background]") {
                setStyleSheet(
                  styleSheet().replace("#008261; /**/",value+";")
                              .replace("#0082d7; /**/",value+";")
                );
                continue;
            }
        }
        file.close();
        return;
    }

    print("File '"+ROOT+"/workspaces/"+WORKSPACE_PATH+"/config"+"' not found");
}

void Workspace::loadModule(QString module){

    if (loaded_modules[module] == nullptr) {
        QString layout = "";

        QFile file(ROOT+"/workspaces/"+WORKSPACE_PATH+"/modules/"+module+".yml");
        if (file.open(QFile::ReadOnly)){
            QTextStream file_data(&file);
            while (!file_data.atEnd()) {
                QStringList line = processSAMLLine(file_data.readLine());

                QString property = line[0];
                QString value = line[1];

                if (property == "layout") {
                    layout = value;
                    continue;
                }
            }

            ModuleViewer*page = new ModuleViewer();
            ui->modulesPage->addWidget(page);
            loadLayout(ROOT+"/workspaces/"+WORKSPACE_PATH+"/layouts/"+layout+".yml",page);
            page->loadScript(ROOT+"/workspaces/"+WORKSPACE_PATH+"/scripts/welcome.lua");

            ui->modulesPage->setCurrentWidget(page);

            loaded_modules[module] = page;
            return;
        }

        print("File '"+ROOT+"/workspaces/"+WORKSPACE_PATH+"/modules/"+module+".yml' not found");
        return;
    }

    ui->modulesPage->setCurrentWidget(loaded_modules[module]);
}
