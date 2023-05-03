#include "adminpage.h"

#include <QVBoxLayout>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QBrush>
#include <QSize>


AdminPage::AdminPage(StadiumManager* sm, QWidget *parent)
    : QDialog(parent), sm { sm },           tabs          { new QTabWidget(this)   },
      MLBTree    { new QTreeWidget(tabs) }, souvenirTable { new QTableWidget(tabs) },
      filterLine { new QLineEdit(this)   }
{
    this->setFixedHeight(800);
    this->setFixedWidth(690);


    filterLine->setGeometry(20, 15, 150, 25);
    filterLine->setPlaceholderText("🔍  Search...");

    QObject::connect(filterLine, &QLineEdit::editingFinished,
                     this,       &AdminPage::filterHandler  );


    tabs->setGeometry(20, 40, 650, 740);

    tabs->addTab(MLBTree,       QIcon(":/Icons/stadium.png"), "Stadiums" );
    tabs->addTab(souvenirTable, QIcon(":/Icons/present.png"), "Souvenirs");

    QObject::connect(tabs, &QTabWidget::currentChanged,
                     this, &AdminPage::clearFilter     );


    if (sm->getStadium("Las Vegas Stadium")->getStadiumName() == "")
    {
        addXbutton = new QPushButton("Add Expansion", this);
        addXbutton->setGeometry(530, 16, 120, 30);

        if (palette().color(QPalette::Window).value() == 236)
        {
            addXbutton->setStyleSheet( "QPushButton { border-radius: 10px; padding:10px;"
                                       "              background-color:    LightBlue;     }");
        }
        else
        {
            addXbutton->setStyleSheet( "QPushButton { border-radius: 10px; padding:10px;"
                                       "              background-color:    SteelBlue;     }");
        }

        QObject::connect(addXbutton, &QPushButton::clicked,
                         this,       &AdminPage::addExpansionData);
    }

    setupMLBTree();
    setupSouvenirTable();

    displayMLBTree();
    displaySouvenirTable();
}



// Need to clear widget elements before deleting!!!
AdminPage::~AdminPage()
{
    delete addXbutton;
    delete filterLine;
//    delete souvenirTable;
//    delete MLBTree;
//    delete tabs;
}


void AdminPage::addExpansionData()
{
//    sm->parseExpansionTables();

//    displayMLBTree();

//    displaySouvenirTable();

//    addXbutton->hide();
}


void AdminPage::filterHandler()
{
    if (!tabs->currentIndex())
    {
        displayMLBTree();
    }
    else
    {
        displaySouvenirTable();
    }
}


void AdminPage::setupMLBTree()
{
    QStringList headers;

    headers << "Attribute" << "Values";

    MLBTree->setColumnCount(2);
    MLBTree->setColumnWidth(0, 300);
    MLBTree->setColumnWidth(1, 300);
    MLBTree->setHeaderLabels(headers);

    MLBTree->header()->setDefaultAlignment(Qt::AlignCenter);
    MLBTree->header()->setFixedHeight(25);

    MLBTree->setSelectionMode(QAbstractItemView::NoSelection);

    if (palette().color(QPalette::Window).value() == 236)
    {
        MLBTree->setStyleSheet( "QHeaderView { background-color: MintCream;"
                                "              font-size:        12pt;"
                                "              font-weight:      bold;       }"   );
    }
    else
    {
        MLBTree->setStyleSheet( "QHeaderView { background-color: LightSeaGreen;"
                                "              font-size:        12pt;"
                                "              font-weight:      bold;          }");
    }
}


