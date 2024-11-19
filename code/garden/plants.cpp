#include "plants.h"
#include "ui_plants.h"

class ColorDelegate : public QStyledItemDelegate {
public:
    explicit ColorDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter* painter, const QStyleOptionViewItem &option, const QModelIndex &index)
        const override{
        QColor background;
        if(index.row() % 2 == 0){
            background = QColor("#CCFFCC");
        }
        if(index.row() % 2 == 1){
            background = QColor("#CCCCFF");
        }
        painter->fillRect(option.rect, background);
        QStyledItemDelegate::paint(painter, option, index);
        painter->save();
        painter->setPen(QPen(Qt::gray, 1));
        painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
        painter->restore();
    }
};


Plants::Plants(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Plants)
    , plantInfoW(new PlantInfo(this))
{
    ui->setupUi(this);
    this->close();
    setupListView(*ui->listView);
    loadPlants();
    connect(ui->pushButton, &QPushButton::clicked, this, &Plants::exitButton_clicked);
}

void Plants::openWindow(const QModelIndex &index){
    QString name = ui->listView->model()->data(index, Qt::DisplayRole).toString();
    QVariantMap plantInfo = plantData.value(name);
    QString description = plantInfo["description"].toString();
    QString date_in = plantInfo["date_in"].toString();
    QString date_out = plantInfo["date_out"].toString();
    plantInfoW->setName(name);
    plantInfoW->setDesc(description);
    plantInfoW->setIn(date_in);
    plantInfoW->setOut(date_out);
    plantInfoW->update();
    plantInfoW->resize(size());
    plantInfoW->show();
    plantInfoW->raise();
}

void Plants::setupListView(QListView &listView){
    plantData = loadPlants();
    QStringList plantNames = plantData.keys();
    QStringListModel *model = new QStringListModel(&listView);
    model->setStringList(plantNames);
     ui->listView->setModel(model);
    ColorDelegate *delegate = new ColorDelegate(&listView);
    ui->listView->setItemDelegate(delegate);
    connect(ui->listView, &QListView::clicked, this, &Plants::openWindow);
}

QMap<QString, QVariantMap> Plants::loadPlants(){
    QMap<QString, QVariantMap> plantData;
    QFile file(":/plantsbase.json");
    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::critical(this, "ошибка", "файл не открыт");
        return plantData;
    }
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()){
        QMessageBox::critical(this, "ошибка", "содержимое");
        return plantData;
    }
    QJsonArray plantsArray = doc.array();
    for(const QJsonValue &value : plantsArray){
        QJsonObject plant = value.toObject();
        QVariantMap plantInfo;
        QString name = plant["name"].toString();
        plantInfo["description"] = plant["description"].toString();
        plantInfo["date_in"] = plant["date_in"].toString();
        plantInfo["date_out"] = plant["date_out"].toString();
        plantData.insert(name, plantInfo);
    }
    return plantData;
}

void Plants::exitButton_clicked(){
    this->close();
}

Plants::~Plants()
{
    delete ui;
}
