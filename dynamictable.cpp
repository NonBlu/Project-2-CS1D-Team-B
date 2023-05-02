#include "dynamictable.h"
#include "ui_dynamictable.h"

DynamicTable::DynamicTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DynamicTable)
{
    ui->setupUi(this);
}

DynamicTable::~DynamicTable()
{
    delete ui;
}
