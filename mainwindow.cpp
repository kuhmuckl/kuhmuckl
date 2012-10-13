#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfile.h>
#include <qtextstream.h>

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

    farmModel = new QSqlTableModel(this, session->getSQLDatabase());
    ui->tv_Farms->setModel(farmModel);

    cowModel = new QSqlTableModel(this, session->getSQLDatabase());
    ui->tv_Cows->setModel(cowModel);

    session->colTrans["cows.lifenb"].push_back("'Lebensnummer'");
    session->colTrans["cows.cowname"].push_back("'Kuhname'");
    session->colTrans["cows.cownb"].push_back("'Kuhnummer'");
    session->colTrans["cows.ldays"].push_back("'Lak - Tage'");
    session->colTrans["cows.lnb"].push_back("'Lak - Nummer'");
    session->colTrans["cows.milk"].push_back("'Milch in kg'");
    session->colTrans["cows.fat"].push_back("'Fett in %'");
    session->colTrans["cows.protein"].push_back("'Eiweiß in %'");
    session->colTrans["cows.harn"].push_back("'Harnstoff in %'");
    session->colTrans["cows.cells"].push_back("'Zellen'");
    session->colTrans["cows.milkall"].push_back("'Milch (aufgelaufen)'");
    session->colTrans["cows.fatall"].push_back("'Fett (aufgelaufen)'");
    session->colTrans["proteinall"].push_back("'Eiweiß (aufgelaufen)'");
    session->colTrans["cows.farmID"].push_back("'Betriebsnummer'");
    session->colTrans["cows.messuredate"].push_back("'Messdatum'");
    session->colTrans["cows.messurenb"].push_back("'Prüfnummer'");
    session->colTrans["farms.id"].push_back("'Betriebs-Nummer'");
    session->colTrans["farms.name"].push_back("'Name'");
    session->colTrans["farms.lastname"].push_back("'Nachname'");
    session->colTrans["farms.firstname"].push_back("'Vorname'");
    session->colTrans["farms.street"].push_back("'Straße'");
    session->colTrans["farms.PLZ"].push_back("'PLZ'");
    session->colTrans["farms.city"].push_back("'Ort'");
    session->colTrans["farms.tel"].push_back("'Telefon'");
    session->colTrans["farms.fax"].push_back("'FAX'");
    session->colTrans["farms.hint"].push_back("'Bemerkung'");
    session->colTrans["farms.createdate"].push_back("'Erstellungsdatum'");
    session->colTrans["farms.changedate"].push_back("'letzte Änderung'");

    refresh_tableCon();
    load_Table(0);
    refresh_cowTable();
    refresh_farmTable();
}

void MainWindow::load_Table(int nb)
{
    QFile loadTable(session->tableCon[nb]);
    loadTable.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&loadTable);

    session->cols.clear();
    //first line is the Tablename
    QString line= stream.readLine();
    line= stream.readLine();
    while (line != "#"){
        session->cols.append(line);
        line = stream.readLine();
    }
    session->filter.clear();
    line = stream.readLine();
    while (line != "#"){
        session->filter.append(line);
        line = stream.readLine();
    }
    line = stream.readLine();
    if (line != "#")
        session->order = line;

    loadTable.close();
}

void MainWindow::refresh_tableCon()
{
    QDir dir("");

    QStringList fileFilter;
    fileFilter.append("*.tbl");
    QStringList flist = dir.entryList(fileFilter);

    session->tableCon.clear();
    for(int i=0;i<flist.length();i++)
    {
        session->tableCon.append(flist[i]);

        //Add Tablename from file to the Comboboxes
        QFile lTable(flist[i]);
        lTable.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream stream(&lTable);
        QString title = stream.readLine();
        lTable.close();
        ui->cob_Table->addItem(title);
        ui->cob_TableCh->addItem(title);
    }
}

void MainWindow::refresh_cowTable()
{
    QString statement = "SELECT ";

    //add Columns
    for(int i = 0; i < session->cols.length(); i++)
        statement.append(session->cols[i]+" AS "+session->colTrans[session->cols[i]]+", ");
    //Remove last ","
    statement.remove(statement.length()-2,1);

    statement.append("FROM cows JOIN farms ON cows.farmID=farms.ID WHERE cows.farmID="+session->farmID+" ");

    for(int i = 0; i != session->filter.length(); i++)
        statement.append(session->filter[i]+" ");

    statement.append("ORDER BY "+session->order);

    QSqlQuery query(session->getSQLDatabase());
    query.exec(statement);
    cowModel->setQuery(query);
}

void MainWindow::refresh_farmTable()
{
    QString statement = "SELECT ";

    statement.append("id AS "+session->colTrans["farms.id"]+", ");
    statement.append("name AS "+session->colTrans["farms.name"]+", ");
    statement.append("firstname AS "+session->colTrans["farms.firstname"]+", ");
    statement.append("lastname AS "+session->colTrans["farms.lastname"]+" ");

    statement.append("FROM farms ");

    statement.append("ORDER BY name");

    QSqlQuery query(session->getSQLDatabase());
    query.exec(statement);
    farmModel->setQuery(query);
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

    int row;

    QModelIndexList selectedList = ui->tv_Farms->selectionModel()->selectedRows();
    if (selectedList.count()>0)
        row = selectedList.at(0).row();
    else
        QMessageBox::information(this,"", "Bitte Betrieb auswählen");


    QModelIndex zelle = farmModel->index(row, 0, QModelIndex()); // row, column
    session->farmID = farmModel->data(zelle, Qt::DisplayRole).toString();

    refresh_cowTable();
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
    {
        ui->lw_Property->addItem(new QListWidgetItem(ui->cob_Property->currentText()));
        //cols.append(colTrans.key(ui->cob_Property->currentText()));
    }
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
    session->order = session->cols[x];
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

