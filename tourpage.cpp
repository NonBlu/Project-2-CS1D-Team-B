#include "tourpage.h"
#include "qspinbox.h"
#include "./ui_tourpage.h"
#include "receipt.h"
//#include "ui_souvenirshop.h"
#include <QDebug>
#include <QString>
#include <QMessageBox>

TourPage::TourPage(QString tripType, std::vector<QString>& stadiums, StadiumManager* sm, QWidget *parent)
    : QDialog(parent), ui(new Ui::TourPage), sm { sm }, tripType(tripType), customTrip(stadiums), currentTrip(stadiums)

{
    ui->setupUi(this);

    int tempo = stadiums.size();

    for(int i = 0; i < tempo; i++)
    {
        currentTrip.pop_back();
    }

//    for(int i = 0; i < tempo; i++)
//    {
//        qDebug() << customTrip[i];
//    }

    //Souv table set up
    receipt.setModal(true);
    QObject::connect(ui->recieptButton, &QPushButton::clicked,
                     this,              &TourPage::showReceipt);
    ui->souvenirTable->insertColumn(0);
    ui->souvenirTable->insertColumn(1);
    ui->souvenirTable->insertColumn(2);

    ui->souvenirTable->setColumnWidth(0, 150);

    ui->souvenirTable->setHorizontalHeaderLabels( {"Souvenirs", "Price", "Quantity"} );

    ui->souvenirTable->horizontalHeader()->setStretchLastSection(true);
//--------------------------------------------------------------

    ui->tripTypeLabel->setText(tripType);
    ui->orderLabel->setVisible(false);
    Trip<MLB*> trip;

    if (tripType == "Minimum Spanning Tree")
       {
           ui->nextButton->setVisible(false);
           //ui->orderLabel->setVisible(true);
           ui->locationLabel->setVisible(false);
           ui->recieptButton->setVisible(false);
           ui->souvenirTable->setVisible(false);
           ui->orderLabel->setVisible(true);

           MinTree tree  = sm->MST("Marlins Park");
           QString temp1 = ui->dfsTourLabel->text();
           QString temp2 = ui->dfsTourLabel_2->text();
           int counter = 0;
           for (auto& edge : tree.edges)
           {
              counter++;
              if (counter < 16)
              {
              temp1.append("\n");
              temp1.append(QString::number(counter));
              temp1.append(" ");
              temp1.append(edge.orig);
              temp1.append(" -> ");
              temp1.append(edge.dest);
              }
              else
              {
                  temp2.append("\n");
                  temp2.append(QString::number(counter));
                  temp2.append(" ");
                  temp2.append(edge.orig);
                  temp2.append(" -> ");
                  temp2.append(edge.dest);
              }
           }
           ui->dfsTourLabel->setText(temp1);
           ui->dfsTourLabel_2->setText(temp2);

           QString temp = ui->totalDistanceLabel->text();
           temp.append(" ");
           temp.append(QString::number(tree.totalDistance));
           temp.append(" miles");
           ui->totalDistanceLabel->setText(temp);
       }
       else if (tripType == "Depth First Search")
       {
        ui->nextButton->setVisible(false);
        ui->locationLabel->setVisible(false);
        ui->recieptButton->setVisible(false);
        ui->souvenirTable->setVisible(false);
        ui->orderLabel->setVisible(true);
        trip = sm->DFS("Oracle Park");
        QString temp1 = ui->dfsTourLabel->text();
        QString temp2 = ui->dfsTourLabel_2->text();
        int counter = 0;
        for (auto& stadium : trip.path)
        {
            counter++;
            if (counter < 16)
            {
            temp1.append("\n");
            temp1.append(QString::number(counter));
            temp1.append(" ");
            temp1.append(stadium->getStadiumName());
            }
            else
            {
            temp2.append("\n");
            temp2.append(QString::number(counter));
            temp2.append(" ");
            temp2.append(stadium->getStadiumName());
            }
        }
        ui->dfsTourLabel->setText(temp1);
        ui->dfsTourLabel_2->setText(temp2);

        QString temp = ui->totalDistanceLabel->text();
        temp.append(" ");
        temp.append(QString::number(trip.distanceTraveled));
        temp.append(" miles");
        ui->totalDistanceLabel->setText(temp);
        }
        else if (tripType == "Breadth First Search")
        {
        ui->nextButton->setVisible(false);
        ui->locationLabel->setVisible(false);
        ui->recieptButton->setVisible(false);
        ui->souvenirTable->setVisible(false);
        ui->orderLabel->setVisible(true);

        trip = sm->BFS("Target Field");
        QString temp1 = ui->dfsTourLabel->text();
        QString temp2 = ui->dfsTourLabel_2->text();
        int counter = 0;
        for (auto& stadium : trip.path)
        {
            counter++;
            if (counter < 16)
            {
                temp1.append("\n");
                temp1.append(QString::number(counter));
                temp1.append(" ");
                temp1.append(stadium->getStadiumName());
            }
            else
            {
                temp2.append("\n");
                temp2.append(QString::number(counter));
                temp2.append(" ");
                temp2.append(stadium->getStadiumName());
            }
        }
        ui->dfsTourLabel->setText(temp1);
        ui->dfsTourLabel_2->setText(temp2);
        QString temp = ui->totalDistanceLabel->text();
        temp.append(" ");
        temp.append(QString::number(trip.distanceTraveled));
        temp.append(" miles");
        ui->totalDistanceLabel->setText(temp);
    }
    else if (tripType == "Specified Order Tour")
    {
        vector<QString> temp;
        for (int i=0; i < tempo; i++)
        {
            temp.push_back(customTrip[i]);
        }
        trip = sm->customOrderTrip(temp);
        for (auto& stadium : trip.path)
        {
            currentTrip.push_back(stadium->getStadiumName());
        }
        nextStadium();
    }
    else if (tripType == "Most Efficient Tour")
    {
        vector<QString> temp;

        for (int i=0; i < tempo; i++)
        {
            temp.push_back(customTrip[i]);
        }

        trip = sm->customTrip(temp);

        for (auto& stadium : trip.path)
        {
            currentTrip.push_back(stadium->getStadiumName());
        }
        nextStadium();
    }

}

TourPage::~TourPage()
{
    delete ui;
}

void TourPage::nextStadium()
{
    if (currentTrip.empty())
    {
        ui->nextButton->setVisible(false);
        QMessageBox::information(this, "Congratulations!", "You have finished your tour. Feel free to peruse your reciept and exit the tour.");
        return;
    }

    ui->locationLabel->setText(currentTrip[0]);
    displaySouvenirs();
    currentTrip.erase(currentTrip.begin());
}

void TourPage::displaySouvenirs()
{
    QTableWidgetItem* souvenirItem;
    QTableWidgetItem* priceItem;
    QSpinBox* quantityBox;

    QString stadiumName = customTrip[0];

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


void TourPage::on_nextButton_clicked()
{
    if (currentTrip.empty())
    {
        ui->nextButton->setVisible(false);
        QMessageBox::information(this, "Congratulations!", "You have finished your tour. Feel free to peruse your reciept and exit the tour.");
        return;
    }

    ui->locationLabel->setText(currentTrip[0]);
    displaySouvenirs();
    currentTrip.erase(currentTrip.begin());
}

