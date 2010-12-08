#ifndef VIEWTHESUPPLIESWINDOW_H
#define VIEWTHESUPPLIESWINDOW_H

#include <QDialog>
#include <QTableWidgetItem>
#include "DataHandler.h"
#include "SupplyType.h"
#include "Region1.h"

namespace Ui {
    class ViewTheSuppliesWindow;
}

class ViewTheSuppliesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ViewTheSuppliesWindow(QWidget *parent = 0);
    ~ViewTheSuppliesWindow();

private:
    Ui::ViewTheSuppliesWindow *ui;
    QTableWidgetItem *region;
    QTableWidgetItem *type;
    QTableWidgetItem *quantity;

private slots:
    void editInventory(int);
    void ViewTheSuppliesWindowSubmitButtonHandler();
    void ViewTheSuppliesWindowCancelButtonHandler();
    void emitSuppliesEditedSignal();

signals:
    void suppliesViewedEdited();
};

#endif // VIEWTHESUPPLIESWINDOW_H
