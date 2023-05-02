#include "souvenirshop.h"
#include "ui_souvenirshop.h"

SouvenirShop::SouvenirShop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SouvenirShop)
{
    ui->setupUi(this);
}

SouvenirShop::~SouvenirShop()
{
    delete ui;
}
