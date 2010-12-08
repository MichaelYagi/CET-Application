#ifndef VIEWTHEDISEASESWINDOW_H
#define VIEWTHEDISEASESWINDOW_H

#include <QDialog>
#include <QTableWidgetItem>
#include "DataHandler.h"
#include "DiseaseType.h"
#include "Region1.h"

namespace Ui {
    class ViewTheDiseasesWindow;
}

class ViewTheDiseasesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ViewTheDiseasesWindow(QWidget *parent = 0);
    ~ViewTheDiseasesWindow();

private:
    Ui::ViewTheDiseasesWindow *ui;
    QTableWidgetItem *date;
    QTableWidgetItem *region;
    QTableWidgetItem *type;
    QTableWidgetItem *quantity;

private slots:
    void editCase(int);
    void viewTheDiseasesWindowCancelButtonHandler();
    void viewTheDiseasesWindowNewButtonHandler();
    void emitDiseasesEditedSignal();

signals:
    void diseasesViewedEdited();
};

#endif // VIEWTHEDISEASESWINDOW_H
