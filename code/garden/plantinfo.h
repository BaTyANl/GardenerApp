#ifndef PLANTINFO_H
#define PLANTINFO_H

#include <QWidget>
#include <QString>

namespace Ui {
class PlantInfo;
}

class PlantInfo : public QWidget
{
    Q_OBJECT

public:
    explicit PlantInfo(QWidget *parent = nullptr);
    ~PlantInfo();
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
    Ui::PlantInfo *ui;

private slots:
    void exitButton_clicked();
};

#endif // PLANTINFO_H
