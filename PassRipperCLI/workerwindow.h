#ifndef WORKERWINDOW_H
#define WORKERWINDOW_H

#include <QWidget>
#include <QString>
#include "worker.h"

namespace Ui
{
class WorkerWindow;
}

class WorkerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WorkerWindow(QWidget *parent = nullptr);
    ~WorkerWindow();

    void appendLogs(const QString &msg);
    void setInputsEnabled(bool enabled);

private slots:
    void on_btnConnect_clicked();

private:
    Ui::WorkerWindow *ui;
    Worker *worker;

    bool isValidIpAddress(const QString &ip);
};

#endif // WORKERWINDOW_H
