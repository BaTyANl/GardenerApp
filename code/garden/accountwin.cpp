#include "accountwin.h"
#include "ui_accountwin.h"

AccountWin::AccountWin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AccountWin)
    , signWindow(new SignWindow(this))
    , regWindow(new RegWindow(this))
{
    this->close();
    ui->setupUi(this);
    loadCurrentUser();
    connect(ui->exitButton, &QPushButton::clicked, this, &AccountWin::exitButtonClicked);
}

void AccountWin::onUserNotRegistered(){

    if (fl == 2){
        ui->verticalLayout_2->removeWidget(labelNice);
        labelNice->close();
        delete(labelNice);
        ui->horizontalLayout->removeWidget(signoutButton);
        signoutButton->close();
        delete(signoutButton);
        ui->verticalLayout_3->removeWidget(chartView);
        chartView->close();
        delete(chartView);
        ui->verticalLayout_3->removeWidget(cropButton);
        cropButton->close();
        delete(cropButton);
        ui->verticalLayout_3->removeWidget(clearButton);
        clearButton->close();
        delete(clearButton);
        this->repaint();
        this->update();
    }

    fl = 1;
    labelNot = new QLabel("Вы не вошли в аккаунт!");
    ui->verticalLayout_3->addWidget(labelNot, 0, Qt::AlignCenter);

    spacerNot = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    ui->horizontalLayout->addItem(spacerNot);

    labelBad = new QLabel("Графики недоступны для гостевых аккаунтов");
    ui->verticalLayout_3->addWidget(labelBad, 0, Qt::AlignTop);

    signButton = new QPushButton("Войти в аккаунта");
    ui->verticalLayout_3->addWidget(signButton);
    connect(signButton, &QPushButton::clicked, this, &AccountWin::signButtonclicked);

    regButton = new QPushButton("Зарегистрировать аккаунт");
    ui->verticalLayout_3->addWidget(regButton);
    connect(regButton, &QPushButton::clicked, this, &AccountWin::regButtonclicked);
}

void AccountWin::onUserRegistered(const QString& login){
    if (fl == 1){
        ui->verticalLayout_3->removeWidget(labelNot);
        labelNot->close();
        delete(labelNot);
        ui->horizontalLayout->removeItem(spacerNot);
        delete(spacerNot);
        ui->verticalLayout_3->removeWidget(labelBad);
        labelBad->close();
        delete(labelBad);
        ui->verticalLayout_3->removeWidget(signButton);
        signButton->close();
        delete(signButton);
        ui->verticalLayout_3->removeWidget(regButton);
        regButton->close();
        delete(regButton);
        this->repaint();
        this->update();
    }
    fl = 2;
    is_signed = true;
    labelNice = new QLabel(login + ", Вы вошли в аккаунт!");
    ui->verticalLayout_3->addWidget(labelNice, 0, Qt::AlignCenter);
    signoutButton = new QPushButton("Выйти из аккаунта");
    ui->horizontalLayout->addWidget(signoutButton, 5, Qt::AlignRight);
    connect(signoutButton, &QPushButton::clicked, this, &AccountWin::onUserUnRegistered);

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
    ui->verticalLayout_3->addWidget(chartView);

    cropButton = new QPushButton("Добавить сборы");
    ui->verticalLayout_3->addWidget(cropButton, 0, Qt::AlignBottom);
    clearButton = new QPushButton("Очистить график");
    ui->verticalLayout_3->addWidget(clearButton, 0, Qt::AlignBottom);
}

void AccountWin::updateAxes() {
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

void AccountWin::regButtonclicked() {
    connect(regWindow, &RegWindow::userRegistered, this, &AccountWin::onUserRegistered);
    regWindow->resize(size());
    regWindow->show();
    regWindow->raise();
}

void AccountWin::signButtonclicked() {
    connect(signWindow, &SignWindow::userSigned, this, &AccountWin::onUserRegistered);
    signWindow->resize(size());
    signWindow->show();
    signWindow->raise();
}

void AccountWin::onUserUnRegistered(){
    if (is_signed == true){
        is_signed = false;
        QMessageBox::information(this, "Успех", "Вы вышли из аккаунта");
        QFile::remove("current_user.txt");
        onUserNotRegistered();
    }
}

void AccountWin::loadCurrentUser(){
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

void AccountWin::exitButtonClicked(){
    this->close();
}


AccountWin::~AccountWin()
{
    delete ui;
}
