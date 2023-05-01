#include "tourpage.h"
#include "qspinbox.h"
#include "./ui_tourpage.h"
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

    ui->locationLabel->setText("Dodger Stadium");

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

    QString stadiumName = "Dodger Stadium";

    ui->souvenirTable->clearContents();
    ui->souvenirTable->setRowCount(0);

//    for(auto& souvenir : sm->getStadium(stadiumName)->getSouvenirs())
//    {
//        qDebug() << souvenir.name << Qt::endl;
//    }

//    qDebug() << "\nSouvenir Shop Souvenirs\n";
//    for(auto& souvenir : sm->getStadium("Marlins Park")->getSouvenirs())
//    {
//        qDebug() << souvenir.name << ": " << souvenir.price;
//    }

//    struct Souvenir
//    {
//      QString item;
//      double price;
//    };

//    for(int i = 0; i < 5; i++)
//    {
//        souvenirs.push_back(Souvenir());
//    }

//    souvenirs[0].item  = "Baseball cap";
//    souvenirs[0].price = 19.99;
//    souvenirs[1].item  = "Baseball bat";
//    souvenirs[1].price = 89.39;
//    souvenirs[2].item  = "Team pennant";
//    souvenirs[2].price = 17.99;
//    souvenirs[3].item  = "Autographed baseball";
//    souvenirs[3].price = 29.99;
//    souvenirs[4].item  = "Team jersey";
//    souvenirs[4].price = 199.99;

    int row { };

//    for (int row = 0; row < souvenirs.size(); row++)
    for(auto& souvenir : sm->getStadium(stadiumName)->getSouvenirs())
    {
        ui->souvenirTable->insertRow(row);

        souvenirItem = new QTableWidgetItem(souvenir.name);
        priceItem    = new QTableWidgetItem(QString::number(souvenir.price));
        quantityBox  = new QSpinBox();

        QObject::connect(quantityBox, &QSpinBox::valueChanged,
                         this,        &TourPage::purchaseItem);

        quantityBox->setRange(0, 100);
        quantityBox->setSingleStep(1);
        quantityBox->setPrefix(" ");
        quantityBox->setValue(0);

        ui->souvenirTable->setItem(row, 0, souvenirItem);
        ui->souvenirTable->setItem(row, 1, priceItem);
        ui->souvenirTable->setCellWidget(row, 2, quantityBox);
    }
}

void TourPage::showReceipt()
{
    receipt.displayPurchases();

    receipt.show();
}

void TourPage::purchaseItem(int quantity)
{
    QWidget* widget = qobject_cast<QWidget*>(sender());
    QString stadiumName = ui->locationLabel->text();
    int row = ui->souvenirTable->indexAt(widget->pos()).row();

    QString souvenirName = ui->souvenirTable->item(row, 0)->text();
    float price          = ui->souvenirTable->item(row, 1)->text().toFloat();

    receipt.addPurchase({stadiumName, souvenirName, price, quantity} );
}

