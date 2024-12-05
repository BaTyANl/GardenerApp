#ifndef HARVESTING_H
#define HARVESTING_H

#include <QWidget>
#include <QDateTime>
#include <QMessageBox>

struct DataPoint {
    QDateTime date;
    int Value;
};

namespace Ui {
class Harvesting;
}

class Harvesting : public QWidget
{
    Q_OBJECT

public:
    explicit Harvesting(QWidget *parent = nullptr);
    ~Harvesting();

private:
    Ui::Harvesting *ui;
    /*struct DataPoint {
        QDateTime date;
        int Value;
    };*/

private slots:
    void exitButtonClicked();
    void addButtonClicked();

signals:
    void added(const DataPoint &point);
};

#endif // HARVESTING_H
