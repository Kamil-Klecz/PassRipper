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
    QString port = QString::number(ui->spinBoxPort->value());
    int numThreads = ui->spinBoxThreads->value();

    if(!isValidIpAddress(ip))
    {
        QMessageBox::warning(this, "Invalid IP address!", "Please enter a valid IPv4 address");
        return;
    }

    appendLogs(QString("Attempting connection to %1:%2...").arg(ip, port));

    worker = new Worker(ip.toStdString(), port.toStdString(), this);
    connect(worker, &Worker::logMessage, this, &WorkerWindow::appendLogs);
    worker->setup();
    worker->numThreads = numThreads;
    worker->run();
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
