#include "informationview.h"
#include "ui_informationview.h"

InformationView::InformationView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationView)
{
    ui->setupUi(this);
}

InformationView::~InformationView()
{
    delete ui;
}
