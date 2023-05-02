#ifndef DYNAMICTABLE_H
#define DYNAMICTABLE_H

#include <QDialog>

namespace Ui {
class DynamicTable;
}

class DynamicTable : public QDialog
{
    Q_OBJECT

public:
    explicit DynamicTable(QWidget *parent = nullptr);
    ~DynamicTable();

private:
    Ui::DynamicTable *ui;
};

#endif // DYNAMICTABLE_H
