#ifndef ADDSUPPLIESWINDOW_H
#define ADDSUPPLIESWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "DataHandler.h"
#include "SupplyType.h"
#include "Region1.h"

namespace Ui {
    class AddSuppliesWindow;
}

class AddSuppliesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddSuppliesWindow(QWidget *parent = 0);
    ~AddSuppliesWindow();

private:
    Ui::AddSuppliesWindow *ui;
    QStringList fetchListOfSupplies();
    QStringList fetchListOfRegions();
    QList<SupplyType> supplyList;
    QList<Region1> regionList;
    QMessageBox msgBox;
    SupplyType *aSupply;
    SupplyType *bSupply;
    Region1 *aRegion1;
    Region1 *bRegion1;

private slots:
    void addSuppliesSubmitButtonHandler();
    void addSuppliesCancelButtonHandler();

signals:
    void suppliesAdded();
};

#endif // ADDSUPPLIESWINDOW_H
