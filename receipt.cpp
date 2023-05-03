
#include "receipt.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QLabel>


Receipt::Receipt()
{
    setFixedWidth(600);
    setFixedHeight(400);

    setupReceipt();
}


void Receipt::setupReceipt()
{
    QTableWidget* table = new QTableWidget(this);
    QFont         font  = QFont();

    QLabel* titleLabel      = new QLabel("Purchases", this);
    QLabel* grandTotalLabel = new QLabel(this);

    table->setGeometry(20, 50, 560, 300);

    table->setColumnCount(4);

    table->setColumnWidth(0, 280);
    table->setColumnWidth(1, 120);
    table->setColumnWidth(2, 75);
    table->setColumnWidth(3, 75);

    font.setWeight(QFont::Bold);

    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setFont(font);
    table->setHorizontalHeaderLabels( {"Stadium", "Souvenir", "Price", "Quantity"} );
    table->horizontalHeader()->setStyleSheet("QHeaderView { font-size: 12pt; }"   );

    if (palette().color(QPalette::Window).value() == 236)
    {
        table->setStyleSheet( "QHeaderView::section { background-color: MintCream; }");
    }
    else
    {
        table->setStyleSheet( "QHeaderView::section { background-color: LightSeaGreen; }");
    }

    titleLabel->setGeometry(250, 10, 250, 35);
    titleLabel->setFont(font);
    titleLabel->setStyleSheet("QLabel { font-size: 18pt; color: SlateGrey; }");

    grandTotalLabel->setGeometry(50, 350, 300, 50);
    grandTotalLabel->setFont(font);
    grandTotalLabel->setStyleSheet("QLabel { font-size: 16pt; }");
}

