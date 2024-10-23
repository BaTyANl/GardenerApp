#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "regwindow.h"
#include "signwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadCurrentUser();

private:
    RegWindow *regWindow;
    SignWindow *signWindow;
    Ui::MainWindow *ui;
    bool is_signed = false;

private slots:
    void regButtonclicked();
    void signButtonclicked();
    void onUserRegistered(const QString& login);
    void onUserUnRegistered();
};
#endif // MAINWINDOW_H
