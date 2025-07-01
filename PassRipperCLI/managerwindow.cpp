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
    std::cout<<"ManagerWidnow: destructor working"<<std::endl;
    delete ui;
}

void ManagerWindow::on_btnChooseZip_clicked()
{
    std::cout<<"ManagerWidnow: btnChooseZipClicked"<<std::endl;
    QString tmpPath = QFileDialog::getOpenFileName(this, "Select ZIP File", "", "ZIP Files (*.zip)");
    if (!tmpPath.isEmpty())
    {
        filePath = tmpPath;
        ui->lineEditZipPath->setText(filePath);
    }
}

void ManagerWindow::on_btnSend_clicked()
{
    std::cout<<"ManagerWidnow: send clicked"<<std::endl;
    if(filePath.isEmpty())
    {
        QMessageBox::warning(this, "Missing File", "Please select a ZIP file first.");
        return;
    }
    std::cout<<"ManagerWidnow: File verification successful" <<std::endl;
    bool includeSpecialChars = ui->checkSpecialChars->isChecked();
    int maxLen = ui->spinBoxMaxLen->value();

    //setInputsEnabled(false);

    appendLog(QString("Sending job: File=%1, MaxLength=%2, Specials=%3")
                  .arg(filePath)
                  .arg(maxLen)
                  .arg(includeSpecialChars ? "Yes" : "No"));

    //logika
    manager = new Manager(ui->spinBoxPort->text().toStdString().data(), 1); //TODO dodać workercount
    manager->maxLen = maxLen;
    manager->zipPath = ui->lineEditZipPath->text().toStdString();
    manager->run();
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
