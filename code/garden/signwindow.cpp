#include "signwindow.h"
#include "ui_signwindow.h"

SignWindow::SignWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignWindow)
{
    ui->setupUi(this);
    this->close();
    connect(ui->exitButton, &QPushButton::clicked, this, &SignWindow::exitButton_clicked);
    connect(ui->signButton, &QPushButton::clicked, this, &SignWindow::signButton_clicked);
}

SignWindow::~SignWindow()
{
    delete ui;
}

void SignWindow::exitButton_clicked() {
    ui->lineEditLogin->clear();
    ui->lineEditPassword->clear();
    this->close();
}

void SignWindow::signButton_clicked(){
    QString login = ui->lineEditLogin->text();
    QString password = ui->lineEditPassword->text();
    if (login.isEmpty() || password.isEmpty()){
        QMessageBox::warning(this, "Ошибка", "Поля не заполены");
        ui->lineEditLogin->clear();
        ui->lineEditPassword->clear();
        return;
    }
    if (isUserValid(login, password) == 1){
        QMessageBox::warning(this, "Ошибка", "Пользователя не существует");
        ui->lineEditLogin->clear();
        ui->lineEditPassword->clear();
        return;
    }
    if (isUserValid(login, password) == 2){
        QMessageBox::warning(this, "Ошибка", "Пароль не верен");
        ui->lineEditPassword->clear();
        return;
    }
    if (isUserValid(login, password) == 3){
        emit userSigned(login);
        QMessageBox::information(this, "Успех", "Вход успешен");
        QFile cur_file("current_user.txt");
        if(cur_file.open(QIODevice::WriteOnly| QIODevice::Text)){
            QTextStream outCur(&cur_file);
            outCur << login << "\n";
            cur_file.close();
        }
        ui->exitButton->click();
    }
}

int SignWindow::isUserValid(const QString& login, const QString& password){
    QFile file("users.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList data = line.split(",");
            if(data.size() == 2 && data[0] == login && data[1] == password){
                file.close();
                return 3;
            }
            if(data.size() == 2 && data[0] == login && data[1] != password){
                file.close();
                return 2;
            }

        }
        file.close();
    }
    return 1;
}
