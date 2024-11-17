#ifndef ACCWINDOW_H
#define ACCWINDOW_H

#include <QDialog>
#include <QInputDialog>
#include <QLabel>
#include "regwindow.h"
#include "signwindow.h"
#include "addcrops.h"
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QDateTime>
#include <QGestureEvent>

namespace Ui {
class AccWindow;
}

class AccWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AccWindow(QWidget *parent = nullptr);
    void loadCurrentUser();
    ~AccWindow();
private:

    Ui::AccWindow *ui;
    RegWindow *regWindow;
    SignWindow *signWindow;
    bool is_signed;
    QLineSeries *series;
    QChart *chart;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;
    int fl = 0;
    QLabel *labelNot;
    QSpacerItem *spacerNot;
    QLabel *labelBad;
    QPushButton *signButton;
    QPushButton *regButton;

    QLabel *labelNice;
    QPushButton *signoutButton;
    QChartView *chartView;
    QPushButton *cropButton;
    QPushButton *clearButton;



private slots:
    void regButtonclicked();
    void signButtonclicked();
    void onUserRegistered(const QString& login);
    void onUserNotRegistered();
    void onUserUnRegistered();
    void openAddEventDialog();
    void exitButtonClicked();
    void updateAxes();
};

#endif // ACCWINDOW_H
