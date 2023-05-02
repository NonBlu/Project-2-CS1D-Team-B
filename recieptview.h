#ifndef RECIEPTVIEW_H
#define RECIEPTVIEW_H

#include <QDialog>

namespace Ui {
class RecieptView;
}

class RecieptView : public QDialog
{
    Q_OBJECT

public:
    explicit RecieptView(QWidget *parent = nullptr);
    ~RecieptView();

private:
    Ui::RecieptView *ui;
};

#endif // RECIEPTVIEW_H
