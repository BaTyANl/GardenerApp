#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , accWindow(new AccWindow(this))
    , calWindow(new Calendar(this))
    , plantWindow(new Plants(this))
{
    ui->setupUi(this);
    this->raise();
    connect(ui->plantButton, &QPushButton::clicked, this, &MainWindow::plantButtonClicked);
    connect(ui->accButton, &QPushButton::clicked, this, &MainWindow::accButtonClicked);
    connect(ui->calButton, &QPushButton::clicked, this, &MainWindow::calButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::accButtonClicked() {
    accWindow = new AccWindow(this);
    accWindow->resize(size());
    accWindow->show();
    accWindow->raise();
}

void MainWindow::calButtonClicked() {
   // connect(signWindow, &SignWindow::userSigned, this, &MainWindow::onUserRegistered);
    calWindow->show();
    calWindow->raise();
}

void MainWindow::plantButtonClicked() {
    plantWindow = new Plants(this);
    plantWindow->resize(size());
    plantWindow->show();
    plantWindow->raise();
}


