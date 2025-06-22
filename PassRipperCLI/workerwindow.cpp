#include "workerwindow.h"
#include "ui_workerwindow.h"

#include <QRegularExpression>
#include <QMessageBox>

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
    int port = ui->spinBoxPort->value();
    int numThreads = ui->spinBoxThreads->value();

    if(!isValidIpAddress(ip))
    {
        QMessageBox::warning(this, "Invalid IP address!", "Please enter a valid IPv4 address");
        return;
    }

    appendLogs(QString("Attempting connection to %1:%2...").arg(ip).arg(port));

    //logika -
    //worker = new Worker(ip,port,)
}

bool WorkerWindow::isValidIpAddress(const QString &ip)
{
    QRegularExpression ipRegex(
        R"(^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\."
        R"(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\."
        R"(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\."
        R"(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$)");

    return ipRegex.match(ip).hasMatch();
}

//zrobione pod connecta - może zbędne - zobaczymy
void appendLogs(const QString &msg)
{
    ui->textEditLogs->append(msg);
}
