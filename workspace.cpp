#include "workspace.h"
#include "ui_workspace.h"

Workspace::Workspace(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Workspace)
{
    ui->setupUi(this);
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
        ui->leftBar->move(0,ui->topBar->height()+2);
        ui->leftBar->resize(200,event->size().height()-ui->leftBar->y());
        ui->hamburguerButton->show();

        if (ui->hamburguerButton->isChecked()) {
            ui->leftBar->show();
        }
        return;
    }

    ui->leftBar->show();
    ui->contentArea->insertWidget(0,ui->leftBar);
    ui->hamburguerButton->hide();
}


void Workspace::showChrome()
{
    int topBarHeight = ui->topBar->height();

    ui->workspaceHeader->setMaximumHeight(topBarHeight);
    ui->discardModifications->setMaximumHeight(topBarHeight);
    ui->saveModifications->setMaximumHeight(topBarHeight);
    ui->callExportOrPrint->setText("Export or Print");
    ui->leftBar->show();
    ui->rightBar->show();
}


void Workspace::hideChrome(){
    ui->workspaceHeader->setMaximumHeight(0);
    ui->discardModifications->setMaximumHeight(0);
    ui->saveModifications->setMaximumHeight(0);
    ui->callExportOrPrint->setText("Cancel");
    ui->leftBar->hide();
    ui->rightBar->hide();
}

