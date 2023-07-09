#include "workspace.h"
#include "ui_workspace.h"
#include <QTimer>

#include <QSettings>

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

    on_clock_update();
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Workspace::on_clock_update);
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

