#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QtWebKit>
#include <QList>
#include "configurecet.h"
#include "adddiseaseswindow.h"
#include "addsupplieswindow.h"
#include "viewthediseaseswindow.h"
#include "viewthesupplieswindow.h"
#include "createshipmentswindow.h"
#include "managetheshipmentswindow.h"
#include "updatecasereport.h"
#include "updateinventory.h"



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    this->setGeometry(100,100, 998,569);
    ui->setupUi(this);

    DataHandler *dh = new DataHandler();
    QFont font;
    font.setPointSize(9);
    ui->statusBar->setStyleSheet("QStatusBar::item { border: 0px solid black; }; ");
    if (dh->isConnected()) {
        /*
        connectionMessage = new QLabel("Connected to server.");
        connectionMessage->setFont(font);
        ui->statusBar->addWidget(connectionMessage);
        */
    }
    else {
        connectionMessage = new QLabel("Not connected to server.");
        connectionMessage->setFont(font);
        ui->statusBar->addWidget(connectionMessage);
    }
    delete dh;


    this->ui->type_selector->clear();
    this->ui->type_selector->addItems(fetchListOfDiseases());
    fetchDataForSelectedType();
    initializeMap();
    selectedCaseOrSupplyID = 0;
    QObject::connect(ui->e_s_selector,SIGNAL(currentIndexChanged(int)),this,SLOT(currentIndexChangedForESSelector(int)));
    QObject::connect(ui->type_selector,SIGNAL(currentIndexChanged(int)),this,SLOT(currentIndexChangedForTypeSelector(int)));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkConnection()));
    timer->start(30000); //30 seconds
}

//Check the connection every 30 seconds
void MainWindow::checkConnection() {
    ui->statusBar->removeWidget(connectionMessage);
    DataHandler *dh = new DataHandler();
    QFont font;
    font.setPointSize(9);
    if (dh->isConnected()) {
        /*
        connectionMessage = new QLabel("Connected to server.");
        connectionMessage->setFont(font);
        ui->statusBar->addWidget(connectionMessage);
        */
    }
    else {
        connectionMessage = new QLabel("Not connected to server.");
        connectionMessage->setFont(font);
        ui->statusBar->addWidget(connectionMessage);
    }
    delete dh;
}

void MainWindow::initializeMap(){
    gmap = new GoogleMap(ui->mapView, this);
    QObject::connect(gmap, SIGNAL(mapItemClicked(QString, QString)),
                     this, SLOT(setNameIDValue(QString, QString)));
    QObject::connect(gmap, SIGNAL(notifyMapTilesLoaded()),
                     this, SLOT(hideLoadingLabel()));
    gmap->show();
}

void MainWindow::updateData(){
    fetchDataForSelectedType();
    calculateLowHighNormal();
    gmap->updateIcons(this->ui->type_selector->currentIndex(), regionsWithDataForSelType_low, regionsWithDataForSelType_normal, regionsWithDataForSelType_high);
    this->ui->namebox->clear();;
    this->ui->idbox->clear();
    this->ui->numberofbox->clear();
}

void MainWindow::setNameIDValue(QString name, QString id){
    this->ui->namebox->setText(name);
    this->ui->idbox->setText(id);
    selectedCaseOrSupplyID = id.toInt();
    if(ui->e_s_selector->currentIndex() == 0){
        int numberOfCases = 0;
        for (int i = 0; i < caseReports.size(); i++) {
            if (caseReports[i].getRegionId() == id.toInt()) {
                int diseaseID = caseReports[i].getDiseaseType();
                QString diseaseName = getDiseaseName(diseaseID);
                if (diseaseName == this->ui->type_selector->currentText()) {
                    numberOfCases += caseReports[i].getQuantity();
                }
            }
        }
        QString numberOfCasesString;
        numberOfCasesString.setNum(numberOfCases);
        this->ui->numberofbox->setText(numberOfCasesString);
    } else {
        int numberOfSupplies = 0;
        for (int i = 0; i < inventory.size(); i++) {
            if (inventory[i].getRegionId() == id.toInt()) {
                int supplyID = inventory[i].getSupplyType();
                QString supplyTypeName = getSupplyTypeName(supplyID);
                if (supplyTypeName == this->ui->type_selector->currentText()) {
                    numberOfSupplies += inventory[i].getQuantity();
                }
            }
        }
        QString numberOfSuppliesString;
        numberOfSuppliesString.setNum(numberOfSupplies);
        this->ui->numberofbox->setText(numberOfSuppliesString);
    }
}

