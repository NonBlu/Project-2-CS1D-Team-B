#ifndef DYNAMICTABLE_H
#define DYNAMICTABLE_H

#include <QDialog>
#include <stadiummanager.h>

namespace Ui {
class DynamicTable;
}

class DynamicTable : public QDialog
{
    Q_OBJECT

public:
    explicit DynamicTable(StadiumManager* sm, QWidget *parent = nullptr);
    ~DynamicTable();

private:
    Ui::DynamicTable* ui;
    StadiumManager*   sm;
};

#endif // DYNAMICTABLE_H
