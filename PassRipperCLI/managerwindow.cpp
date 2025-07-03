#include "managerwindow.h"
#include "ui_managerwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QThread>

ManagerWindow::ManagerWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ManagerWindow)
{
    ui->setupUi(this);
}

ManagerWindow::~ManagerWindow()
{
    delete ui;
}

void ManagerWindow::on_btnChooseZip_clicked()
{
    QString tmpPath = QFileDialog::getOpenFileName(this, "Select ZIP File", "", "ZIP Files (*.zip)");
    if (!tmpPath.isEmpty())
    {
        filePath = tmpPath;
        ui->lineEditZipPath->setText(filePath);
    }
}

void ManagerWindow::on_btnSend_clicked()
{
    if(filePath.isEmpty())
    {
        QMessageBox::warning(this, "Missing File", "Please select a ZIP file first.");
        return;
    }

    bool includeSpecialChars = ui->checkSpecialChars->isChecked();
    int maxLen = ui->spinBoxMaxLen->value();

    setInputsEnabled(false);

    appendLog(QString("Sending job: File=%1, MaxLength=%2, Specials=%3")
                  .arg(filePath)
                  .arg(maxLen)
                  .arg(includeSpecialChars ? "Yes" : "No"));

    manager = new Manager(ui->spinBoxPort->text().toStdString().data(), ui->spinBoxWorkerCount->value(), this);

    manager->maxLen = maxLen;
    manager->alphabet = ui->checkSpecialChars->isChecked() ? alphabet+specialChars : alphabet;
    manager->zipPath = ui->lineEditZipPath->text();
    QThread* thread = new QThread(this);
    manager->moveToThread(thread);
    connect(thread, &QThread::started, manager, &Manager::run);
    // Cleanup:
    connect(manager,    &Manager::finished,thread, &QThread::quit);
    connect(manager,    &Manager::finished, manager,    &QObject::deleteLater);
    connect(thread,    &QThread::finished,thread,    &QObject::deleteLater);
    thread->start();
}

void ManagerWindow::setInputsEnabled(bool enabled)
{
    ui->btnChooseZip->setEnabled(enabled);
    ui->checkSpecialChars->setEnabled(enabled);
    ui->spinBoxMaxLen->setEnabled(enabled);
    ui->btnSend->setEnabled(enabled);
    ui->spinBoxPort->setEnabled(enabled);
    ui->spinBoxWorkerCount->setEnabled(enabled);
}

void ManagerWindow::appendLog(const QString &message)
{
    ui->textEditLogs->append(message);
}
