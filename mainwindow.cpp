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
    ui->setupUi(this);
    session = 0; //Initialization on reset
    //TODO: Initialize menue entries (Recent used stuff)
    on_actionReset_triggered();

    connect(ui->tv_Cows->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(on_sectionClicked(int)));
    connect(ui->cob_Table , SIGNAL(currentIndexChanged(int)),this,SLOT(on_changeConfig(int)));
    connect(ui->cob_TableCh , SIGNAL(currentIndexChanged(int)),this,SLOT(on_changeConfig(int)));

    typedef QMap<QString, QString> ColTransMap;

    ui->cob_Property->clear();
    ui->cob_FilterName->clear();
    for(ColTransMap::const_iterator iter = session->colTrans.begin(); iter!=session->colTrans.end();iter++)
        if (iter.key() != "farms.ID")
        {
            ui->cob_Property->addItem(iter.value().mid(1,iter.value().length()-2));
            ui->cob_FilterName->addItem(iter.value().mid(1,iter.value().length()-2));
        }

    fillComboBox(ui->cob_XAxis);
    fillComboBox(ui->cob_YAxis);
}

/** Form destructor
  Don't forget to free your variables.
*/
MainWindow::~MainWindow()
{
    delete ui;
    delete session;
}

/**Function to fill Comboboxes with properties ... attention, hard coded */
void MainWindow::fillComboBox(QComboBox* cb){
    cb->clear();
    cb->insertItem(1,session->colTrans["cows.ldays"]);
    cb->insertItem(1,session->colTrans["cows.ldays"]);
    cb->insertItem(1,session->colTrans["cows.lnb"]);
    cb->insertItem(1,session->colTrans["cows.milk"]);
    cb->insertItem(1,session->colTrans["cows.fat"]);
    cb->insertItem(1,session->colTrans["cows.protein"]);
    cb->insertItem(1,session->colTrans["cows.harn"]);
    cb->insertItem(1,session->colTrans["cows.cells"]);
    cb->insertItem(1,session->colTrans["cows.milkall"]);
    cb->insertItem(1,session->colTrans["cows.fatall"]);
    cb->insertItem(1,session->colTrans["proteinall"]);
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

    session->colTrans["cows.lifenb"]="'Lebensnummer'";
    session->colTrans["cows.cowname"]="'Kuhname'";
    session->colTrans["cows.cownb"]="'Kuhnummer'";
    session->colTrans["cows.ldays"]="'Lak-Tage'";
    session->colTrans["cows.lnb"]="'Lak-Nummer'";
    session->colTrans["cows.milk"]="'Milch in kg'";
    session->colTrans["cows.fat"]="'Fett in %'";
    session->colTrans["cows.protein"]="'Eiweiß in %'";
    session->colTrans["cows.harn"]="'Harnstoff in %'";
    session->colTrans["cows.cells"]="'Zellen'";
    session->colTrans["cows.milkall"]="'Milch (aufgelaufen)'";
    session->colTrans["cows.fatall"]="'Fett (aufgelaufen)'";
    session->colTrans["proteinall"]="'Eiweiß (aufgelaufen)'";
    session->colTrans["cows.farmID"]="'Betriebs-Nummer'";
    session->colTrans["cows.messuredate"]="'Messdatum'";
    session->colTrans["cows.messurenb"]="'Prüfnummer'";
    session->colTrans["farms.id"]="'Betriebs-Nummer'";
    session->colTrans["farms.name"]="'Betriebs-name'";
    session->colTrans["farms.lastname"]="'Besitzer Nachname'";
    session->colTrans["farms.firstname"]="'Besitzer Vorname'";
    session->colTrans["farms.street"]="'Straße'";
    session->colTrans["farms.PLZ"]="'PLZ'";
    session->colTrans["farms.city"]="'Ort'";
    session->colTrans["farms.tel"]="'Telefon'";
    session->colTrans["farms.fax"]="'FAX'";
    session->colTrans["farms.hint"]="'Bemerkung'";
    session->colTrans["farms.createdate"]="'Erstellungsdatum'";
    session->colTrans["farms.changedate"]="'letzte Änderung'";

    refresh_tableCon();
    if (session->tableCon.length() > 0) load_Table(0);
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

    ui->lw_Property->clear();
    ui->lw_Filter->clear();

    for(int i=0;i<session->cols.length();i++)
        ui->lw_Property->addItem((session->colTrans[session->cols[i]]).mid(1,session->colTrans[session->cols[i]].length()-2));

    for(int i=0;i<session->filter.length();i++)
    {
        QString germanFilter="";
        QStringList l = session->filter[i].split(" ");
        int bias;
        if ((l[0] == "OR")||(l[0] == "AND"))
            bias = 1;
        else
            bias = 0;

        if (l[0] == "OR")
            germanFilter.append("ODER ");
        if (l[0] == "AND")
            germanFilter.append("UND ");

        germanFilter.append((session->colTrans[l[bias]]).mid(1,session->colTrans[l[bias]].length()-2)+" ");

        germanFilter.append(l[bias+1]+" ");

        for (int i=bias+2;i<l.length();i++)
            germanFilter.append(l[i]);

        ui->lw_Filter->addItem(germanFilter);

    }
}

