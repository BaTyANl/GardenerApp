#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , accountWin(new AccountWin(this))
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
    accountWin = new AccountWin(this);
    accountWin->resize(size());
    accountWin->show();
    accountWin->raise();
}

void MainWindow::calButtonClicked() {
    calWindow->resize(size());
    calWindow->show();
    calWindow->raise();
}

void MainWindow::plantButtonClicked() {
    plantWindow = new Plants(this);
    plantWindow->resize(size());
    plantWindow->show();
    plantWindow->raise();
}


