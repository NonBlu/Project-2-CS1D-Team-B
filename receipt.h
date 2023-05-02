#ifndef RECEIPT_H
#define RECEIPT_H

#include <QDialog>
#include <QString>

#include "Containers/Vector.h"

/**
 * @brief The Purchase struct (hold stadium name, souvenir name, price, and quantity)
 */
struct Purchase
{
    QString stadiumName;
    QString souvenirName;
    float   price;
    int     quantity;

    bool operator<(const Purchase& purchase)
        { return stadiumName < purchase.stadiumName; }
};


namespace Ui { class Receipt; }


/**
 * @brief The Receipt class
 */
class Receipt : public QDialog
{
    Q_OBJECT

  public:
    Receipt();

    ~Receipt() {};

    /**
     * @brief Sets up the receipt window
     */
    void setupReceipt();

    /**
     * @brief Displays purchases made by the user
     */
    void displayPurchases();

    /**
     * @brief addPurchase - Adds souvenir that user purchased
     * @param purchase    - Struct that holds all souvenir info
     */
    void addPurchase(const Purchase& purchase);

    /**
     * @brief calculatePurchaseTotal - Calculates total spent for stadiumName
     * @param stadiumName - Total for this stadium
     * @return
     */
    float calculatePurchaseTotal(QString stadiumName);

    /**
     * @brief calculateGrandTotal - Calculates grand total for all souvenirs from all stadiumes
     * @return
     */
    float calculateGrandTotal();

    // TESTING
    void printPurchases();

  private:
    Vector<Purchase> purchases;
};



#endif // RECEIPT_H
