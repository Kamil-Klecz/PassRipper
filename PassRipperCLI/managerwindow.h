#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QWidget>
#include <QString>

namespace Ui {
class ManagerWindow;
}

class ManagerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerWindow(QWidget *parent = nullptr);
    ~ManagerWindow();

private slots:
    void on_btnChooseZip_clicked();
    void on_btnSend_clicked();

private:
    Ui::ManagerWindow *ui;
    QString filePath;

    void setInputsEnabled(bool enabled);
    void appendLog(const QString &message);
    void passwordFound(const QString &password);
};

#endif // MANAGERWINDOW_H
