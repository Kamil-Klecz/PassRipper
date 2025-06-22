#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workerwindow.h"
#include "managerwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , workerWindow(nullptr)
    , managerWindow(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnConfirm_clicked()
{
    if(ui->radioWorker->isChecked())
    {
        workerWindow = new WorkerWindow();
        workerWindow->show();
    }
    else if(ui->radioManager->isChecked())
    {
        managerWindow = new ManagerWindow();
        managerWindow->show();
    }

    this->close();
}

void MainWindow::on_btnClose_clicked()
{
    QApplication::quit();
}