void Receipt::displayPurchases()
{
    QTableWidgetItem* stadiumItem    { };
    QTableWidgetItem* souvenirItem  { };
    QTableWidgetItem* priceItem     { };
    QTableWidgetItem* quantityItem  { };

    QString stadiumName { };

    int   row           { };
    int   count         { };
    float purchaseTotal { };
    float grandTotal    { };

    QFont font = QFont();

    QTableWidget* table = qobject_cast<QTableWidget*>(childAt(20,  50));
    QLabel*       label = qobject_cast<QLabel*>      (childAt(50, 350));

    table->clearContents();
    table->setRowCount(0);

    font.setWeight(QFont::Bold);

    for (auto& purchase : purchases)
    {
        if (!row)
        {
            stadiumItem  = new QTableWidgetItem(purchase.stadiumName);
            souvenirItem = new QTableWidgetItem(purchase.souvenirName);
            priceItem    = new QTableWidgetItem("$ " + QString::number(purchase.price));
            quantityItem = new QTableWidgetItem(QString::number(purchase.quantity));
        }
        else if (stadiumName == purchase.stadiumName)
        {
            stadiumItem  = new QTableWidgetItem(" ");
            souvenirItem = new QTableWidgetItem(purchase.souvenirName);
            priceItem    = new QTableWidgetItem("$ " + QString::number(purchase.price));
            quantityItem = new QTableWidgetItem(QString::number(purchase.quantity));
        }
        else
        {
            purchaseTotal = calculatePurchaseTotal(stadiumName);

            stadiumItem  = new QTableWidgetItem(" ");
            souvenirItem = new QTableWidgetItem(" Total: ");
            priceItem    = new QTableWidgetItem("$ " + QString::number(purchaseTotal));
            quantityItem = new QTableWidgetItem(" ");

            souvenirItem->setFont(font);
            priceItem->setFont(font);
            priceItem->setForeground(Qt::darkRed);

            table->insertRow(row);

            table->setItem(row, 0, stadiumItem  );
            table->setItem(row, 1, souvenirItem);
            table->setItem(row, 2, priceItem   );
            table->setItem(row, 3, quantityItem);

            ++row;

            stadiumItem   = new QTableWidgetItem(" ");
            souvenirItem = new QTableWidgetItem(" ");
            priceItem    = new QTableWidgetItem(" ");
            quantityItem = new QTableWidgetItem(" ");

            table->insertRow(row);

            table->setItem(row, 0, stadiumItem  );
            table->setItem(row, 1, souvenirItem);
            table->setItem(row, 2, priceItem   );
            table->setItem(row, 3, quantityItem);

            ++row;

            stadiumItem   = new QTableWidgetItem(purchase.stadiumName);
            souvenirItem = new QTableWidgetItem(purchase.souvenirName);
            priceItem    = new QTableWidgetItem("$ " + QString::number(purchase.price));
            quantityItem = new QTableWidgetItem(QString::number(purchase.quantity));
        }

        table->insertRow(row);

        table->setItem(row, 0, stadiumItem  );
        table->setItem(row, 1, souvenirItem);
        table->setItem(row, 2, priceItem   );
        table->setItem(row, 3, quantityItem);

        stadiumName = purchase.stadiumName;

        if(table->item(row, 0)->text().isEmpty()) {

        }

        ++row;
        ++count;

        if (count == purchases.size())
        {
            purchaseTotal = calculatePurchaseTotal(stadiumName);

            stadiumItem  = new QTableWidgetItem(" ");
            souvenirItem = new QTableWidgetItem(" Total: ");
            priceItem    = new QTableWidgetItem("$ " + QString::number(purchaseTotal));
            quantityItem = new QTableWidgetItem(" ");

            souvenirItem->setFont(font);
            priceItem->setFont(font);
            priceItem->setForeground(Qt::darkRed);

            table->insertRow(row);

            table->setItem(row, 0, stadiumItem  );
            table->setItem(row, 1, souvenirItem);
            table->setItem(row, 2, priceItem   );
            table->setItem(row, 3, quantityItem);
        }

    }
    for (int i = table->rowCount() - 1; i >= 0; i--)
    {
        QTableWidgetItem* item = table->item(i, 3); // get the quantity item in the row
        if (item && item->text().toInt() <= 0)     // check if quantity is zero or less
        {
            table->removeRow(i);                   // delete the row
        }
    }

//    if(table->item(row, 0)->text().isEmpty()) {
//        table->setItem(row, 0, stadiumItem  );
//    }

    grandTotal = calculateGrandTotal();

    label->setText("Grand Total:  $ " + QString::number(grandTotal));
}

//void Receipt::displayPurchases()
//{
//    QTableWidgetItem* stadiumItem    { };
//    QTableWidgetItem* souvenirItem  { };
//    QTableWidgetItem* priceItem     { };
//    QTableWidgetItem* quantityItem  { };

//    QString stadiumName { };

//    int   row           { };
//    int   count         { };
//    float purchaseTotal { };
//    float grandTotal    { };

//    QFont font = QFont();

//    QTableWidget* table = qobject_cast<QTableWidget*>(childAt(20,  50));
//    QLabel*       label = qobject_cast<QLabel*>      (childAt(50, 350));

//    table->clearContents();
//    table->setRowCount(0);

//    font.setWeight(QFont::Bold);

//    for (auto& purchase : purchases)
//    {
//        if (!row)
//        {
//            stadiumItem   = new QTableWidgetItem(purchase.stadiumName);
//            souvenirItem = new QTableWidgetItem(purchase.souvenirName);
//            priceItem    = new QTableWidgetItem("$ " + QString::number(purchase.price));
//            quantityItem = new QTableWidgetItem(QString::number(purchase.quantity));
//        }
//        else if (stadiumName == purchase.stadiumName)
//        {
//            stadiumItem   = new QTableWidgetItem(" ");
//            souvenirItem = new QTableWidgetItem(purchase.souvenirName);
//            priceItem    = new QTableWidgetItem("$ " + QString::number(purchase.price));
//            quantityItem = new QTableWidgetItem(QString::number(purchase.quantity));
//        }
//        else
//        {
//            purchaseTotal = calculatePurchaseTotal(stadiumName);

