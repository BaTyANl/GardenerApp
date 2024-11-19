#ifndef DATEEVENT_H
#define DATEEVENT_H

#include <QWidget>
#include <QDate>
#include <QString>

namespace Ui {
class DateEvent;
}

class DateEvent : public QWidget
{
    Q_OBJECT

public:
    explicit DateEvent(QWidget *parent = nullptr);
    ~DateEvent();
    void update();
    void setDate(QDate newDate);
    void setEvents(QStringList newEvents);

private slots:
    void exitButton_clicked();

private:
    QDate date;
    QStringList events;

    Ui::DateEvent *ui;
};

#endif // DATEEVENT_H
