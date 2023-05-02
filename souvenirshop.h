#ifndef SOUVENIRSHOP_H
#define SOUVENIRSHOP_H

#include "receipt.h"
#include "stadiummanager.h"
#include <QDialog>

namespace Ui {
class SouvenirShop;
}

class SouvenirShop : public QDialog
{
    Q_OBJECT

public:
    explicit SouvenirShop(StadiumManager* sm, QWidget *parent = nullptr);
//    SouvenirShop(QWidget* parent, StadiumManager* sm = nullptr);
    ~SouvenirShop();

    void purchaseItem(int quantity);
    void displaySouvenirs();

private:
    Ui::SouvenirShop* ui;
    StadiumManager*   sm;
    Receipt receipt;
};

#endif // SOUVENIRSHOP_H
