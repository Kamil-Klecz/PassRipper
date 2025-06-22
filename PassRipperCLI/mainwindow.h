#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class WorkerWindow;
class ManagerWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnConfirm_clicked();
    void on_btnClose_clicked();

private:
    Ui::MainWindow *ui;
    WorkerWindow *workerWindow;
    ManagerWindow *managerWindow;
};

#endif // MAINWINDOW_H
