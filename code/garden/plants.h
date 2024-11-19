#ifndef PLANTS_H
#define PLANTS_H

#include "plantinfo.h"
#include <QWidget>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QStringListModel>
#include <QMessageBox>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QMap>
#include <QVariantMap>
#include <QListView>
#include <QScroller>
#include <QScrollerProperties>

namespace Ui {
class Plants;
}

class Plants : public QWidget
{
    Q_OBJECT

public:
    explicit Plants(QWidget *parent = nullptr);
    ~Plants();

private:
    QMap<QString, QVariantMap> plantData;
    PlantInfo *plantInfoW;
    QMap<QString, QVariantMap> loadPlants();
    Ui::Plants *ui;
    void setupListView(QListView &listView);
private slots:
    void openWindow(const QModelIndex &index);
    void exitButton_clicked();
};

#endif // PLANTS_H
