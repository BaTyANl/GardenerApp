#include "plantinfo.h"
#include "ui_plantinfo.h"

PlantInfo::PlantInfo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlantInfo)
{
    ui->setupUi(this);
    this->hide();
    ui->label->setText(name);
    ui->textEdit->setPlainText(desc + "\n" + "Дата высадки: " + date_in + "\n" + "Дата сбора: " + date_out);
    connect(ui->pushButton, &QPushButton::clicked, this, &PlantInfo::exitButton_clicked);
}

void PlantInfo::setName(QString name){
    this->name = name;
}

void PlantInfo::setDesc(QString desc){
    this->desc = desc;
}

void PlantInfo::setIn(QString in){
    this->date_in = in;
}

void PlantInfo::setOut(QString out){
    this->date_out = out;
}

void PlantInfo::update(){
    ui->label->setText(name);
    ui->textEdit->setPlainText(desc + "\n" + "Дата высадки: " + date_in + "\n" + "Дата сбора: " + date_out);
}

void PlantInfo::exitButton_clicked(){
    this->close();
}

PlantInfo::~PlantInfo()
{
    delete ui;
}
