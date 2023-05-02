#include "souvenirshop.h"
#include "ui_souvenirshop.h"

SouvenirShop::SouvenirShop(StadiumManager* sm, QWidget *parent)
    : QDialog(parent), ui(new Ui::SouvenirShop), sm { sm }
{
    ui->setupUi(this);
}

SouvenirShop::~SouvenirShop()
{
    delete ui;
}
