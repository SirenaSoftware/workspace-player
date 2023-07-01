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

