#ifndef CETSERVER_H
#define CETSERVER_H

#include <QMainWindow>
#include "DatabaseHandler.h"
#include <QtNetwork>


namespace Ui {
    class cetserver;
}

class cetserver : public QMainWindow
{
    Q_OBJECT

public:
    explicit cetserver(QWidget *parent = 0);
    ~cetserver();


/*UI Handlers*/
public slots:
    //Open database button
    void openDatabaseButtonHandler();
    //Start server button
    void startServerButtonHandler();
    //Stop server button
    void stopServerButtonHandler();
    //Output the command and reply status
    void commandStatus(QString);

    void acceptConnection();
    void startRead();

private:
    Ui::cetserver *ui;
    DatabaseHandler *sqLite;
    bool databaseOpen;
    //Server server;

    QTcpServer server;
    QTcpSocket* client;
    QString xmlQuery;

private slots:
    void on_actionExit_triggered();
};

#endif // CETSERVER_H