void AdminPage::displayMLBTree()
{
    QTreeWidgetItem* rootItem;
    QTreeWidgetItem* item;
    QComboBox*       box;
    QSpinBox*        spinBox;
    QBrush           brush;
    QString          stadium;
    int              count    { };
    QString filter = filterLine->text();

    MLBTree->disconnect();
    MLBTree->clear();

    if (palette().color(QPalette::Window).value() == 236)
    {
        brush.setColor(Qt::lightGray);
        brush.setStyle(Qt::Dense7Pattern);
    }
    else
    {
        brush.setColor(Qt::darkGray);
        brush.setStyle(Qt::Dense2Pattern);
    }

    for (auto& mlb : sm->map)
    {
        stadium = mlb.getStadiumName();

        if (    filter == ""
             || stadium.contains(filter, Qt::CaseInsensitive) )
        {
            rootItem = new QTreeWidgetItem(MLBTree);
            rootItem->setText(0, stadium);
            rootItem->setFlags(rootItem->flags() | Qt::ItemIsEditable);
            MLBTree->addTopLevelItem(rootItem);

            item = new QTreeWidgetItem();
            item->setText(0, "Team Name");
            item->setText(1, mlb.getTeamName());
            item->setSizeHint(0, QSize(150, 28));
            item->setFlags(item->flags() | Qt::ItemIsEditable);
            rootItem->addChild(item);

            item = new QTreeWidgetItem();
            item->setText(0, "Location");
            item->setText(1, mlb.getLocation());
            item->setSizeHint(0, QSize(150, 28));
            item->setBackground(0, brush);
            item->setFlags(item->flags() | Qt::ItemIsEditable);
            rootItem->addChild(item);

            item = new QTreeWidgetItem();
            item->setText(0, "Seating Capcity");
            rootItem->addChild(item);
            spinBox = createSpinBox("Seating", mlb.getSeatingCapacity());
            MLBTree->setItemWidget(item, 1, spinBox);

            item = new QTreeWidgetItem();
            item->setText(0, "Date Opened");
            item->setBackground(0, brush);
            rootItem->addChild(item);
            spinBox = createSpinBox("Date", mlb.getDateOpened());
            MLBTree->setItemWidget(item, 1, spinBox);

            item = new QTreeWidgetItem();
            item->setText(0, "Feet to center field");
            rootItem->addChild(item);
            spinBox = createSpinBox("Feet", mlb.getFeetToCenter());
            MLBTree->setItemWidget(item, 1, spinBox);

            item = new QTreeWidgetItem();
            item->setText(0, "Meters to center field");
            item->setBackground(0, brush);
            rootItem->addChild(item);
            spinBox = createSpinBox("Meters", mlb.getMetersToCenter());
            MLBTree->setItemWidget(item, 1, spinBox);

            item = new QTreeWidgetItem();
            item->setText(0, "League");
            rootItem->addChild(item);
            box = createComboBox("League", mlb);
            MLBTree->setItemWidget(item, 1, box);

            item = new QTreeWidgetItem();
            item->setText(0, "Playing Surface");
            item->setBackground(0, brush);
            rootItem->addChild(item);
            box = createComboBox("Playing Surface", mlb);
            MLBTree->setItemWidget(item, 1, box);

            item = new QTreeWidgetItem();
            item->setText(0, "Ballpark Typology");
            rootItem->addChild(item);
            box = createComboBox("Typology", mlb);
            MLBTree->setItemWidget(item, 1, box);

            item = new QTreeWidgetItem();
            item->setText(0, "Roof Type");
            item->setBackground(0, brush);
            rootItem->addChild(item);
            box = createComboBox("Roof", mlb);
            MLBTree->setItemWidget(item, 1, box);

            ++count;
        }
    }

    if (count == 1)
    {
        MLBTree->expandItem(MLBTree->topLevelItem(0));
    }

    QObject::connect(MLBTree, &QTreeWidget::itemChanged,
                    this,     &AdminPage::updateMLBInfo);
}


