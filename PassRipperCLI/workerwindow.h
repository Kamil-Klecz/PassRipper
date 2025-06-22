#ifndef WORKERWINDOW_H
#define WORKERWINDOW_H

#include <QWidget>
#include "worker.h"

namespace Ui {
class WorkerWindow;
}

class WorkerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WorkerWindow(QWidget *parent = nullptr);
    ~WorkerWindow();

private slots:
    void on_btnConnect_clicked();

private:
    Ui::WorkerWindow *ui;
    Worker *worker;

    bool isValidIpAddress(const QString &ip);
};

#endif // WORKERWINDOW_H