QStringList MainWindow::fetchListOfDiseases(){
    QStringList list;
    DataHandler *dh = new DataHandler();
    if (dh->isConnected()) {
        diseaseList = dh->getDiseaseTypes();
        for (int i = 0; i < diseaseList.size(); i++) {
            list.push_front(diseaseList[i].getName());
        }
        delete dh;
    }
    return list;
}

QStringList MainWindow::fetchListOfSupplyTypes(){
    QStringList list;
    DataHandler *dh = new DataHandler;
    if (dh->isConnected()) {
        supplyList = dh->getSupplyTypes();
        for (int i = 0; i < supplyList.size(); i++) {
            list.push_front(supplyList[i].getName());
        }
        delete dh;
    }
    return list;
}


void MainWindow::currentIndexChangedForESSelector(int index){
    this->ui->namebox->clear();
    this->ui->idbox->clear();
    this->ui->numberofbox->clear();
    this->ui->type_selector->clear();
    if(index == 0){
        this->ui->type_selector->addItems(fetchListOfDiseases());
        this->ui->numberof_label->setText("Number of Cases:");
    }else{
        this->ui->type_selector->addItems(fetchListOfSupplyTypes());
        this->ui->numberof_label->setText("Number of Supplies:");
    }
}

void MainWindow::currentIndexChangedForTypeSelector(int index){
    if(this->ui->type_selector->currentText().isEmpty()){
        //means clear() was called, so do nothing
    } else {
        fetchDataForSelectedType();
        calculateLowHighNormal();
        gmap->updateIcons(this->ui->type_selector->currentIndex(), regionsWithDataForSelType_low, regionsWithDataForSelType_normal, regionsWithDataForSelType_high);

    }
}

void MainWindow::fetchDataForSelectedType(){
    DataHandler *dh = new DataHandler;
    if (dh->isConnected()) {
        caseReports = dh->getCaseReports();
        inventory = dh->getInventory();
        delete dh;
    }
}


int MainWindow::getTotalNumberOfCasesForRegion(int regionID, QList<CaseReport> list){
    int numberOfCases = 0;
    for (int i = 0; i < list.size(); i++) {
        if (list[i].getRegionId() == regionID) {
            numberOfCases += list[i].getQuantity();
        }
    }
    return numberOfCases;
}