void AdminPage::setupSouvenirTable()
{
    QFont font { QFont() };

    font.setWeight(QFont::Bold);

    souvenirTable->setFixedHeight(750);
    souvenirTable->setFixedWidth(648);

    souvenirTable->verticalHeader()->setVisible(false);
    souvenirTable->setSelectionMode(QAbstractItemView::NoSelection);
    souvenirTable->horizontalHeader()->setFont(font);

    souvenirTable->setColumnCount(4);
    souvenirTable->setColumnWidth(0, 250);
    souvenirTable->setColumnWidth(1, 200);
    souvenirTable->setColumnWidth(2, 105);
    souvenirTable->setColumnWidth(3, 75);

    souvenirTable->setHorizontalHeaderLabels({"Stadium", "Souvenir", "Price", ""});

    if (palette().color(QPalette::Window).value() == 236)
    {
        souvenirTable->setStyleSheet( "QHeaderView::section { background-color: MintCream;"
                                      "                       font-size:        12pt;          }");
    }
    else
    {
        souvenirTable->setStyleSheet( "QHeaderView::section { background-color: LightSeaGreen; "
                                      "                       font-size:        12pt;           }");
    }
}


void AdminPage::displaySouvenirTable()
{
    QTableWidgetItem* souvenirItem;
    QHBoxLayout*      horLayout;
    QPushButton*      addBtn;
    QWidget*          widget;
    QLabel*           stadiumLabel;

    QString filter = filterLine->text();

    int row {};

    souvenirTable->disconnect();
    souvenirTable->model()->removeRows(0, souvenirTable->rowCount());

    for (auto& stadium : sm->getStadiums())
    {
        if (    filter == ""
             || stadium.stadiumName.contains(filter) )
        {
            stadiumLabel = new QLabel(stadium.stadiumName);
            addBtn       = new QPushButton(QIcon(":/Icons/add.png"), "", souvenirTable);
            widget       = new QWidget();
            horLayout    = new QHBoxLayout(widget);

            addBtn->setFixedWidth(30);
            addBtn->setStyleSheet("border: none;");

            QObject::connect(addBtn, &QPushButton::clicked,
                             this,   &AdminPage::addSouvenirRow);

            horLayout->addWidget(stadiumLabel);
            horLayout->addWidget(addBtn);
            horLayout->setContentsMargins(0,0,0,0);

            souvenirTable->insertRow(row);

            souvenirTable->setCellWidget(row, 0, widget);

            for (int col { 1 }; col < 4; ++col)
            {
                souvenirTable->setItem(row, col, createBlankCell());
            }

            ++row;

            for (auto& souvenir : stadium.souvenirs)
            {
                souvenirItem = createSouvenirItem(souvenir.name);

                souvenirTable->insertRow(row);

                souvenirTable->setItem(      row, 0, createBlankCell());
                souvenirTable->setItem(      row, 1, souvenirItem);
                souvenirTable->setCellWidget(row, 2, createPriceCell(souvenir.price));
                souvenirTable->setCellWidget(row, 3, createDeleteButton());

                ++row;
            }
        }
    }

    QObject::connect(souvenirTable, &QTableWidget::itemChanged,
                     this,          &AdminPage::modSouvenir    );
}



QSpinBox* AdminPage::createSpinBox(const QString& attribute, int value)
{
    QSpinBox* box { new QSpinBox() };

    box->setRange(1, 99999);
    box->setSingleStep(1);

    box->setAlignment(Qt::AlignRight);

    box->setValue(value);


    box->setStyleSheet("QSpinBox { padding-right: 10px; padding-left: 7px; height: 28px; }");

    if (attribute == "Seating")
    {
        QObject::connect(box,  &QSpinBox::valueChanged,
                         this, &AdminPage::updateSeating);
    }
    else if (attribute == "Date")
    {
        QObject::connect(box,  &QSpinBox::valueChanged,
                         this, &AdminPage::updateDate);
    }
    else if (attribute == "Feet")
    {
        QObject::connect(box,  &QSpinBox::valueChanged,
                         this, &AdminPage::updateFeetToCenter);
    }
    else if (attribute == "Meters")
    {
        QObject::connect(box,  &QSpinBox::valueChanged,
                         this, &AdminPage::updateMetersToCenter);
    }

    return box;
}