void MainWindow::refresh_tableCon()
{
    QDir dir("");

    QStringList fileFilter;
    fileFilter.append("*.tbl");
    QStringList flist = dir.entryList(fileFilter);

    session->tableCon.clear();
    ui->cob_Table->clear();
    ui->cob_TableCh->clear();
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

    statement.append("FROM cows JOIN farms ON cows.farmID=farms.ID WHERE (cows.farmID="+session->farmID+" ");

    if (session->filter.length() > 0)
        statement.append("AND (");
    for(int i = 0; i != session->filter.length(); i++)
        statement.append(session->filter[i]+" ");

    if (session->filter.length() > 0)
        statement.append(")");

    if (session->order != "")
        statement.append(") ORDER BY "+session->order);

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

void MainWindow::on_changeConfig(int index)
{
    if(index != -1)
    {
        if(sender()->objectName() == ui->cob_Table->objectName())
            ui->cob_TableCh->setCurrentIndex(ui->cob_Table->currentIndex());
        else
            ui->cob_Table->setCurrentIndex(ui->cob_TableCh->currentIndex());
        load_Table(index);
        refresh_cowTable();
    }
}


/**********************************************************
  Actions concerning the "Betriebe" section
**********************************************************/

/** Select Button
  Sets a farm active and enables necessary fields.
*/
void MainWindow::on_pb_FarmsSelectMarked_clicked()
{
    int row;

    QModelIndexList selectedList = ui->tv_Farms->selectionModel()->selectedRows();
    if (selectedList.count()>0)
    {
        row = selectedList.at(0).row();

        ui->tab_Cows->setEnabled(true);
        ui->menuDataSet->setEnabled(true);
        ui->tab_Diagram->setEnabled(true);
        ui->menuDiagram->setEnabled(true);
        ui->tab_Report->setEnabled(true);
        ui->menuReport->setEnabled(true);
        //session->setActiveFarm(&session->getFarm(index?));
    }
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
    QGraphicsScene* scene = new QGraphicsScene(0,0,ui->gv_Diagram->width()-10,
                                               ui->gv_Diagram->height()-10);
    session->createDiagram(ui->cob_XAxis->currentText(),
                           ui->cob_YAxis->currentText(),
                           scene);
    ui->gv_Diagram->setScene(scene);
    //calculating axis, draw things and create models
}


/**********************************************************
  Actions concerning the "Tabellen verwalten" section
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
        session->cols.append(session->colTrans.key("'"+ui->cob_Property->currentText()+"'"));
    }
    else
        if   ((ui->cob_Property->currentText() != "Lebensnummer")
            &&(ui->cob_Property->currentText() != "Kuhname")
            &&(ui->cob_Property->currentText() != "Messdatum")
            &&(ui->cob_Property->currentText() != "Betrieb"))
        {
            ui->lw_Property->addItem(new QListWidgetItem(ui->cob_Property->currentText()+" Diff."));
        }
    refresh_cowTable();
}
/** Add And Filter Button
  Adds another property to the existing Report.
*/
void MainWindow::on_pb_AddAndFilter_clicked()
{
    QString filterName = ui->cob_FilterName->currentText();
    QString filterOperator = ui->cob_FilterOperator->currentText();
    QString filterValue = ui->le_FilterValue->text();

    //read filter from comboboxes and add it
    if (session->filter.length() > 0)
    {
        ui->lw_Filter->addItem(new QListWidgetItem(
            "UND "+filterName+" "+filterOperator+" '"+filterValue+"'"
        ));
        session->filter.append("AND "+session->colTrans.key("'"+filterName+"'")+" "+filterOperator+" '"+filterValue+"'");
    }
    else
    {
        ui->lw_Filter->addItem(new QListWidgetItem(
                                   filterName+" "+filterOperator+" '"+filterValue+"'"
        ));
        session->filter.append(session->colTrans.key("'"+filterName+"'")+" "+filterOperator+" '"+filterValue+"'");
    }
    refresh_cowTable();
}
/** Add Or Filter Button
  Adds another property to the existing Report.
*/
void MainWindow::on_pb_AddOrFilter_clicked()
{
    QString filterOperator = ui->cob_FilterOperator->currentText();
    QString filterName = ui->cob_FilterName->currentText();
    QString filterValue = ui->le_FilterValue->text();

    //read filter from comboboxes and add it
    if (session->filter.length() > 0)
    {
        ui->lw_Filter->addItem(new QListWidgetItem(
            "ODER "+filterName+" "+filterOperator+" '"+filterValue+"'"
        ));
        session->filter.append("OR "+session->colTrans.key("'"+filterName+"'")+" "+filterOperator+" '"+filterValue+"'");
    }
    else
    {
        ui->lw_Filter->addItem(new QListWidgetItem(
            filterName+" "+filterOperator+" '"+filterValue+"'"
        ));
        session->filter.append(session->colTrans.key("'"+filterName+"'")+" "+filterOperator+" '"+filterValue+"'");
    }
    refresh_cowTable();
}

/**
Clicking on the Cols to sort
*/
void MainWindow::on_sectionClicked(int x)
{
    session->order = session->cols[x];
    refresh_cowTable();
}


void MainWindow::on_pb_delFilter_clicked()
{
    int index = ui->lw_Filter->row(ui->lw_Filter->currentItem());

    ui->lw_Filter->takeItem(index);
    session->filter.removeAt(index);

    if ((index == 0)&&(session->filter.size()))
    {
        session->filter[0] = session->filter[0].right(session->filter[0].length()-session->filter[0].indexOf(" ")-1);
        ui->lw_Filter->insertItem(0,ui->lw_Filter->item(0)->text().right(ui->lw_Filter->item(0)->text().length()-ui->lw_Filter->item(0)->text().indexOf(" ")-1));
        session->filter.removeAt(1);
        ui->lw_Filter->takeItem(1);
    }
    refresh_cowTable();
}

void MainWindow::on_pb_DelProperty_clicked()
{
    int index = ui->lw_Property->row(ui->lw_Property->currentItem());

    ui->lw_Property->takeItem(index);
    session->cols.removeAt(index);
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
    refresh_cowTable();
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

void MainWindow::on_pb_propertyUp_clicked()
{
    int index = ui->lw_Property->row(ui->lw_Property->currentItem());
    if (index > 0)
    {
        session->cols.insert(index,session->cols.takeAt(index-1));

        ui->lw_Property->insertItem(index-1,ui->lw_Property->takeItem(index));
        ui->lw_Property->setCurrentRow(index-1);
    }
    refresh_cowTable();
}

void MainWindow::on_pb_propertyDown_clicked()
{
    int index = ui->lw_Property->row(ui->lw_Property->currentItem());
    if (index < ui->lw_Property->count()-1)
    {
        session->cols.insert(index,session->cols.takeAt(index+1));

        ui->lw_Property->insertItem(index+1,ui->lw_Property->takeItem(index));
        ui->lw_Property->setCurrentRow(index+1);
    }
    refresh_cowTable();
}

void MainWindow::on_pb_FilterUp_clicked()
{
    int index = ui->lw_Filter->row(ui->lw_Filter->currentItem());
    if (index > 0)
    {
        session->cols.insert(index,session->cols.takeAt(index-1));

        ui->lw_Filter->insertItem(index-1,ui->lw_Filter->takeItem(index));
        ui->lw_Filter->setCurrentRow(index-1);
    }
    refresh_cowTable();
}

void MainWindow::on_pb_FilterDown_clicked()
{
    int index = ui->lw_Filter->row(ui->lw_Filter->currentItem());
    if (index < ui->lw_Filter->count()-1)
    {
        session->cols.insert(index,session->cols.takeAt(index+1));

        ui->lw_Filter->insertItem(index+1,ui->lw_Filter->takeItem(index));
        ui->lw_Filter->setCurrentRow(index+1);
    }
    refresh_cowTable();
}

void MainWindow::on_sb_saveTable_clicked()
{
    bool ok;
    QInputDialog iDial;
    iDial.setCancelButtonText("Abbrechen");
    iDial.setOkButtonText("Speichern");
    QString text = iDial.getText(this, "Speichern","Bitte Tabellennamen eingeben:",QLineEdit::Normal,"",&ok);

    if (ok && !text.isEmpty())
    {
        QString fileName = session->getNextFreeFileName();

        QDir dir("");
        QStringList fileFilter;
        fileFilter.append("*.tbl");
        QStringList flist = dir.entryList(fileFilter);

        for(int i=0;i<flist.length();i++)
        {
            QFile lTable(flist[i]);
            lTable.open(QIODevice::ReadOnly | QIODevice::Text);
            QTextStream stream(&lTable);
            QString title = stream.readLine();
            lTable.close();
            if (title == text)
            {
                ok = false;
                fileName = flist[i];
                break;
            }
        }

        if (!ok)
        {
            QMessageBox mB;
            mB.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
            mB.setText("Diese Tabelle ist schon vorhanden. Überschreiben?");
            mB.setWindowTitle("Überschreiben");
            mB.setButtonText(1,"Speichern");
            mB.setButtonText(2,"NICHT Speichern");

            if (mB.exec() == QMessageBox::Ok)
                ok = true;
        }

        if (ok)
        {
            QFile writeFile(fileName);
            writeFile.open(QFile::WriteOnly | QFile::Truncate);
            QTextStream stream(&writeFile);
            stream << text+"\r\n";
            for (int i=0;i<session->cols.length();i++)
                stream << session->cols[i]+"\r\n";
            stream << "#\r\n";
            for (int i=0;i<session->filter.length();i++)
                stream << session->filter[i]+"\r\n";
            stream << "#\r\n";
            stream << session->order+"\r\n";
            stream << "###";

            writeFile.close();
        }
    }
}
