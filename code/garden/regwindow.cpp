#include "regwindow.h"
#include "ui_regwindow.h"

RegWindow::RegWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegWindow)
{
    ui->setupUi(this);
    this->close();
    connect(ui->exitButton, &QPushButton::clicked, this, &RegWindow::exitButton_clicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &RegWindow::registerButton_clicked);
}

RegWindow::~RegWindow()
{
    delete ui;
}

void RegWindow::exitButton_clicked() {
    ui->lineEditLogin->clear();
    ui->lineEditPassword->clear();
    this->close();
}

void RegWindow::registerButton_clicked(){
    QString login = ui->lineEditLogin->text();
    QString password = ui->lineEditPassword->text();
    if (login.isEmpty() || password.isEmpty()){
        QMessageBox::warning(this, "Ошибка", "Поля не заполены");
        ui->lineEditLogin->clear();
        ui->lineEditPassword->clear();
        return;
    }
    if (isUserExists(login)){
        QMessageBox::warning(this, "Ошибка", "Пользователь с таким именемм уже существует");
        ui->lineEditLogin->clear();
        ui->lineEditPassword->clear();
        return;
    }
    saveUser(login, password);
    emit userRegistered(login);
    QMessageBox::information(this, "Успех", "Регистрация успешна");
    ui->exitButton->click();
}

bool RegWindow::isUserExists(const QString& login){
    QFile file("users.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QString existingLogin = line.split(",").first();
            if (existingLogin == login) {
                file.close();
                return true;
            }
        }
        file.close();
    }
    return false;
}

void RegWindow::saveUser(const QString& login, const QString& password){
    QFile file("users.txt");
    if(file.open(QIODevice::Append | QIODevice::Text)){
        QTextStream out(&file);
        out << login << "," << password << "\n";
        file.close();
    }
    QFile cur_file("current_user.txt");
    if(cur_file.open(QIODevice::WriteOnly| QIODevice::Text)){
        QTextStream outCur(&cur_file);
        outCur << login << "\n";
        cur_file.close();
    }
}
