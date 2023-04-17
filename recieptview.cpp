#include "recieptview.h"
#include "ui_recieptview.h"

RecieptView::RecieptView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecieptView)
{
    ui->setupUi(this);
}

RecieptView::~RecieptView()
{
    delete ui;
}
