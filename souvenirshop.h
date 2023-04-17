#ifndef SOUVENIRSHOP_H
#define SOUVENIRSHOP_H

#include <QDialog>

namespace Ui {
class SouvenirShop;
}

class SouvenirShop : public QDialog
{
    Q_OBJECT

public:
    explicit SouvenirShop(QWidget *parent = nullptr);
    ~SouvenirShop();

private:
    Ui::SouvenirShop *ui;
};

#endif // SOUVENIRSHOP_H
