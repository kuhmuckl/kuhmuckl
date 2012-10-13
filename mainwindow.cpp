#include "mainwindow.h"
#include "ui_mainwindow.h"

/**********************************************************
  Initialization and Finalization
**********************************************************/

/** Form constructor
  All important initializations happen right here.
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    colTrans["cowname"].push_back("'Kuhname'");
    colTrans["lifenb"].push_back("'Lebensnummer'");
    colTrans["cownb"].push_back("'Kuhnummer'");
    colTrans["ldays"].push_back("'Lak - Tage'");
    colTrans["lnb"].push_back("'Lak - Nummer'");
    colTrans["milk"].push_back("'Milch in kg'");
    colTrans["fat"].push_back("'Fett in %'");
    colTrans["protein"].push_back("'Eiweiß in %'");
    colTrans["harn"].push_back("'Harnstoff in %'");
    colTrans["cells"].push_back("'Zellen'");
    colTrans["milkall"].push_back("'Milch (aufgelaufen)'");
    colTrans["fatall"].push_back("'Fett (aufgelaufen)'");
    colTrans["proteinall"].push_back("'Eiweiß (aufgelaufen)'");
    colTrans["farmID"].push_back("'Betriebsnummer'");
    colTrans["messuredate"].push_back("'Messdatum'");
    colTrans["messurenb"].push_back("'Prüfnummer'");
    for(QMap<QString, QString>::const_iterator i = colTrans.begin();i != colTrans.end();i++)
        cols.append(i.key());
    order = "lnb";
    farmID = "345514";

    ui->setupUi(this);
    session = 0; //Initialization on reset
    //TODO: Initialize menue entries (Recent used stuff)
    on_actionReset_triggered();

    connect(ui->tv_Cows->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(on_sectionClicked(int)));
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
  'nuf said.
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
    ui->menuDiagram->setEnabled(false);
    ui->menuReport->setEnabled(false);
    ui->tab_Cows->setEnabled(false);
    ui->tab_CowView->setEnabled(false);
    ui->tab_Diagram->setEnabled(false);
    ui->tab_Report->setEnabled(false);

    QSqlTableModel* farmModel = new QSqlTableModel(this,session->getSQLDatabase());
    ui->tv_Farms->setModel(farmModel);
    farmModel->setTable("Farms");
    farmModel->select();

    refresh_cowTable();
}

void MainWindow::refresh_cowTable()
{
    QSqlQueryModel* cowModel = new QSqlTableModel(this, session->getSQLDatabase());
    ui->tv_Cows->setModel(cowModel);
    QSqlQuery query(session->getSQLDatabase());

    QString statement = "SELECT DISTINCT ";

    //add Columns
    if(cols.length()>0)
    {
        for(int i = 0; i < cols.length(); i++)
            statement.append(cols[i]+" AS "+colTrans[cols[i]]+", ");
        //Remove last ","
        statement.remove(statement.length()-2,1);
    }
    else
        statement.append("* ");

    statement.append("FROM cows WHERE farmID ="+farmID+" ");

    for(int i = 0; i != filter.length(); i++)
        statement.append(filter[i]+" ");

    statement.append("ORDER BY "+order);

    query.exec(statement);
    cowModel->setQuery(query);
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
    // Search function goes here
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
    //Search function goes here
}


/**********************************************************
  Actions concerning the "Kuhübersicht" section
**********************************************************/

/** Button that saves changes in View of single Cow
*/
void MainWindow::on_pb_SaveChanges_clicked()
{
    //Aply changes via QSqlTableView ...
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
    //calculating axis, draw things and create models
}


/**********************************************************
  Actions concerning the "Auswertung" section
**********************************************************/

/** Add Property Button
  Adds another property to the existing Report.
*/
void MainWindow::on_pb_AddProperty_clicked()
{
    //read property from combobox and add it using
    //session->getReport()->addProperty(...);
    if (!ui->cB_diff->checkState())
        ui->lw_Property->addItem(new QListWidgetItem(ui->cob_Property->currentText()));
    else
        if   ((ui->cob_Property->currentText() != "Lebensnummer")
            &&(ui->cob_Property->currentText() != "Kuhname")
            &&(ui->cob_Property->currentText() != "Messdatum")
            &&(ui->cob_Property->currentText() != "Betrieb"))
        {
            ui->lw_Property->addItem(new QListWidgetItem(ui->cob_Property->currentText()+" Diff."));
        }
}
/** Add And Filter Button
  Adds another property to the existing Report.
*/
void MainWindow::on_pb_AddAndFilter_clicked()
{
    //read filter from comboboxes and add it
    if (ui->lw_Filter->count() > 0)
        ui->lw_Filter->addItem(new QListWidgetItem(
            "AND "+ui->cob_FilterName->currentText()+" "+ui->cob_FilterOperator->currentText()+" "+ui->le_FilterValue->text()
        ));
    else
        ui->lw_Filter->addItem(new QListWidgetItem(
            ui->cob_FilterName->currentText()+" "+ui->cob_FilterOperator->currentText()+" "+ui->le_FilterValue->text()
        ));
}
/** Add Or Filter Button
  Adds another property to the existing Report.
*/
void MainWindow::on_pb_AddOrFilter_clicked()
{
    //read filter from comboboxes and add it
    if (ui->lw_Filter->count() > 0)
        ui->lw_Filter->addItem(new QListWidgetItem(
            "OR "+ui->cob_FilterName->currentText()+" "+ui->cob_FilterOperator->currentText()+" "+ui->le_FilterValue->text()
        ));
    else
        ui->lw_Filter->addItem(new QListWidgetItem(
            ui->cob_FilterName->currentText()+" "+ui->cob_FilterOperator->currentText()+" "+ui->le_FilterValue->text()
        ));
}
/**
Clicking on the Cols to sort
*/
void MainWindow::on_sectionClicked(int x)
{
    order = cols[x];
    refresh_cowTable();
}