QComboBox* AdminPage::createComboBox(const QString& attribute, const MLB& mlb)
{
    QStringList values;
    QComboBox*  box = new QComboBox();

    if (attribute == "Playing Surface")
    {
        switch (mlb.surface)
        {
            case Surface::Grass  : values << "Grass"
                                          << "AstroTurf GameDay Grass"
                                          << "AstroTurf GameDay Grass 3D";
                                   break;

            case Surface::Turf   : values << "AstroTurf GameDay Grass"
                                          << "AstroTurf GameDay Grass 3D"
                                          << "Grass";
                                   break;

            case Surface::Turf3D : values << "AstroTurf GameDay Grass 3D"
                                          << "AstroTurf GameDay Grass"
                                          << "Grass";
        }

        box->addItems(values);

        QObject::connect(box,  &QComboBox::currentTextChanged,
                         this, &AdminPage::updateSurface      );
    }
    else if (attribute == "League")
    {
        switch (mlb.league)
        {
            case League::American : values << "American"
                                           << "National";
                                    break;

            case League::National : values << "National"
                                           << "American";
        }

        box->addItems(values);

        QObject::connect(box,  &QComboBox::currentTextChanged,
                         this, &AdminPage::updateLeague      );
    }
    else if (attribute == "Typology")
    {
        values << "Modern"
               << "Jewel Box"
               << "Contemporary"
               << "Multipurpose"
               << "Retro Modern"
               << "Retro Classic";

        switch (mlb.typology)
        {
            case Typology::JewelBox :     values.remove(1);
                                          values.push_front("Jewel Box");
                                          break;

            case Typology::Contemporary : values.remove(2);
                                          values.push_front("Contemporary");
                                          break;

            case Typology::Multipurpose : values.remove(3);
                                          values.push_front("Multipurpose");
                                          break;

            case Typology::RetroModern  : values.remove(4);
                                          values.push_front("Retro Modern");
                                          break;

            case Typology::RetroClassic : values.remove(5);
                                          values.push_front("Retro Classic");
                                          break;

                                default : break;
        }

        box->addItems(values);

        QObject::connect(box,  &QComboBox::currentTextChanged,
                         this, &AdminPage::updateTypology     );
    }
    else if (attribute == "Roof")
    {
        switch (mlb.roofType)
        {
            case RoofType::Open        : values << "Open"
                                                << "Fixed"
                                                << "Retractable";
                                         break;

            case RoofType::Fixed       : values << "Fixed"
                                                << "Open"
                                                << "Retractable";
                                         break;

            case RoofType::Retractable : values << "Retractable"
                                                << "Fixed"
                                                << "Open";
        }

        box->addItems(values);

        QObject::connect(box,  &QComboBox::currentTextChanged,
                         this, &AdminPage::updateRoof         );
    }

    return box;
}



void AdminPage::addSouvenirRow()
{
    QWidget* widget = qobject_cast<QWidget*>(sender()->parent());
    int      row    = souvenirTable->indexAt(widget->pos()).row();

    if (     row == souvenirTable->rowCount() - 1
         ||  souvenirTable->item(row + 1, 1)->text() != ""
         || !souvenirTable->item(row + 1, 0)               )
    {

        ++row;

        souvenirTable->insertRow(row);

        souvenirTable->setItem(      row, 0, createBlankCell());
        souvenirTable->setItem(      row, 1, createSouvenirItem(""));
        souvenirTable->setCellWidget(row, 2, createPriceCell(0.0));
        souvenirTable->setCellWidget(row, 3, createDeleteButton());
    }


}



QTableWidgetItem* AdminPage::createSouvenirItem(QString name)
{
    QTableWidgetItem* widget = new QTableWidgetItem(name);

    widget->setTextAlignment(Qt::AlignCenter);

    return widget;
}


QTableWidgetItem* AdminPage::createBlankCell()
{
    QTableWidgetItem* item = new QTableWidgetItem();

    item->setFlags(item->flags() & ~Qt::ItemIsEditable);

    item->setBackground(QBrush(Qt::lightGray, Qt::Dense7Pattern));

    return item;
}


