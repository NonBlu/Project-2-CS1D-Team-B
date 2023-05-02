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
    explicit TourPage(QString tripType, std::vector<QString>& stadiums, QWidget *parent = nullptr);
    void displaySouvenirs();
    void purchaseItem(int quantity);
    void nextStadium();
    ~TourPage();

private slots:
//    void on_souvenirButton_clicked();
    void showReceipt();
//    void on_recieptButton_clicked();

    void on_nextButton_clicked();

private:
    Ui::TourPage *ui;
    StadiumManager sm;
    Receipt receipt;
    QString tripType;
    vector<QString>& customTrip;
    vector<QString>& currentTrip;
};

#endif // TOURPAGE_H
