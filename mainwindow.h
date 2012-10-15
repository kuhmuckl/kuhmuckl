#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFileDialog>
#include <QSqlTableModel>
#include <QComboBox>

#include "Session.h"

/**
  Mainly auto-generated Headerfile to manage
  events and global variables.
*/

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void fillComboBox(QComboBox* cb);
private slots:

    void on_actionQuit_triggered();

    void on_actionReset_triggered();

    void on_pb_FarmsSelectMarked_clicked();

    void on_pb_SelectMarked_clicked();

    void on_pb_FarmsSearchAndMark_clicked();

    void on_pb_CowsSearchAndMark_clicked();

    void on_pb_SaveChanges_clicked();

    void on_pb_CreatDiagram_clicked();

    void on_pb_AddProperty_clicked();

    void on_pb_AddAndFilter_clicked();

    void on_pb_AddOrFilter_clicked();

    void refresh_tableCon();

    void refresh_farmTable();

    void refresh_cowTable();

    void on_sectionClicked(int);

    void on_changeConfig(int index);

    void on_actionReadFromFile_triggered();

    void on_action_Report_DOC_triggered();

    void on_action_Report_PDF_triggered();

    void on_action_Report_TextFile_triggered();

    void on_actionPrintReport_triggered();

    void on_action_Diagram_PDF_triggered();

    void on_action_Diagram_SVG_triggered();

    void on_action_Diagram_JPEG_triggered();

    void on_actionPrintDiagram_triggered();

    void on_actionLoadDiagramTemplate_triggered();

    void on_actionSaveDiagramTemplate_triggered();

    void on_actionNewDiagramTemplate_triggered();

    void on_actionNewReportTemplate_triggered();

    void on_actionSaveReportTemplate_triggered();

    void on_actionLoadReportTemplate_triggered();

    void on_action_ToSaveMyTemplates_triggered();

    void on_action_ToReadNewData_triggered();

    void on_action_ToPrint_triggered();

    void on_action_AreTabsDisabled_triggered();

    void on_action_ToCreateReports_triggered();

    void on_action_ToCreateDiagrams_triggered();

    void on_action_ToCheckCowDetails_triggered();

    void on_action_ToChoseAFarm_triggered();

    void on_actionTeam_triggered();

    void on_actionAbout_triggered();

    void load_Table(int nb);

    void on_pb_delFilter_clicked();

    void on_pb_DelProperty_clicked();

    void on_pushButton_clicked();

    void on_pb_propertyUp_clicked();

private:
    Ui::MainWindow  *ui;
    Session*        session;
    QSqlQueryModel*         cowModel;
    QSqlQueryModel*         farmModel;
};

#endif // MAINWINDOW_H
