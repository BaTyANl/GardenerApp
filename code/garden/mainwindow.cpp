#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , regWindow(new RegWindow(this))
    , signWindow(new SignWindow(this))
{
    ui->setupUi(this);
    ui->labelSigned->hide();
    ui->exitButton->hide();
    connect(ui->regButton, &QPushButton::clicked, this, &MainWindow::regButtonclicked);
    connect(ui->signButton, &QPushButton::clicked, this, &MainWindow::signButtonclicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::onUserUnRegistered);
    loadCurrentUser();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onUserRegistered(const QString& login){
    if (is_signed == false){
        is_signed = true;
        ui->labelSigned->setText(login + ",\nВы вошли в аккаунт!");
        ui->labelSigned->show();
        ui->exitButton->show();
        ui->signButton->hide();
        ui->regButton->hide();
    }
}

void MainWindow::regButtonclicked() {
    connect(regWindow, &RegWindow::userRegistered, this, &MainWindow::onUserRegistered);
    regWindow->show();
    regWindow->raise();
}

void MainWindow::signButtonclicked() {
    connect(signWindow, &SignWindow::userSigned, this, &MainWindow::onUserRegistered);
    signWindow->show();
    signWindow->raise();
}

void MainWindow::onUserUnRegistered(){
    if (is_signed == true){
        is_signed = false;
        QMessageBox::information(this, "Успех", "Вы вышли из аккаунта");
        ui->labelSigned->hide();
        ui->exitButton->hide();
        ui->signButton->show();
        ui->regButton->show();
        QFile::remove("current_user.txt");
    }
}

void MainWindow::loadCurrentUser(){
    QFile file("current_user.txt");
    if (!file.exists())
        return;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString login = file.readLine().split('\n').first();
        file.close();
        onUserRegistered(login);
    }
}