void MainWindow::calculateLowHighNormal(){

    if(this->ui->e_s_selector->currentIndex() == 0){
        regionsWithDataForSelType_low.clear();
        regionsWithDataForSelType_normal.clear();
        regionsWithDataForSelType_high.clear();
        regionsWithCasesForSelectedDisease.clear();

        QList<CaseReport> caseReportsForSelectedDisease;
        QList<int> regionIDQuantity;
        //get a set of caseReports for which there is data for selected disease
        for (int i = 0; i < caseReports.size(); i++) {
            if(getDiseaseName(caseReports[i].getDiseaseType()) == this->ui->type_selector->currentText()){
                caseReportsForSelectedDisease.push_front(caseReports[i]);
            }
        }

        //add up total quantities for each region
        DataHandler *dh = new DataHandler;
        if (dh->isConnected()) {
            QList<Region1> listOfRegions = dh->getRegions();
            delete dh;
            for (int i = 0; i < listOfRegions.size(); i++) {
                int totalNumberOfCasesForRegion = getTotalNumberOfCasesForRegion(listOfRegions[i].getId(), caseReportsForSelectedDisease);
                if(totalNumberOfCasesForRegion != 0){
                    regionIDQuantity.push_front(totalNumberOfCasesForRegion);
                    regionsWithCasesForSelectedDisease.push_front(listOfRegions[i].getId());
                }
            }

            //find the lowest and the highest values, tu use as thresholds
            if(!regionIDQuantity.isEmpty()){
                qSort(regionIDQuantity.begin(), regionIDQuantity.end());
                int highThreshold = regionIDQuantity.last();
                int lowThreshold = regionIDQuantity.first();
                int oneThird = (highThreshold - lowThreshold) / 3;

                //create low, normal and high lists
                if(oneThird != 0){
                    for (int i = 0; i < listOfRegions.size(); i++) {
                        int totalCases = getTotalNumberOfCasesForRegion(listOfRegions[i].getId(), caseReportsForSelectedDisease);
                        if(totalCases != 0){
                            if((totalCases >= lowThreshold) && (totalCases < (lowThreshold + oneThird))){
                                QString idString;
                                idString.setNum(listOfRegions[i].getId());
                                if(!regionsWithDataForSelType_low.contains(idString)){
                                    regionsWithDataForSelType_low.push_front(idString);
                                }
                            } else if ((totalCases >= (lowThreshold + oneThird)) && (totalCases < (lowThreshold + oneThird + oneThird))){
                                QString idString;
                                idString.setNum(listOfRegions[i].getId());
                                if(!regionsWithDataForSelType_normal.contains(idString)){
                                    regionsWithDataForSelType_normal.push_front(idString);
                                }

                            } else if ((totalCases > (lowThreshold + oneThird + oneThird) && (totalCases <= highThreshold))){
                                QString idString;
                                idString.setNum(listOfRegions[i].getId());
                                if(!regionsWithDataForSelType_high.contains(idString)){
                                    regionsWithDataForSelType_high.push_front(idString);
                                }
                            }
                        }
                    }
                } else {
                    for (int i = 0; i < regionsWithCasesForSelectedDisease.size(); i++) {
                        QString idString;
                        idString.setNum(regionsWithCasesForSelectedDisease[i]);
                        regionsWithDataForSelType_normal.push_front(idString);
                    }
                }
            }
        }

    } else {
        //get a set of supplyList for which there is data for selected supply type
        regionsWithDataForSelType_low.clear();
        regionsWithDataForSelType_normal.clear();
        regionsWithDataForSelType_high.clear();
        regionsWithCasesForSelectedDisease.clear();

        QList<Inventory> inventoryForSelectedSupplyType;
        QList<int> regionIDQuantity;
        //get a set of inventory for which there is data for selected supply type
        for (int i = 0; i < inventory.size(); i++) {
            if(getSupplyTypeName(inventory[i].getSupplyType()) == this->ui->type_selector->currentText()){
                inventoryForSelectedSupplyType.push_front(inventory[i]);
            }
        }

        //make a list of quantities available for any region
        for (int i = 0; i < inventoryForSelectedSupplyType.size(); i++) {
            regionIDQuantity.push_front(inventoryForSelectedSupplyType[i].getQuantity());
        }

        //find the lowest and the highest values, tu use as thresholds
        if(!regionIDQuantity.isEmpty()){
            qSort(regionIDQuantity.begin(), regionIDQuantity.end());
            int highThreshold = regionIDQuantity.last();
            int lowThreshold = regionIDQuantity.first();
            int oneThird = (highThreshold - lowThreshold) / 3;


            DataHandler *dh = new DataHandler;
            QList<Region1> listOfRegions;
            if (dh->isConnected()) {
                listOfRegions = dh->getRegions();
                delete dh;
            }

            //create low, normal and high lists
            if(oneThird != 0){
                for (int i = 0; i < listOfRegions.size(); i++) {
                    for (int k = 0; k < inventoryForSelectedSupplyType.size(); k++){
                        if(inventoryForSelectedSupplyType[k].getRegionId() == listOfRegions[i].getId()){
                            int totalCases = inventoryForSelectedSupplyType[k].getQuantity();
                            if(totalCases != 0){
                                if((totalCases >= lowThreshold) && (totalCases < (lowThreshold + oneThird))){
                                    QString idString;
                                    idString.setNum(listOfRegions[i].getId());
                                    if(!regionsWithDataForSelType_low.contains(idString)){
                                        regionsWithDataForSelType_low.push_front(idString);
                                    }
                                } else if ((totalCases >= (lowThreshold + oneThird)) && (totalCases < (lowThreshold + oneThird + oneThird))){
                                    QString idString;
                                    idString.setNum(listOfRegions[i].getId());
                                    if(!regionsWithDataForSelType_normal.contains(idString)){
                                        regionsWithDataForSelType_normal.push_front(idString);
                                    }

                                } else if ((totalCases > (lowThreshold + oneThird + oneThird) && (totalCases <= highThreshold))){
                                    QString idString;
                                    idString.setNum(listOfRegions[i].getId());
                                    if(!regionsWithDataForSelType_high.contains(idString)){
                                        regionsWithDataForSelType_high.push_front(idString);
                                    }
                                }
                            }
                        }
                    }

                }
            } else {
                for (int i = 0; i < regionsWithCasesForSelectedDisease.size(); i++) {
                    QString idString;
                    idString.setNum(regionsWithCasesForSelectedDisease[i]);
                    regionsWithDataForSelType_normal.push_front(idString);
                }
            }
        }
    }
}



