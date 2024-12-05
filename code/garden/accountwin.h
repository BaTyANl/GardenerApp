#ifndef ACCOUNTWIN_H
#define ACCOUNTWIN_H

#include <QWidget>
#include <QLabel>
#include "regwindow.h"
#include "signwindow.h"
#include "harvesting.h"
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QDateTime>
#include <QSpacerItem>
#include <QGestureEvent>
#include <QVector>

namespace Ui {
class AccountWin;
}

class AccountWin : public QWidget
{
    Q_OBJECT

public:
    explicit AccountWin(QWidget *parent = nullptr);
    void loadCurrentUser();
    ~AccountWin();

private:

    QVector<DataPoint> dataPoint;
    Ui::AccountWin *ui;
    RegWindow *regWindow;
    SignWindow *signWindow;
    Harvesting *harvesting;
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
    void exitButtonClicked();
    void clearButtonClicked();
    void addButtonClicked();
    void onAdded(const DataPoint& point);

};

#endif // ACCOUNTWIN_H
