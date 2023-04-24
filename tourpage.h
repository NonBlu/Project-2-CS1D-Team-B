#ifndef TOURPAGE_H
#define TOURPAGE_H

#include "receipt.h"
#include "stadiummanager.h"
#include <QDialog>

namespace Ui {
class TourPage;
}

class TourPage : public QDialog
{
    Q_OBJECT

public:
    explicit TourPage(QWidget *parent = nullptr);
    TourPage(QWidget *parent, StadiumManager *sm);
    void displaySouvenirs();
    void purchaseItem(int quantity);
    ~TourPage();

private slots:
//    void on_souvenirButton_clicked();
    void showReceipt();
//    void on_recieptButton_clicked();

private:
    Ui::TourPage *ui;
    StadiumManager* sm;
    Receipt receipt;
};

#endif // TOURPAGE_H
