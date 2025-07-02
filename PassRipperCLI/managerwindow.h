#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QWidget>
#include <QString>
#include "manager.h"

namespace Ui {
class ManagerWindow;
}

class ManagerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerWindow(QWidget *parent = nullptr);
    ~ManagerWindow();

    void appendLog(const QString &message);

private slots:
    void on_btnChooseZip_clicked();
    void on_btnSend_clicked();

private:
    Ui::ManagerWindow *ui;
    QString filePath;
    QString alphabet = "abcdefghijklmnopqrstuvwxyz";
    QString specialChars = "!@#$%^&*()_-+=,<.>/?;:'{|[}]";

    void setInputsEnabled(bool enabled);
    void passwordFound(const QString &password);
    Manager* manager;
};

#endif // MANAGERWINDOW_H
