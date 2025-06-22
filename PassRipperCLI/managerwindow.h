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

private:
    Ui::ManagerWindow *ui;
    QString filePath;

    void setInputsEnabled(bool enabled);
    void appendLog(const QString &message);
};

#endif // MANAGERWINDOW_H
