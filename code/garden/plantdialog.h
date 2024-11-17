#ifndef PLANTDIALOG_H
#define PLANTDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class PlantDialog;
}

class PlantDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlantDialog(QWidget *parent = nullptr);
    ~PlantDialog();

    void setName(QString name);
    void update();
    void setDesc(QString desc);
    void setIn(QString date_in);
    void setOut(QString date_out);

private:
    QString name;
    QString desc;
    QString date_in;
    QString date_out;


    Ui::PlantDialog *ui;
private slots:
    void exitButton_clicked();
};

#endif // PLANTDIALOG_H
