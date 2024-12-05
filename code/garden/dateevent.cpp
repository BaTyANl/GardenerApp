#include "dateevent.h"
#include "ui_dateevent.h"

DateEvent::DateEvent(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DateEvent)
{
    this->close();
    ui->setupUi(this);
    connect(ui->exitButton, &QPushButton::clicked, this, &DateEvent::exitButton_clicked);
    ui->textEdit->clear();
    //loadEvents();
    if (events.empty()){
        ui->label->setText("События " + date.toString());
        ui->textEdit->append("Событий данного числа нет.");
    } else {
        ui->label->setText("События " + date.toString());
        for (int i = 0; i < events.size(); ++i) {
            QString event = QString("%1) %2").arg(i+1).arg(events[i]);
            ui->textEdit->append(event);
        }
    }
}

void DateEvent::update(){
    ui->textEdit->clear();
    //loadEvents();
    if (events.empty()){
        ui->label->setText("События " + date.toString());
        ui->textEdit->append("Событий данного числа нет.");
    } else {
        ui->label->setText("События " + date.toString());
        for (int i = 0; i < events.size(); ++i) {
            QString event = QString("%1) %2").arg(i+1).arg(events[i]);
            ui->textEdit->append(event);
        }
    }
}

void DateEvent::setDate(QDate newDate){
    this->date = newDate;
}

void DateEvent::setEvents(QStringList newEvents){
    this->events = newEvents;
}


void DateEvent::exitButton_clicked(){
    this->close();
}

DateEvent::~DateEvent()
{
    delete ui;
}
