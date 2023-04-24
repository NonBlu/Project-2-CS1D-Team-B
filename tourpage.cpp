#include "tourpage.h"
#include "qboxlayout.h"
#include "qspinbox.h"
#include "./ui_tourpage.h"
#include "souvenirshop.h"
#include "receipt.h"
#include "ui_souvenirshop.h"
#include <QDebug>

TourPage::TourPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TourPage)
{
    ui->setupUi(this);
}

TourPage::TourPage(QWidget *parent, StadiumManager* sm) :
    QDialog(parent),
    ui(new Ui::TourPage),
    sm { sm }
{
    ui->setupUi(this);

    receipt.setModal(true);

    QObject::connect(ui->recieptButton, &QPushButton::clicked,
                     this,              &TourPage::showReceipt);

    ui->souvenirTable->insertColumn(0);
    ui->souvenirTable->insertColumn(1);
    ui->souvenirTable->insertColumn(2);

    ui->souvenirTable->setColumnWidth(0, 150);

    ui->souvenirTable->setHorizontalHeaderLabels( {"Souvenirs", "Price", "Quantity"} );

    ui->souvenirTable->horizontalHeader()->setStretchLastSection(true);

    displaySouvenirs();
}

TourPage::~TourPage()
{
    delete ui;
}

void TourPage::displaySouvenirs()
{
    QTableWidgetItem* souvenirItem;
    QTableWidgetItem* priceItem;
    QSpinBox* quantityBox;
//    QTableWidget *tableWidget = new QTableWidget(this);
//    tableWidget->setColumnCount(2);
//    tableWidget->setHorizontalHeaderLabels({"Item", "Price"});

    QString stadiumName = "Test Stadium";

    ui->souvenirTable->clearContents();
    ui->souvenirTable->setRowCount(0);

    // Add the items to the table
//    QList<QPair<QString, double>> items = {
//        {"Baseball cap", 19.99},
//        {"Baseball bat", 89.39},
//        {"Team pennant", 17.99},
//        {"Autographed baseball", 29.99},
//        {"Team jersey", 199.99}
//};

    struct Souvenir
    {
      QString item;
      double price;
    };

    QVector<Souvenir> souvenirs;

    for(int i = 0; i < 5; i++)
    {
        souvenirs.push_back(Souvenir());
    }

    souvenirs[0].item  = "Baseball cap";
    souvenirs[0].price = 19.99;
    souvenirs[1].item  = "Baseball bat";
    souvenirs[1].price = 89.39;
    souvenirs[2].item  = "Team pennant";
    souvenirs[2].price = 17.99;
    souvenirs[3].item  = "Autographed baseball";
    souvenirs[3].price = 29.99;
    souvenirs[4].item  = "Team jersey";
    souvenirs[4].price = 199.99;

    int row { };

    for (int row = 0; row < souvenirs.size(); row++)
    {
        ui->souvenirTable->insertRow(row);

        qDebug() << "Item: " << souvenirs[row].item << Qt::endl;
        qDebug() << "Price: " << souvenirs[row].price << Qt::endl;
        qDebug() << "Row: " << row << Qt::endl;

        souvenirItem = new QTableWidgetItem(souvenirs[row].item);
        priceItem    = new QTableWidgetItem(QString::number(souvenirs[row].price));
        quantityBox  = new QSpinBox();

        qDebug() << "Item: " << souvenirItem << Qt::endl;
        qDebug() << "Price: " << priceItem << Qt::endl;
        qDebug() << "Row: " << row << Qt::endl;

        QObject::connect(quantityBox, &QSpinBox::valueChanged,
                         this,        &TourPage::purchaseItem);

        quantityBox->setRange(0, 100);
        quantityBox->setSingleStep(1);
        quantityBox->setPrefix(" ");
        quantityBox->setValue(0);

        ui->souvenirTable->setItem(row, 0, souvenirItem);
        ui->souvenirTable->setItem(row, 1, priceItem);
        ui->souvenirTable->setCellWidget(row, 2, quantityBox);



//        QObject::connect(quantityBox, &QSpinBox::valueChanged,
//                         this,        &SouvenirShop::purchaseItem);

//        QTableWidgetItem *item = new QTableWidgetItem(items[row].first);
//        tableWidget->setItem(row, 0, item);
//        QTableWidgetItem *price = new QTableWidgetItem(QString::number(items[row].second, 'f', 2));
//        tableWidget->setItem(row, 1, price);
    }

    // Add the table widget to the layout
//    QVBoxLayout *layout = new QVBoxLayout();
//    layout->addWidget(tableWidget);
//    setLayout(layout);
}

void TourPage::showReceipt()
{
    receipt.displayPurchases();

    receipt.show();
}

void TourPage::purchaseItem(int quantity)
{
    QWidget* widget = qobject_cast<QWidget*>(sender());
    int row = ui->souvenirTable->indexAt(widget->pos()).row();

    QString stadiumName  = "Test Stadium";
    QString souvenirName = ui->souvenirTable->item(row, 0)->text();
    float price          = ui->souvenirTable->item(row, 1)->text().toFloat();

    receipt.addPurchase({stadiumName, souvenirName, price, quantity} );
}

//void TourPage::on_souvenirButton_clicked()
//{
//    SouvenirShop souvPage;
//    souvPage.setModal(true);
//    souvPage.exec();
//}

//void TourPage::on_recieptButton_clicked()
//{
//    Receipt recieptPage;
//    recieptPage.setModal(true);
//    recieptPage.exec();
//}

