#include "souvenirshop.h"
#include "ui_souvenirshop.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include "qspinbox.h"

SouvenirShop::SouvenirShop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SouvenirShop)
{
    ui->setupUi(this);
}

SouvenirShop::SouvenirShop(QWidget *parent, StadiumManager* sm) :
    QDialog(parent),
    ui(new Ui::SouvenirShop),
    sm { sm }
{
    ui->setupUi(this);

//    QObject::connect(ui->)
}

void SouvenirShop::displaySouvenirs()
{
    QSpinBox* quantityBox;
    QTableWidget *tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(2);
    tableWidget->setHorizontalHeaderLabels({"Item", "Price"});

    // Add the items to the table
    QList<QPair<QString, double>> items = {
        {"Baseball cap", 19.99},
        {"Baseball bat", 89.39},
        {"Team pennant", 17.99},
        {"Autographed baseball", 29.99},
        {"Team jersey", 199.99}
    };

    tableWidget->setRowCount(items.size());
    for (int row = 0; row < items.size(); ++row) {
        quantityBox = new QSpinBox();

        QObject::connect(quantityBox, &QSpinBox::valueChanged,
                         this,        &SouvenirShop::purchaseItem);

        QTableWidgetItem *item = new QTableWidgetItem(items[row].first);
        tableWidget->setItem(row, 0, item);
        QTableWidgetItem *price = new QTableWidgetItem(QString::number(items[row].second, 'f', 2));
        tableWidget->setItem(row, 1, price);
    }

    // Add the table widget to the layout
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(tableWidget);
    setLayout(layout);
}

void SouvenirShop::purchaseItem(int quantity)
{
//    QWidget* widget = qobject_cast<QWidget*>(sender());
//    QString stadiumName = "Test Stadium";
//    QString souvenirName = ui->
//    int row = ui->tableWidget->indexAt(widget->pos()).row();
}

SouvenirShop::~SouvenirShop()
{
    delete ui;
}
