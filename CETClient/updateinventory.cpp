#include "updateinventory.h"
#include "ui_updateinventory.h"
#include "viewthesupplieswindow.h"

updateinventory::updateinventory(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::updateinventory)
{
    ui->setupUi(this);
}

void updateinventory::updateInventory(int id) {
    inventoryId = id;

    QString regionName;
    QString supplyType;
    int quantity;

    dh = new DataHandler();
    if (dh->isConnected()) {
        QList<Inventory> inventoryList = dh->getInventory();
        QList<Region1> regionList = dh->getRegions();
        QList<SupplyType> supplyList = dh->getSupplyTypes();

        for (int i = 0; i < inventoryList.size(); i++) {
            if (inventoryList[i].getId() == id) {
                for (int j = 0; j < regionList.size(); j++) {
                    if (inventoryList[i].getRegionId() == regionList[j].getId()) {
                        regionName = regionList[j].getName();
                    }
                }
                for (int k = 0; k < supplyList.size(); k++) {
                    if (inventoryList[i].getSupplyType() == supplyList[k].getId()) {
                        supplyType = supplyList[k].getName();
                    }
                }
                quantity = inventoryList[i].getQuantity();

            }
        }

        ui->label_2->setText(supplyType);
        ui->label_7->setText(regionName);
        ui->spinBox->setValue(quantity);
    }
}

void updateinventory::UpdateInventorySubmitButtonHandler() {
    dh->updateInventory(inventoryId, ui->spinBox->value());
    //qDebug() << inventoryId;

    //Use a confirmation popup dialog
    msgBox.setText("Inventory has been updated.");
    msgBox.exec();

    ViewTheSuppliesWindow *viewTheSuppliesWindow = new ViewTheSuppliesWindow;
    viewTheSuppliesWindow->show();
    viewTheSuppliesWindow->setModal(true);

    emit suppliesUpdated();
    updateinventory::close();
}

void updateinventory::UpdateInventoryCancelButtonHandler() {
    ViewTheSuppliesWindow *viewTheSuppliesWindow = new ViewTheSuppliesWindow;
    viewTheSuppliesWindow->show();
    viewTheSuppliesWindow->setModal(true);

    updateinventory::close();
}

updateinventory::~updateinventory()
{
    delete ui;
}
