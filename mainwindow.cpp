#include "mainwindow.h"
#include "ui_mainwindow.h"


/** Form constructor
  All important initializations happen right here.
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    session = new Session();
    //TODO: Initialize menue entries (Recent used stuff)
    on_actionReset_triggered();
}

/** Form destructor
  Don't forget to free your variables.
*/
MainWindow::~MainWindow()
{
    delete ui;
    delete session;
}


/**********************************************************
  Triggered actions of menue bar
**********************************************************/

/** Quit button
  nuff said.
*/
void MainWindow::on_actionQuit_triggered()
{
       close();
}

/** Reset button
  This function is also called on Creation of Mainwindow and
  contains all clearing and disabling steps.
*/
void MainWindow::on_actionReset_triggered()
{
    //TODO: Empty used edits, tables and graphicViews
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


/**********************************************************
  Actions concerning the "Betriebe" section
**********************************************************/

/** Select Button
  Sets a farm active and enables necessary fields.
*/
void MainWindow::on_pb_FarmsSelectMarked_clicked()
{
    ui->tab_Cows->setEnabled(true);
    ui->menuDataSet->setEnabled(true);
    ui->tab_Diagram->setEnabled(true);
    ui->menuDiagram->setEnabled(true);
    ui->tab_Report->setEnabled(true);
    ui->menuReport->setEnabled(true);
    //session->setActiveFarm(&session->getFarm(index?));
}

/** Button for searching a farm and marking it
*/
void MainWindow::on_pb_FarmsSearchAndMark_clicked()
{

}

/**********************************************************
  Actions concerning the "Kuhtabelle" section
**********************************************************/

/** Select Button
  Selects a cow and sets all fields active that can be used
  for further information about this Cow.
*/
void MainWindow::on_pb_SelectMarked_clicked()
{
    ui->tab_CowView->setEnabled(true);
    //session->setActiveAnimal(&session->getFarm(index?));
}

/** Button for searching a farm and marking it
  That includes paying attention to critical values.
*/
void MainWindow::on_pb_CowsSearchAndMark_clicked()
{

}


/**********************************************************
  Actions concerning the "Kuhübersicht" section
**********************************************************/

/** Button that saves changes in View of single Cow
*/
void MainWindow::on_pb_SaveChanges_clicked()
{

}


/**********************************************************
  Actions concerning the "Diagramm" section
**********************************************************/

/** Button to create a diagram
Creates a new Diagram by given information:
about single cow, xAxis and yAxis
*/
void MainWindow::on_pb_CreatDiagram_clicked()
{

}


/**********************************************************
  Actions concerning the "Auswertung" section
**********************************************************/

/** Add Property Button
  Adds another property to the existing Report.
*/
void MainWindow::on_pb_AddProperty_clicked()
{

}

/**********************************************************
  Actions that haven't been sorted into the upper sections!!
**********************************************************/
