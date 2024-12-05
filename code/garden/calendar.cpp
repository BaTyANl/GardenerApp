#include "calendar.h"
#include "ui_calendar.h"

Calendar::Calendar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Calendar)
    , dateEvent(new DateEvent(this))
{
    this->close();
    ui->setupUi(this);
    connect(ui->exitButton, &QPushButton::clicked, this, &Calendar::exitButton_clicked);
    calendar = new QCalendarWidget(this);
    connect(calendar, &QCalendarWidget::activated, this, &Calendar::onDateSelected);
    deployCalendar();
    grabGesture(Qt::SwipeGesture);
}


bool Calendar::event(QEvent *event) {
    if (event->type() == QEvent::Gesture) {
        QGestureEvent *gestureEvent = static_cast<QGestureEvent*>(event);
        if (QGesture *swipe = gestureEvent->gesture(Qt::SwipeGesture)) {
            QSwipeGesture *swipeGesture = static_cast<QSwipeGesture*>(swipe);
            handleSwipeGesture(swipeGesture);
            return true;
        }
    }
    return QWidget::event(event);
}

void Calendar::handleSwipeGesture(QSwipeGesture *swipe) {
    if (swipe->horizontalDirection() == QSwipeGesture::Left) {
        calendar->setCurrentPage(calendar->yearShown(), calendar->monthShown() + 1);
    } else if (swipe->horizontalDirection() == QSwipeGesture::Right) {
        calendar->setCurrentPage(calendar->yearShown(), calendar->monthShown() - 1);
    }
}

void Calendar::exitButton_clicked(){
    this->close();
}

void Calendar::deployCalendar(){
    ui->verticalLayout->addWidget(calendar);
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    loadEvents();
}

void Calendar::loadEvents(){
    QFile file(":/events.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open JSON file.");
        return;
    }

    QByteArray jsonData = file.readAll();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData));
    if (jsonDoc.isNull()) {
        qWarning("Failed to create JSON doc.");
        return;
    }

    QJsonArray jsonArray = jsonDoc.array();
    for (const QJsonValue &value : jsonArray) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            QString dateString = obj.value("date").toString();
            QDate date = QDate::fromString(dateString, "yyyy-MM-dd");
            if (date.isValid()) {
                marks[date] = true;
                QJsonArray eventArray = obj.value("events").toArray();
                QStringList eventList;
                for (const QJsonValue &eventValue : eventArray) {
                    if (eventValue.isString()) {
                        eventList << eventValue.toString();
                    }
                }
                events[date] = eventList;
                applyEventColor(date);
            }
        }
    }
}

void Calendar::applyEventColor(const QDate &date){
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    format.setForeground(Qt::blue);
    calendar->setDateTextFormat(date, format);
}

void Calendar::onDateSelected(QDate date){
    dateEvent->setDate(date);
    dateEvent->setEvents(events[date]);
    dateEvent->update();
    dateEvent->resize(size());
    dateEvent->show();
    dateEvent->raise();
}

Calendar::~Calendar()
{
    delete ui;
}
