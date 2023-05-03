#ifndef CENTERFIELDDIST_H
#define CENTERFIELDDIST_H

#include <QDialog>
#include <stadiummanager.h>

namespace Ui {
class CenterFieldDist;
}

class CenterFieldDist : public QDialog
{
    Q_OBJECT

public:
    explicit CenterFieldDist(QString type, StadiumManager* sm, QWidget *parent = nullptr);
    ~CenterFieldDist();

private:
    Ui::CenterFieldDist *ui;
    StadiumManager*      sm;
};

#endif // CENTERFIELDDIST_H