QDoubleSpinBox*AdminPage::createPriceCell(float price)
{
    QDoubleSpinBox* box = new QDoubleSpinBox();

    QString prefix = "$ ";

    if      (price <  10) prefix += "  ";
    else if (price < 100) prefix += " ";

    box->setRange(0.0, 999.99);
    box->setSingleStep(0.01);

    box->setPrefix(prefix);
    box->setValue(price);

    QObject::connect(box,  &QDoubleSpinBox::editingFinished,
                     this, &AdminPage::updateSouvenirPrice);

    return box;
}


QPushButton* AdminPage::createDeleteButton()
{
    QPushButton* btn = new QPushButton(QIcon(":/Icons/delete.png"), "", souvenirTable);

    btn->setStyleSheet("border: none;");

    QObject::connect(btn, &QPushButton::clicked,
                    this, &AdminPage::deleteSouvenir);

    return btn;
}



// add new or update current souvenir
void AdminPage::modSouvenir(QTableWidgetItem* item)
{
    MLB*     stadium;
    float    price;
    int      row;
    QString  souvenir = item->text();

    if (souvenir != "")
    {
        row     = souvenirTable->row(item);
        stadium = getMLB(row);
        price   = getPrice(row);

        if (!price)
        {
            stadium->addSouvenir(souvenir, 0);

            sm->addSouvenirToDB(stadium->stadiumName, souvenir, price);
        }
        else
        {
            for (auto& svnr : stadium->souvenirs)
            {
                if (svnr.price == price)
                {
                    sm->modSouvenirNameInDB(stadium->stadiumName, svnr.name, souvenir);

                    stadium->modifySouvenirName(svnr.name, souvenir);

                    break;
                }
            }
        }
    }
}


void AdminPage::updateSouvenirPrice()
{
    QWidget* widget    = qobject_cast<QWidget*>(sender());
    int      row       = souvenirTable->indexAt(widget->pos()).row();
    QString  souvenir  = souvenirTable->item(row, 1)->text();
    MLB*     stadium   = getMLB(row);
    float    price     = getPrice(row);

    stadium->modifySouvenirPrice(souvenir, price);

    sm->modSouvenirPriceInDB(stadium->stadiumName, souvenir, price);
}


void AdminPage::deleteSouvenir()
{
    QWidget* widget   = qobject_cast<QWidget*>(sender());
    int      row      = souvenirTable->indexAt(widget->pos()).row();
    QString  souvenir = souvenirTable->item(row, 1)->text();
    MLB*     stadium  = getMLB(row);

    souvenirTable->removeRow(row);

    stadium->removeSouvenir(souvenir);
    sm->deleteSouvenirFromDB(stadium->stadiumName, souvenir);
}


void AdminPage::updateMLBInfo(QTreeWidgetItem* item, int column)
{
    MLB* mlb { nullptr };

    if (!item->parent())
    {
        QString oldName;

        mlb     = sm->getTeam(item->child(0)->text(1));
        oldName = mlb->getStadiumName();
        mlb->setStadiumName(item->text(0));

        sm->graph.updateVertexValue(oldName, item->text(0));

        sm->map.erase(oldName);
        sm->map.put( { item->text(0), *mlb } );

        sm->updateStadiumNameInDB(oldName, item->text(0));
    }
    else if (column)
    {
        QString stadium  = item->parent()->text(0);
        QString newValue = item->text(1);
        int     index    = item->parent()->indexOfChild(item);

        mlb = sm->getStadium(stadium);

        switch (index)
        {
            case 0 : mlb->setTeamName(newValue);
                     sm->updateTeamNameInDB(stadium, newValue);
                     break;

            case 1 : mlb->setLocation(newValue);
                     sm->updateLocationInDB(stadium, newValue);
        }
    }
}


