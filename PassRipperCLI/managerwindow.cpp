#include "managerwindow.h"
#include "ui_managerwindow.h"

#include <QFileDialog>
#include <QMessageBox>

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
                  .arg(selectedFilePath)
                  .arg(maxLength)
                  .arg(includeSpecials ? "Yes" : "No"));

    //logika
}

void ManagerWindow::setInputsEnabled(bool enabled)
{
    ui->btnChooseZip->setEnabled(enabled);
    ui->checkSpecialChars->setEnabled(enabled);
    ui->spinBoxMaxLen->setEnabled(enabled);
    ui->btnSend->setEnabled(enabled);
}

//zrobione pod connecta - może do wywalenia
void ManagerWindow::appendLog(const QString &message)
{
    ui->textEditLogs->append(message);
}

void ManagerWindow::passwordFound(const QString &password)
{
    QMessageBox::information(this, "Password Found", "The password is: " + password);
    QApplication::quit();
}
