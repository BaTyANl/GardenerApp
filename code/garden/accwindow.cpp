#include "accwindow.h"
#include "ui_accwindow.h"

AccWindow::AccWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AccWindow)
    , signWindow(new SignWindow(this))
    , regWindow(new RegWindow(this))
{
    this->close();
    ui->setupUi(this);
    loadCurrentUser();
    connect(ui->exitButton, &QPushButton::clicked, this, &AccWindow::exitButtonClicked);
}

void AccWindow::onUserNotRegistered(){

    if (fl == 2){
        ui->verticalLayout->removeWidget(labelNice);
        labelNice->close();
        delete(labelNice);
        ui->horizontalLayout->removeWidget(signoutButton);
        signoutButton->close();
        delete(signoutButton);
        ui->verticalLayout_2->removeWidget(chartView);
        chartView->close();
        delete(chartView);
        ui->verticalLayout_2->removeWidget(cropButton);
        cropButton->close();
        delete(cropButton);
        ui->verticalLayout_2->removeWidget(clearButton);
        clearButton->close();
        delete(clearButton);
        this->repaint();
        this->update();
    }

    fl = 1;
    labelNot = new QLabel("Вы не вошли в аккаунт!");
    ui->verticalLayout_2->addWidget(labelNot, 0, Qt::AlignCenter);

    spacerNot = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    ui->horizontalLayout->addItem(spacerNot);

    labelBad = new QLabel("Графики недоступны для гостевых аккаунтов");
    ui->verticalLayout_2->addWidget(labelBad, 0, Qt::AlignTop);

    signButton = new QPushButton("Войти в аккаунта");
    ui->verticalLayout_2->addWidget(signButton);
    connect(signButton, &QPushButton::clicked, this, &AccWindow::signButtonclicked);

    regButton = new QPushButton("Зарегистрировать аккаунт");
    ui->verticalLayout_2->addWidget(regButton);
    connect(regButton, &QPushButton::clicked, this, &AccWindow::regButtonclicked);
}

void AccWindow::onUserRegistered(const QString& login){
    if (fl == 1){
        ui->verticalLayout_2->removeWidget(labelNot);
        labelNot->close();
        delete(labelNot);
        ui->horizontalLayout->removeItem(spacerNot);
        delete(spacerNot);
        ui->verticalLayout_2->removeWidget(labelBad);
        labelBad->close();
        delete(labelBad);
        ui->verticalLayout_2->removeWidget(signButton);
        signButton->close();
        delete(signButton);
        ui->verticalLayout_2->removeWidget(regButton);
        regButton->close();
        delete(regButton);
        this->repaint();
        this->update();
    }
    fl = 2;
    is_signed = true;
    labelNice = new QLabel(login + ", Вы вошли в аккаунт!");
    ui->verticalLayout_2->addWidget(labelNice, 0, Qt::AlignCenter);
    signoutButton = new QPushButton("Выйти из аккаунта");
    ui->horizontalLayout->addWidget(signoutButton, 5, Qt::AlignRight);
    connect(signoutButton, &QPushButton::clicked, this, &AccWindow::onUserUnRegistered);

    series = new QLineSeries();
    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Собранные культуры");
    axisX = new QDateTimeAxis;
    axisX->setFormat("dd-MM-yyyy");
    axisX->setTitleText("Дата");
    chart->addAxis(axisX, Qt::AlignBottom);
    axisX->setTickCount(2);
    axisX->setVisible(false);
    series->attachAxis(axisX);

    axisY = new QValueAxis;
    axisY->setTitleText("Количество");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout_2->addWidget(chartView);

    cropButton = new QPushButton("Добавить сборы");
    ui->verticalLayout_2->addWidget(cropButton, 0, Qt::AlignBottom);
    clearButton = new QPushButton("Очистить график");
    ui->verticalLayout_2->addWidget(clearButton, 0, Qt::AlignBottom);
    connect(cropButton, &QPushButton::clicked, this, &AccWindow::openAddEventDialog);
}

void AccWindow::openAddEventDialog() {
    AddCrops dialog(this);
    dialog.setWindowModality(Qt::ApplicationModal);
    dialog.exec();
    if (dialog.result() == QDialog::Accepted) {
        QDateTime dateTime = dialog.getDateTime();
        double value = dialog.getValue();
        series->append(dateTime.toMSecsSinceEpoch(), value);
        updateAxes();
    }
}

void AccWindow::updateAxes() {
    if (series->count() > 0) {
        qreal firstX = series->points().first().x();
        qreal lastX = series->points().last().x();
        QDateTime startDateTime = QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(firstX));
        QDateTime endDateTime = QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(lastX));
        axisX->setRange(startDateTime, endDateTime);
        axisY->setRange(0, series->points().last().y() + 10);
        axisX->setFormat("dd MMM yyyy");
    }
}



void AccWindow::regButtonclicked() {
    connect(regWindow, &RegWindow::userRegistered, this, &AccWindow::onUserRegistered);
    regWindow->resize(size());
    regWindow->show();
    regWindow->raise();
}

void AccWindow::signButtonclicked() {
    connect(signWindow, &SignWindow::userSigned, this, &AccWindow::onUserRegistered);
    signWindow->resize(size());
    signWindow->show();
    signWindow->raise();
}

void AccWindow::onUserUnRegistered(){
    if (is_signed == true){
        is_signed = false;
        QMessageBox::information(this, "Успех", "Вы вышли из аккаунта");
        QFile::remove("current_user.txt");
        onUserNotRegistered();
    }
}

void AccWindow::loadCurrentUser(){
    QFile file("current_user.txt");
    if (!file.exists()){
        is_signed = false;
        onUserNotRegistered();
    }
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString login = file.readLine().split('\n').first();
        file.close();
        is_signed = true;
        onUserRegistered(login);
    }
}

void AccWindow::exitButtonClicked(){
    this->close();
}

AccWindow::~AccWindow()
{
    delete ui;
}
