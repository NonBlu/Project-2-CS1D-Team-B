#include "tourpage.h"
#include "ui_tourpage.h"
#include "souvenirshop.h"
#include "recieptview.h"

TourPage::TourPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TourPage)
{
    ui->setupUi(this);
}

TourPage::~TourPage()
{
    delete ui;
}

void TourPage::on_souvenirButton_clicked()
{
    SouvenirShop souvPage;
    souvPage.setModal(true);
    souvPage.exec();
}

void TourPage::on_recieptButton_clicked()
{
    RecieptView recieptPage;
    recieptPage.setModal(true);
    recieptPage.exec();
}