QString MainWindow::getSupplyTypeName(int supplyTypeID){
    QString supplyTypeName = "";
    for (int i = 0; i < supplyList.size(); i++) {
        if(supplyList[i].getId() == supplyTypeID){
            supplyTypeName = supplyList[i].getName();
        }
    }
    return supplyTypeName;
}

QString MainWindow::getDiseaseName(int diseaseID){
    QString diseaseName = "";
    for (int i = 0; i < diseaseList.size(); i++) {
        if(diseaseList[i].getId() == diseaseID){
            diseaseName = diseaseList[i].getName();
        }
    }
    return diseaseName;
}

void MainWindow::hideLoadingLabel(){
    this->ui->loadinglabel->hide();
    qDebug() << "done";
    currentIndexChangedForTypeSelector(ui->type_selector->currentIndex());
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddDiseaseHandler()
{
    AddDiseasesWindow *addDiseasesWindow = new AddDiseasesWindow;
    addDiseasesWindow->showNormal();
    addDiseasesWindow->setModal(true);
    QObject::connect(addDiseasesWindow,SIGNAL(diseaseAdded()),this,SLOT(updateData()));
}

void MainWindow::AddSupplyHandler()
{
    AddSuppliesWindow *addSuppliesWindow = new AddSuppliesWindow;
    addSuppliesWindow->showNormal();
    addSuppliesWindow->setModal(true);
    QObject::connect(addSuppliesWindow,SIGNAL(suppliesAdded()),this,SLOT(updateData()));
}

void MainWindow::ViewDiseasesHandler()
{
    ViewTheDiseasesWindow *viewTheDiseasesWindow = new ViewTheDiseasesWindow;
    viewTheDiseasesWindow->showNormal();
    viewTheDiseasesWindow->setModal(true);
    QObject::connect(viewTheDiseasesWindow,SIGNAL(diseasesViewedEdited()),this,SLOT(updateData()));
}

void MainWindow::ViewSuppliesHandler()
{
    ViewTheSuppliesWindow *viewTheSuppliesWindow = new ViewTheSuppliesWindow;
    viewTheSuppliesWindow->showNormal();
    viewTheSuppliesWindow->setModal(true);
    QObject::connect(viewTheSuppliesWindow,SIGNAL(suppliesViewedEdited()),this,SLOT(updateData()));
}

void MainWindow::AddShipmentHandler()
{
    CreateShipmentsWindow *createShipmentsWindow = new CreateShipmentsWindow;
    createShipmentsWindow->showNormal();
    createShipmentsWindow->setModal(true);
}

void MainWindow::ManageShipmentsHandler()
{
    ManageTheShipmentsWindow *manageTheShipmentsWindow = new ManageTheShipmentsWindow;
    manageTheShipmentsWindow->showNormal();
    manageTheShipmentsWindow->setModal(true);
}

void MainWindow::AboutCETHandler()
{
    aboutDialog = new AboutCETDialog;
    aboutDialog->showNormal();
    aboutDialog->setModal(true);
}

void MainWindow::on_actionConfigure_triggered()
{
    ConfigureCet *configCet = new ConfigureCet;
    configCet->showNormal();
    configCet->setModal(true);
}

void MainWindow::EditDataHandler(){
    if(this->ui->e_s_selector->currentIndex() == 0){
        ViewTheDiseasesWindow *viewTheDiseasesWindow = new ViewTheDiseasesWindow;
        viewTheDiseasesWindow->showNormal();
        viewTheDiseasesWindow->setModal(true);
        QObject::connect(viewTheDiseasesWindow,SIGNAL(diseasesViewedEdited()),this,SLOT(updateData()));
    } else {
        ViewTheSuppliesWindow *viewTheSuppliesWindow = new ViewTheSuppliesWindow;
        viewTheSuppliesWindow->showNormal();
        viewTheSuppliesWindow->setModal(true);
        QObject::connect(viewTheSuppliesWindow,SIGNAL(suppliesViewedEdited()),this,SLOT(updateData()));
    }
}


