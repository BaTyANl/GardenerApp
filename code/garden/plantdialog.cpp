#include "plantdialog.h"
#include "ui_plantdialog.h"

PlantDialog::PlantDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PlantDialog)
{
    ui->setupUi(this);
    this->hide();
    ui->label->setText(name);
    ui->textEdit->setPlainText(desc + "\n" + "Дата высадки: " + date_in + "\n" + "Дата сбора: " + date_out);
    connect(ui->pushButton, &QPushButton::clicked, this, &PlantDialog::exitButton_clicked);
}

void PlantDialog::setName(QString name){
    this->name = name;
}

void PlantDialog::setDesc(QString desc){
    this->desc = desc;
}

void PlantDialog::setIn(QString in){
    this->date_in = in;
}

void PlantDialog::setOut(QString out){
    this->date_out = out;
}

void PlantDialog::update(){
    ui->label->setText(name);
    ui->textEdit->setPlainText(desc + "\n" + "Дата высадки: " + date_in + "\n" + "Дата сбора: " + date_out);
}

PlantDialog::~PlantDialog()
{
    delete ui;
}

void PlantDialog::exitButton_clicked(){
    this->close();
}