// Add better error handling
void AdminPage::updateSeating(int capacity)
{
    QWidget* widget  { qobject_cast<QWidget*>(sender())                  };
    QString  stadium { MLBTree->itemAt(widget->pos())->parent()->text(0) };
    MLB*     mlb     { sm->getStadium(stadium)                           };

    mlb->setSeatingCapacity(capacity);
    sm->updateSeatingInDB(stadium, capacity);
}


void AdminPage::updateDate(int date)
{
    QWidget* widget  { qobject_cast<QWidget*>(sender())                  };
    QString  stadium { MLBTree->itemAt(widget->pos())->parent()->text(0) };
    MLB*     mlb     { sm->getStadium(stadium)                           };

    mlb->setDateOpened(date);
    sm->updateDateInDB(stadium, date);
}


void AdminPage::updateFeetToCenter(int feet)
{
    QWidget* widget  { qobject_cast<QWidget*>(sender())                  };
    QString  stadium { MLBTree->itemAt(widget->pos())->parent()->text(0) };
    MLB*     mlb     { sm->getStadium(stadium)                           };

    mlb->setDistanceToCenterFT(feet);
    sm->updateFeetToCenterInDB(stadium, feet);
}


void AdminPage::updateMetersToCenter(int meters)
{
    QWidget* widget  { qobject_cast<QWidget*>(sender())                  };
    QString  stadium { MLBTree->itemAt(widget->pos())->parent()->text(0) };
    MLB*     mlb     { sm->getStadium(stadium)                           };

    mlb->setDistanceToCenterM(meters);
    sm->updateMetersToCenterInDB(stadium, meters);
}


void AdminPage::updateLeague(const QString& league)
{
    QWidget* widget  { qobject_cast<QWidget*>(sender())                  };
    QString  stadium { MLBTree->itemAt(widget->pos())->parent()->text(0) };
    MLB*     mlb     { sm->getStadium(stadium)                           };

    mlb->setLeague(league);
    sm->updateLeagueInDB(stadium, league);
}


void AdminPage::updateSurface(const QString& surface)
{
    QWidget* widget { qobject_cast<QWidget*>(sender())                  };
    QString stadium { MLBTree->itemAt(widget->pos())->parent()->text(0) };
    MLB*    mlb     { sm->getStadium(stadium)                           };

    qDebug() << surface;

    mlb->setSurface(surface);
    sm->updateSurfaceInDB(stadium, surface);
}


void AdminPage::updateTypology(const QString& typology)
{
    QWidget* widget  { qobject_cast<QWidget*>(sender())                  };
    QString  stadium { MLBTree->itemAt(widget->pos())->parent()->text(0) };
    MLB*     mlb     { sm->getStadium(stadium)                           };

    mlb->setTypology(typology);
    sm->updateTypologyInDB(stadium, typology);
}


void AdminPage::updateRoof(const QString& roof)
{
    QWidget* widget  { qobject_cast<QWidget*>(sender())                  };
    QString  stadium { MLBTree->itemAt(widget->pos())->parent()->text(0) };
    MLB*     mlb     { sm->getStadium(stadium)                           };

    mlb->setRoofType(roof);
    sm->updateRoofTypeInDB(stadium, roof);
}



void AdminPage::clearFilter()
{
    if (filterLine->text() != "")
    {
        filterLine->clear();

        if (tabs->currentIndex())
        {
            displayMLBTree();
        }
        else
        {
            displaySouvenirTable();
        }
    }
}


MLB* AdminPage::getMLB(int row)
{
    QWidget*          widget;
    QTableWidgetItem* item;

    do
    {
        --row;

        item = souvenirTable->item(row, 0);

    } while (item);

    widget = souvenirTable->cellWidget(row, 0);

    return sm->getStadium(qobject_cast<QLabel*>(widget->children()[1])->text());
}


float AdminPage::getPrice(int row)
{
    QWidget* widget { souvenirTable->cellWidget(row, 2) };

    return qobject_cast<QDoubleSpinBox*>(widget)->value();
}
