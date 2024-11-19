#ifndef CALENDAR_H
#define CALENDAR_H


#include "dateevent.h"
#include <QWidget>
#include <QCalendarWidget>
#include <QMap>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStringList>
#include <QPainter>
#include <QTextCharFormat>

namespace Ui {
class Calendar;
}

class Calendar : public QWidget
{
    Q_OBJECT

public:
    explicit Calendar(QWidget *parent = nullptr);
    ~Calendar();


private:
    Ui::Calendar *ui;
    void deployCalendar();
    bool isSigned;
    QCalendarWidget *calendar;
    QMap<QDate, QStringList> events;
    QMap<QDate, bool> marks;

    void loadEvents();
    void applyEventColor(const QDate &date);

    DateEvent* dateEvent;


private slots:
    void onDateSelected(QDate date);
    void exitButton_clicked();

};

#endif // CALENDAR_H
