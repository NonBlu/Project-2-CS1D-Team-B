#pragma once

#include "stadiummanager.h"

#include <QDialog>
#include <QTabWidget>
#include <QTreeWidget>
#include <QTableWidget>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>


namespace Ui { class AdminPage; }

class AdminPage : public QDialog
{
    Q_OBJECT

   public:
    explicit AdminPage(StadiumManager* sm, QWidget *parent = nullptr);

    ~AdminPage();

  protected:
    void  setupMLBTree();
    void  displayMLBTree();
    void  setupSouvenirTable();
    void  displaySouvenirTable();
    MLB*  getMLB(int row);
    float getPrice(int row);

  private slots:
    void addExpansionData();

    void addSouvenirRow();
    void modSouvenir(QTableWidgetItem* item);
    void updateSouvenirPrice();
    void deleteSouvenir();

    void updateLeague(const QString& league);
    void updateSurface(const QString& surface);
    void updateTypology(const QString& typology);
    void updateRoof(const QString& roof);
    void updateSeating(int capacity);
    void updateDate(int date);
    void updateFeetToCenter(int feet);
    void updateMetersToCenter(int meters);
    void updateMLBInfo(QTreeWidgetItem* item, int column);

    void filterHandler();
    void clearFilter();

  private:
    QTableWidgetItem* createBlankCell();
    QDoubleSpinBox*   createPriceCell(float price);
    QPushButton*      createDeleteButton();
    QTableWidgetItem* createSouvenirItem(QString name);
    QComboBox*        createComboBox(const QString& attribute, const MLB& mlb);
    QSpinBox*         createSpinBox(const QString&  attribute, int value);

    StadiumManager* sm;
    QTabWidget*     tabs;
    QTreeWidget*    MLBTree;
    QTableWidget*   souvenirTable;
    QLineEdit*      filterLine;
    QPushButton*    addXbutton;
};


