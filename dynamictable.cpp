#include "dynamictable.h"
#include "ui_dynamictable.h"

DynamicTable::DynamicTable(StadiumManager* sm, QWidget *parent) :
    QDialog(parent), ui(new Ui::DynamicTable), sm { sm }
{
    ui->setupUi(this);
}

DynamicTable::~DynamicTable()
{
    delete ui;
}
