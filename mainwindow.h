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
    void on_actionBeenden_triggered();

    void on_actionStartseite_triggered();

private:
    Ui::MainWindow  *ui;
    Session*        session;
};

#endif // MAINWINDOW_H
