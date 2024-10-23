#ifndef SIGNWINDOW_H
#define SIGNWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QFile>

namespace Ui {
class SignWindow;
}

class SignWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SignWindow(QWidget *parent = nullptr);
    ~SignWindow();

private:
    Ui::SignWindow *ui;
    int isUserValid(const QString& login, const QString& password);

private slots:
    void exitButton_clicked();
    void signButton_clicked();
signals:
    void userSigned(const QString& login);
};

#endif // SIGNWINDOW_H
