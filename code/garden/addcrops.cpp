#include "addcrops.h"
#include "ui_addcrops.h"

AddCrops::AddCrops(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddCrops)
{
    ui->setupUi(this);
    setWindowTitle("Добавить событие");
    resize(0.75 * parent->width(), 0.25 * parent->height());

    QVBoxLayout *layout = new QVBoxLayout(this);

    dateEdit = new QDateTimeEdit(this);
    dateEdit->setDisplayFormat("dd MMM yyyy HH:mm");
    layout->addWidget(dateEdit);

    valueEdit = new QLineEdit(this);
    valueEdit->setPlaceholderText("Введите значение");
    layout->addWidget(valueEdit);

    QPushButton *addButton = new QPushButton("Добавить", this);
    layout->addWidget(addButton);

    connect(addButton, &QPushButton::clicked, this, &AddCrops::addEvent);
}

QDateTime AddCrops::getDateTime() const {
    return dateEdit->dateTime();
}

double AddCrops::getValue() const {
    return valueEdit->text().toDouble();
}

void AddCrops::addEvent() {
    if (!valueEdit->text().isEmpty()) {
        accept();
    }
}
AddCrops::~AddCrops()
{
    delete ui;
}
