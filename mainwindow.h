#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stadiummanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    vector<QString> obtainDefaultList();
public slots:
    //void on_allButton_clicked();

private slots:
    void on_adminButton_clicked();

    void on_viewInfoButton_clicked();

    void on_choiceButton_clicked();

    void on_mstButton_clicked();

    void on_dfsButton_clicked();

    void on_bfsButton_clicked();

    void on_dynamicTableButton_clicked();

signals:
    void tripTypeChanged(QString value);
private:
    Ui::MainWindow *ui;
    StadiumManager sm;
    //std::vector<QString>& stadiumList;
};
#endif // MAINWINDOW_H