//            stadiumItem   = new QTableWidgetItem(" ");
//            souvenirItem = new QTableWidgetItem(" Total: ");
//            priceItem    = new QTableWidgetItem("$ " + QString::number(purchaseTotal));
//            quantityItem = new QTableWidgetItem(" ");

//            souvenirItem->setFont(font);
//            priceItem->setFont(font);
//            priceItem->setForeground(Qt::darkRed);

//            table->insertRow(row);

//            table->setItem(row, 0, stadiumItem  );
//            table->setItem(row, 1, souvenirItem);
//            table->setItem(row, 2, priceItem   );
//            table->setItem(row, 3, quantityItem);

//            ++row;

//            stadiumItem   = new QTableWidgetItem(" ");
//            souvenirItem = new QTableWidgetItem(" ");
//            priceItem    = new QTableWidgetItem(" ");
//            quantityItem = new QTableWidgetItem(" ");

//            table->insertRow(row);

//            table->setItem(row, 0, stadiumItem  );
//            table->setItem(row, 1, souvenirItem);
//            table->setItem(row, 2, priceItem   );
//            table->setItem(row, 3, quantityItem);

//            ++row;

//            stadiumItem   = new QTableWidgetItem(purchase.stadiumName);
//            souvenirItem = new QTableWidgetItem(purchase.souvenirName);
//            priceItem    = new QTableWidgetItem("$ " + QString::number(purchase.price));
//            quantityItem = new QTableWidgetItem(QString::number(purchase.quantity));
//        }

//        table->insertRow(row);

//        table->setItem(row, 0, stadiumItem  );
//        table->setItem(row, 1, souvenirItem);
//        table->setItem(row, 2, priceItem   );
//        table->setItem(row, 3, quantityItem);

//        stadiumName = purchase.stadiumName;

//        ++row;
//        ++count;

//        if (count == purchases.size())
//        {
//            purchaseTotal = calculatePurchaseTotal(stadiumName);

//            stadiumItem   = new QTableWidgetItem(" ");
//            souvenirItem = new QTableWidgetItem(" Total: ");
//            priceItem    = new QTableWidgetItem("$ " + QString::number(purchaseTotal));
//            quantityItem = new QTableWidgetItem(" ");

//            souvenirItem->setFont(font);
//            priceItem->setFont(font);
//            priceItem->setForeground(Qt::darkRed);

//            table->insertRow(row);

//            table->setItem(row, 0, stadiumItem  );
//            table->setItem(row, 1, souvenirItem);
//            table->setItem(row, 2, priceItem   );
//            table->setItem(row, 3, quantityItem);
//        }
//    }

//    grandTotal = calculateGrandTotal();

//    label->setText("Grand Total:  $ " + QString::number(grandTotal));
//}



void Receipt::addPurchase(const Purchase& purchase)
{
    bool alreadyPurchased { false };

    if ( !purchases.size() )
    {
        purchases.pushBack(purchase);
    }
    else
    {
        for (auto& purch : purchases)
        {
            if (    purch.stadiumName   == purchase.stadiumName
                 && purch.souvenirName == purchase.souvenirName )
            {
                purch.quantity = purchase.quantity;

                alreadyPurchased = true;

                break;
            }
        }

        if ( !alreadyPurchased )
        {
            purchases.pushBack(purchase);
        }
    }
}




float Receipt::calculatePurchaseTotal(QString stadiumName)
{
    float total { };

    for (auto& purchase : purchases)
    {
        if (purchase.stadiumName == stadiumName)
        {
            total += purchase.price * purchase.quantity;
        }
    }

    return total;
}



float Receipt::calculateGrandTotal()
{
    float total { };

    for (auto& purchase : purchases)
    {
        total += purchase.price * purchase.quantity;
    }

    return total;
}




void Receipt::printPurchases()
{
    for (auto& purchase : purchases)
    {
        qDebug() << purchase.stadiumName;
        qDebug() << purchase.souvenirName;
        qDebug() << purchase.price;
        qDebug() << purchase.quantity;
    }
}
