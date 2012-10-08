#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    session = new Session();
    on_actionReset_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete session;
}

void MainWindow::on_actionQuit_triggered()
{
       close();
}

void MainWindow::on_actionReset_triggered()
{
    if(session)
        delete session;
    session = new Session();
    ui->menuDataSet->setEnabled(false);
    ui->menuDiagram->setEnabled(false);
    ui->menuReport->setEnabled(false);
    ui->tab_Cows->setEnabled(false);
    ui->tab_CowView->setEnabled(false);
    ui->tab_Diagram->setEnabled(false);
    ui->tab_Report->setEnabled(false);
}

void MainWindow::on_pb_FarmsSelectMarked_clicked()
{
    ui->tab_Cows->setEnabled(true);
    ui->menuDataSet->setEnabled(true);
    ui->tab_Diagram->setEnabled(true);
    ui->menuDiagram->setEnabled(true);
    ui->tab_Report->setEnabled(true);
    ui->menuReport->setEnabled(true);
}

void MainWindow::on_pb_SelectMarked_clicked()
{
    ui->tab_CowView->setEnabled(true);
}
