#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "accountwin.h"
#include "calendar.h"
#include "plants.h"

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

private:
    Calendar* calWindow;
    Plants* plantWindow;
    AccountWin* accountWin;
    Ui::MainWindow *ui;

private slots:
    void accButtonClicked();
    void calButtonClicked();
    void plantButtonClicked();
};
#endif // MAINWINDOW_H
