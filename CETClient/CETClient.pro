#-------------------------------------------------
#
# Project created by QtCreator 2010-12-07T22:58:53
#
#-------------------------------------------------

QT       += core gui webkit network xml sql

TARGET = CETClient
TEMPLATE = app

SOURCES += main.cpp \
    viewthesupplieswindow.cpp \
    viewthediseaseswindow.cpp \
    User.cpp \
    updateinventory.cpp \
    updatecasereport.cpp \
    SupplyType.cpp \
    ShipmentDetail.cpp \
    Shipment.cpp \
    Region1.cpp \
    Province.cpp \
    managetheshipmentswindow.cpp \
    mainwindow.cpp \
    Inventory.cpp \
    googlemap.cpp \
    DiseaseType.cpp \
    DataHandler.cpp \
    createshipmentswindow.cpp \
    configurecet.cpp \
    clientconnection.cpp \
    CaseReport.cpp \
    addsupplieswindow.cpp \
    adddiseaseswindow.cpp \
    aboutCET.cpp

OTHER_FILES += \
    mapDefinition.html \
    CET.png

HEADERS += \
    viewthesupplieswindow.h \
    viewthediseaseswindow.h \
    User.h \
    updateinventory.h \
    updatecasereport.h \
    SupplyType.h \
    ShipmentDetail.h \
    Shipment.h \
    Region1.h \
    Province.h \
    managetheshipmentswindow.h \
    mainwindow.h \
    Inventory.h \
    googlemap.h \
    DiseaseType.h \
    DataHandler.h \
    createshipmentswindow.h \
    configurecet.h \
    clientconnection.h \
    CaseReport.h \
    addsupplieswindow.h \
    adddiseaseswindow.h \
    aboutCET.h

FORMS += \
    viewthesupplieswindow.ui \
    viewthediseaseswindow.ui \
    updateinventory.ui \
    updatecasereport.ui \
    managetheshipmentswindow.ui \
    mainwindow.ui \
    createshipmentswindow.ui \
    configurecet.ui \
    addsupplieswindow.ui \
    adddiseaseswindow.ui \
    aboutCET.ui

RESOURCES += \
    mapDefinitionFile.qrc
