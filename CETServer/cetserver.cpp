#include "cetserver.h"
#include "ui_cetserver.h"
#include <QDebug>
#include <QFile>
#include <QtXml/QDomDocument>
#include <QFileDialog>

cetserver::cetserver(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::cetserver)
{
    ui->setupUi(this);
    ui->startServerButton->setEnabled(false);
    ui->stopServerButton->setEnabled(false);
    databaseOpen = false;
}

//Destructor
cetserver::~cetserver()
{
    if (databaseOpen) {
        //Close the database connections and delete instance
        sqLite->closeDB();
    }
    delete sqLite;
    delete ui;
}

void cetserver::openDatabaseButtonHandler() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Database"), "./CETdb.sqlite", tr("Database Files (*.sqlite)"));
    QString dbType = "QSQLITE";
    QString dbHostName = "hostname";
    sqLite = new DatabaseHandler();
    //Check if the db file exists
    const QFile sqlite_db(fileName);
    if (fileName == "") {
    	//Do nothing
    }
    else if(sqlite_db.exists() && sqLite->openDB(dbType, fileName, dbHostName)) {
        ui->statusText->appendHtml("<b style=\"color:'green'\">Opening database.</b>");
        databaseOpen = true;
        ui->startServerButton->setEnabled(true);
        ui->openDatabaseButton->setEnabled(false);
    }
    else {
        ui->startServerButton->setEnabled(false);
        ui->statusText->appendHtml("<b style=\"color:'red'\">Database file not found. Check paths.</b>");
        databaseOpen = false;
    }
}

/*Start server button handler*/
void cetserver::startServerButtonHandler() {
    ui->statusText->appendHtml("<b style=\"color:'green'\">Starting Server.</b>");
    ui->stopServerButton->setEnabled(true);
    ui->startServerButton->setEnabled(false);
    //Start the server connection here

    /*
    //This should be the XML request document coming from the client
    QString xmlRequest;

    //This should be the XML reply document created by the server
    QString xmlReply = sqLite->queryDatabase(xmlRequest);

    //This is an optional function that will output the status of the server reply,
    //ie. "OK", "BadRequest" or "PermissionDenied"
    this->commandStatus(xmlReply);
    */

    //QString reply = sqLite->queryDatabase("<message><command>findEntities</command> <findEntitiesRequest type=\"CaseReport\"><query key=\"diseaseType\" value=\"8\" comparison=\"=\" /> <query key=\"dateOfReport\" value=\"2010-10-01\" comparison=\"&gt;=\" /> <query key=\"dateOfReport\" value=\"2010-10-31\" comparison=\"&lt;=\" /></findEntitiesRequest> </message>");
    //qDebug() << reply;



    //Start the server, pass it the handler so it can perform queries
    connect(&server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));

    server.listen(QHostAddress::Any, 6789);



    /*
    //These are hardcoded XML documents being tested
    //Test 1
    QString List = sqLite->queryDatabase("<message<command>findEntities</command><findEntitiesRequest type=\"Province\"></findEntitiesRequest></message>");
    //Output the status of the server reply
    this->commandStatus(List);

    //Test2
    QString List = sqLite->queryDatabase("<message><command>findEntities</command><findEntitiesRequest type=\"Region\"></findEntitiesRequest></message>");
    //Spit output to console
    qDebug() << List;
    //Spit output to statusText box in plain text (should not be html)
    ui->statusText->appendPlainText(List);
    */

}

/*Stop server button handler*/
void cetserver::stopServerButtonHandler() {
    ui->statusText->appendHtml("-----<br><b style=\"color:'red'\">Stopping Server.</b>");
    server.close();
    ui->stopServerButton->setEnabled(false);
    ui->startServerButton->setEnabled(true);
}

/*Press Exit in the menubar*/
void cetserver::on_actionExit_triggered()
{
    cetserver::close();
}


void cetserver::acceptConnection()
{
    client = server.nextPendingConnection();


    connect(client, SIGNAL(readyRead()), this, SLOT(startRead()));

}

//Outputs the command and its request status in the text area
//after queryingDatabase (optional use)
void cetserver::commandStatus(QString xmlString) {
    if (xmlString != "") {
        //Parse the xml string
        //The name of the xml document
        QDomDocument doc("xmldocument");
        if (doc.setContent(xmlString)) {
            //Get the root element
            QDomElement root = doc.documentElement();
            QDomNode n = root.firstChild();
            if(!n.isNull()) {
                QDomElement e = n.toElement();
                QDomNode f = n.nextSibling();
                QDomElement m = f.toElement();
                QString message = "-----<br>Command: ";
                message.append(e.text());
                message.append("<br>Status: ");
                message.append(m.text());
                if (e.tagName() == "command" && e.text() == "findEntities") {
                    ui->statusText->appendHtml(message);
                }
                else if (e.tagName() == "command" && e.text() == "saveEntities") {
                    ui->statusText->appendHtml(message);
                }
                else if (e.tagName() == "command" && e.text() == "getIdNumbers") {
                    ui->statusText->appendHtml(message);
                }
                else if (e.tagName() == "command" && e.text() == "login") {
                    ui->statusText->appendHtml(message);
                }
                else {
                    ui->statusText->appendHtml("-----<br>Command: Querying database");
                    ui->statusText->appendHtml("Status: Bad Request");
                }
            }
        }
        else {
            ui->statusText->appendHtml("-----<br>Command: Querying database");
            ui->statusText->appendHtml("Status: Bad Request");
        }
    }
    else {
        ui->statusText->appendHtml("-----<br>Command: Querying database");
        ui->statusText->appendHtml("Status: String malformed");
    }
}



//readmessages and respond
void cetserver::startRead()
{
    char buffer[1024] = {0};

    client->read(buffer, client->bytesAvailable());

    QString readIn;

    //cout << "Received: " << buffer << endl;

    readIn = (QString) buffer;

    //ui->statusText->appendPlainText("Received: " + readIn);

    //New messages in will be opened with the xml version tag
    //if we receive said tag we need to clear our query
    if (readIn.contains("<?xml version =\"1.0\"?>",Qt::CaseSensitive))
    {
        //cout<<"Clearing query."<<endl;

        xmlQuery = "";
    }

    //add the line received to the query string
    xmlQuery += readIn;

    //if we have the clsoe message tag in our query it is tiem to do stuf with the query
    if(xmlQuery.contains("</message>"))
    {
        //do stuff with query

        //cout<<"Query received: "<<xmlQuery.toStdString()<<endl;
        ui->statusText->appendPlainText("Query received:" + xmlQuery);

        QString reply = this->sqLite->queryDatabase(xmlQuery);
        xmlQuery = "";

        //qDebug() << reply;

        this->commandStatus(reply);

        ///////////test a delay///
        ////this shoudl work with client
        /*int x,y;
        for(x = 0; x < 2000; x++)
        {
            for(y = 0; y < 2000000; y++)
            {
            }
        }*/
        ////////////////

        if(client->isWritable()){

            client->write(reply.toAscii(),reply.length()+1);


            //cout<<"Message sent to client"<<endl;
        }else{
            //cout<<"Client not writable"<<endl;
        }
    }
}