/**********************************************************
  All actions triggered by Menuebar
**********************************************************/

void MainWindow::on_actionReadFromFile_triggered()
{
    QFileDialog dialog;
    QString filename = dialog.getOpenFileName();
    session->readNewDataFromFile(filename);
}

void MainWindow::on_action_Report_DOC_triggered()
{
    QFileDialog dialog;
    QString filename = dialog.getSaveFileName();
    session->getReport()->exportAsDOC(filename);
}

void MainWindow::on_action_Report_PDF_triggered()
{
    QFileDialog dialog;
    QString filename = dialog.getSaveFileName();
    session->getReport()->exportAsPDF(filename);
}

void MainWindow::on_action_Report_TextFile_triggered()
{
    QFileDialog dialog;
    QString filename = dialog.getSaveFileName();
    session->getReport()->exportAsTextFile(filename);
}

void MainWindow::on_actionPrintReport_triggered()
{
    session->getReport()->print();
}

void MainWindow::on_action_Diagram_PDF_triggered()
{
    QFileDialog dialog;
    QString filename = dialog.getSaveFileName();
    session->getDiagram()->exportAsPDF(filename);
}

void MainWindow::on_action_Diagram_SVG_triggered()
{
    QFileDialog dialog;
    QString filename = dialog.getSaveFileName();
    session->getDiagram()->exportAsSVG(filename);
}

void MainWindow::on_action_Diagram_JPEG_triggered()
{
    QFileDialog dialog;
    QString filename = dialog.getSaveFileName();
    session->getDiagram()->exportAsJPG(filename);
}

void MainWindow::on_actionPrintDiagram_triggered()
{
    session->getDiagram()->print();
}

void MainWindow::on_actionLoadDiagramTemplate_triggered()
{
    QFileDialog dialog;
    QString filename = dialog.getOpenFileName();
    session->getDiagram()->print();
}

void MainWindow::on_actionSaveDiagramTemplate_triggered()
{
    QFileDialog dialog;
    QString filename = dialog.getSaveFileName();
    session->getDiagram()->saveLayoutToFile(filename);
}

void MainWindow::on_actionNewDiagramTemplate_triggered()
{
    //reset diagram axis
}

void MainWindow::on_actionNewReportTemplate_triggered()
{
    // reset report Values .. destroy and create new?
}

void MainWindow::on_actionSaveReportTemplate_triggered()
{
    QFileDialog dialog;
    QString filename = dialog.getSaveFileName();
    session->getReport()->saveLayoutToFile(filename);
}

void MainWindow::on_actionLoadReportTemplate_triggered()
{
    QFileDialog dialog;
    QString filename = dialog.getOpenFileName();
    session->getReport()->loadLayoutFromFile(filename);
}

void MainWindow::on_action_ToSaveMyTemplates_triggered()
{
    //Simple QMessagebox should be enough
}

void MainWindow::on_action_ToReadNewData_triggered()
{
    //Simple QMessagebox should be enough
}

void MainWindow::on_action_ToPrint_triggered()
{
    //Simple QMessagebox should be enough
}

void MainWindow::on_action_AreTabsDisabled_triggered()
{
    //Simple QMessagebox should be enough
}

void MainWindow::on_action_ToCreateReports_triggered()
{
    //Simple QMessagebox should be enough
}

void MainWindow::on_action_ToCreateDiagrams_triggered()
{
    //Simple QMessagebox should be enough
}

void MainWindow::on_action_ToCheckCowDetails_triggered()
{
    //Simple QMessagebox should be enough
}

void MainWindow::on_action_ToChoseAFarm_triggered()
{
    //Simple QMessagebox should be enough
}

void MainWindow::on_actionTeam_triggered()
{
    //Simple QMessagebox should be enough, mybe including our logo
}

void MainWindow::on_actionAbout_triggered()
{
    //Simple QMessagebox should be enough
}

/**********************************************************
  Actions that haven't been sorted into the upper sections!!
**********************************************************/

