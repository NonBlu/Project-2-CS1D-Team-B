#ifndef DYNAMICTABLE_H
#define DYNAMICTABLE_H

#include <QDialog>
#include <stadiummanager.h>
#include <centerfielddist.h>

namespace Ui {
class DynamicTable;
}

class DynamicTable : public QDialog
{
    Q_OBJECT

public:
    explicit DynamicTable(StadiumManager* sm, QWidget *parent = nullptr);
    ~DynamicTable();

private slots:

    void on_filterDropdown_currentTextChanged(const QString &arg1);

    void on_sortDropdown_currentTextChanged(const QString &arg1);

    void on_greatestDistButton_clicked();

    void on_smallestDistButton_clicked();

private:
    Ui::DynamicTable* ui;
    StadiumManager*   sm;
};

#endif // DYNAMICTABLE_H
