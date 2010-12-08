#ifndef CREATESHIPMENTSWINDOW_H
#define CREATESHIPMENTSWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "DataHandler.h"
#include "SupplyType.h"
#include "Region1.h"
#include "Inventory.h"

namespace Ui {
    class CreateShipmentsWindow;
}

class CreateShipmentsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CreateShipmentsWindow(QWidget *parent = 0);
    ~CreateShipmentsWindow();
public slots:
    void fromManager(int);
private:
    Ui::CreateShipmentsWindow *ui;
    QStringList fetchListOfRegions();
    QStringList fetchListOfSupplies();
    QMessageBox msgBox;
    QList<SupplyType> supplyList;
    QList<Region1> regionList;
    QList<Inventory> inventoryList;
    QStringList regionComboList;
    SupplyType *aSupply;
    SupplyType *bSupply;
    Region1 *aRegion1;
    Region1 *bRegion1;
    bool cameFrom;
private slots:
    void changeText(QString);
    void notifyUser();
    void CreateShipmentsWindowSubmitButtonHandler();
    void CreateShipmentsWindowCancelButtonHandler();
};

#endif // CREATESHIPMENTSWINDOW_H
