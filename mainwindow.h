#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Session.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionQuit_triggered();

    void on_actionReset_triggered();

    void on_pb_FarmsSelectMarked_clicked();

    void on_pb_SelectMarked_clicked();

private:
    Ui::MainWindow  *ui;
    Session*        session;
};

#endif // MAINWINDOW_H
