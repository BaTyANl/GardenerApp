#ifndef ADDCROPS_H
#define ADDCROPS_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include <QDateTimeEdit>

namespace Ui {
class AddCrops;
}

class AddCrops : public QDialog
{
    Q_OBJECT

public:
    explicit AddCrops(QWidget *parent = nullptr);
    ~AddCrops();
    QDateTime getDateTime() const;
    double getValue() const;

private slots:
    void addEvent();

private:
    Ui::AddCrops *ui;
    QDateTimeEdit *dateEdit;
    QLineEdit *valueEdit;
};

#endif // ADDCROPS_H
