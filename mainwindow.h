#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stadiummanager.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_adminButton_clicked();

    void on_viewInfoButton_clicked();

    void on_beginButton_clicked();

private:
    Ui::MainWindow *ui;
    StadiumManager* sm;
};
#endif // MAINWINDOW_H
