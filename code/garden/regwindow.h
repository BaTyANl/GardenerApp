#ifndef REGWINDOW_H
#define REGWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QFile>
#include <QMessageBox>

namespace Ui {
class RegWindow;
}

class RegWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegWindow(QWidget *parent = nullptr);
    ~RegWindow();

private:
    Ui::RegWindow *ui;
    bool isUserExists(const QString& login);
    void saveUser(const QString& login, const QString& password);

private slots:
    void exitButton_clicked();
    void registerButton_clicked();
signals:
    void userRegistered(const QString& login);
};


#endif // REGWINDOW_H
