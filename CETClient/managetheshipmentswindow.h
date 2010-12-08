#ifndef MANAGETHESHIPMENTSWINDOW_H
#define MANAGETHESHIPMENTSWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QTableWidgetItem>
#include "DataHandler.h"
#include "SupplyType.h"
#include "Region1.h"
#include "Shipment.h"
#include "Inventory.h"
#include "ShipmentDetail.h"


namespace Ui {
    class ManageTheShipmentsWindow;
}

class ManageTheShipmentsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ManageTheShipmentsWindow(QWidget *parent = 0);
    ~ManageTheShipmentsWindow();
private:
    Ui::ManageTheShipmentsWindow *ui;
    QStringList shipStateList;
    QMessageBox msgBox;
    int status;
    QTableWidgetItem *idText;
    QTableWidgetItem *sourceText;
    QTableWidgetItem *destText;
    QTableWidgetItem *typeText;
    QTableWidgetItem *quantRequested;
    QTableWidgetItem *quantShipped;
    QTableWidgetItem *createdText;
    QTableWidgetItem *shippedText;
    QTableWidgetItem *receivedText;
    QTableWidgetItem *cancelledText;
    QTableWidgetItem *statusText;
private slots:
    void changeShipmentStatus(QString);
    void ManageTheShipmentsWindowSubmitButtonHandler();
    void ManageTheShipmentsWindowCancelButtonHandler();
};

#endif // MANAGETHESHIPMENTSWINDOW_H
