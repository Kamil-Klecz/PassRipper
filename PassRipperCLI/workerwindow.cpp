#include "workerwindow.h"
#include "ui_workerwindow.h"

#include <QRegularExpression>
#include <QMessageBox>
#include <QHostAddress>
#include <QThread>

WorkerWindow::WorkerWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WorkerWindow)
{
    ui->setupUi(this);

}

WorkerWindow::~WorkerWindow()
{
    delete ui;
}

void WorkerWindow::on_btnConnect_clicked()
{
    QString ip = ui->lineEditIP->text().trimmed();

    if(!isValidIpAddress(ip))
    {
        QMessageBox::warning(this, "Invalid IP address!", "Please enter a valid IPv4 address");
        return;
    }

    setInputsEnabled(false);

    QString port = QString::number(ui->spinBoxPort->value());
    int numThreads = ui->spinBoxThreads->value();

    appendLogs(QString("\nAttempting connection to %1:%2...").arg(ip, port));

    worker = new Worker(ip.toStdString(), port.toStdString(), this);
    worker->numThreads = numThreads;

    QThread* thread = new QThread(this);
    worker->moveToThread(thread);
    connect(thread, &QThread::started, worker, &Worker::run);
    connect(worker, &Worker::logMessage, this, &WorkerWindow::appendLogs);

    // Cleanup:
    connect(worker,    &Worker::finished,thread, &QThread::quit);
    connect(worker,    &Worker::finished, worker,    &QObject::deleteLater);
    connect(thread,    &QThread::finished,thread,    &QObject::deleteLater);

    thread->start();
}

bool WorkerWindow::isValidIpAddress(const QString &ip)
{
    QHostAddress address;
    if (address.setAddress(ip)) {
        return address.protocol() == QAbstractSocket::IPv4Protocol;
    }
    return false;
}

void WorkerWindow::appendLogs(const QString &msg)
{
    ui->textEditLogs->append(msg);
}

void WorkerWindow::setInputsEnabled(bool enabled)
{
    ui->btnConnect->setEnabled(enabled);
    ui->spinBoxPort->setEnabled(enabled);
    ui->spinBoxThreads->setEnabled(enabled);
    ui->lineEditIP->setEnabled(enabled);
}
