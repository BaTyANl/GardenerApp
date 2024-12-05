#include "harvesting.h"
#include "ui_harvesting.h"

Harvesting::Harvesting(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Harvesting)
{
    this->close();
    ui->setupUi(this);
    connect(ui->exitButton, &QPushButton::clicked, this, &Harvesting::exitButtonClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Harvesting::addButtonClicked);
}

void Harvesting::exitButtonClicked(){
    this->close();
}
void Harvesting::addButtonClicked(){
    QDateTime first = QDateTime::fromString(ui->lineEdit_2->text() + "T00:00:00", "yyyy-MM-ddThh:mm:ss");
    bool ok;
    int second = ui->lineEdit->text().toInt(&ok);
    if (!first.isValid() || !ok) {
        QMessageBox::warning(this, "Ошибка ввода", "Введите корректные данные!");
        return;
    }
    DataPoint newValue;
    newValue.date = first;
    newValue.Value = second;
    emit added(newValue);
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    this->close();
}

Harvesting::~Harvesting()
{
    delete ui;
}
