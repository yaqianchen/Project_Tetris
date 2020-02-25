#include "client.h"
#include <qdebug.h>
#include <QtWidgets>
/*
 * File: client.cpp
 * ---------------------------
 * This file implements the client interface while the player chose client in the client_server_interface
 */

/*
 * Implementation notes： client
 * -----------------------------------------------------
 * This function is used initialize the client class including build the client GUI and connect
 * buttons with signal, connet client and server with socket
 */
client::client(QWidget *parent) : QWidget (parent)
{
    setMaximumSize(700, 600);
    setMinimumSize(700, 600);
    QPalette client = this->palette();
    client.setBrush(QPalette::Background,QBrush(QPixmap(":/images/Background.png")));
    setPalette(client);
    socket = new QTcpSocket();
    QString buttonStyle = "QPushButton:pressed{color:black;background:rgb(238,210,238);border-radius:10px;border-style:inset;}"
            "QPushButton{color:white;background:rgb(139,123,139);border-radius:10px;border-style:outset;}";

    p_goTo = new QPushButton();
    p_IpAddress = new QLineEdit();
    p_Port = new QLineEdit();
    p_IpLabel = new QLabel();
    p_PortLabel = new QLabel();
    p_connection = new QPushButton();

    p_goTo->setFixedSize(150,50);
    p_goTo->setStyleSheet(buttonStyle);
    p_IpAddress->setFixedSize(200,50);
    p_Port->setFixedSize(200,50);
    p_IpLabel->setFixedSize(100,50);
    p_PortLabel->setFixedSize(100,50);
    p_connection->setFixedSize(150,50);
    p_connection->setStyleSheet(buttonStyle);
    p_goTo->setEnabled(false);

    p_goTo->setText("ready");
    p_connection->setText("connect");
    p_IpLabel->setText("IP");
    p_PortLabel->setText("Port");
    p_IpAddress->setText("127.0.0.1");
    p_Port->setText("8765");


    QGridLayout *playout = new QGridLayout();
    playout->addWidget(p_goTo,0,0,2,1);
    playout->addWidget(p_connection,1,0,2,1);
    playout->addWidget(p_IpAddress,0,4,2,1);
    playout->addWidget(p_IpLabel,0,3,2,1);
    playout->addWidget(p_Port,1,4,2,1);
    playout->addWidget(p_PortLabel,1,3,2,1);
    playout->setHorizontalSpacing(40);
    playout->setVerticalSpacing(10);
    playout->setContentsMargins(30,30,30,30);
    setLayout(playout);


    start = new start_interface;
    connection_check = false;
    connect(p_goTo, &QPushButton::clicked, start, &start_interface::displayStart);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &client::socket_Disconnected);
     connect(p_connection,&QPushButton::clicked, this, &client::on_pushButton_Connect_clicked);
}

/*
 * Implementation notes： displayClient
 * -----------------------------------------------------
 * This function is used to show the interface while detectd the signal
 */
void client::displayClient(){
    this->show();
    //**
    your_score = start->YourScore;
    qDebug()<<"start"<<endl;
    this->send_score();
    qDebug()<<"end"<<endl;
    connect(start,&start_interface::start_client,this,&client::client_recieve);
    connect(socket,&QTcpSocket::readyRead,this,&client::read_score);
    connect(start,&start_interface::start_client,this,&client::competition);
    connect(this,&client::finished,this,&client::competition);
}

/*
 * Implementation notes： ~client
 * -----------------------------------------------------
 * This function is used to delete the client class
 */
client::~client()
{
    delete this->socket;
}

/*
 * Implementation notes： client_recieve
 * -----------------------------------------------------
 *send the signal you got from send_YourScore
 */
void client::client_recieve(){
    your_score = start->YourScore;
    emit send_YourScore(your_score);
}

/*
 * Implementation notes： on_pushButton_Connect_clicked
 * -----------------------------------------------------
 * This function does a series of operation while the client press the connection button,
 * the operations including get the IP number, get the port number,connect to the server, change the text while the
 * network is originally not connected. It will also chang the text and set the ready button disabled while the
 * network is originally connected
 */
void client::on_pushButton_Connect_clicked()
{
    qDebug()<<"update_successfully"<<endl;
    if(p_connection->text() == tr("connect"))
    {
        QString IP;
        int port;
        qDebug()<<"first"<<endl;
        IP = p_IpAddress->text();
        qDebug()<<"there_pIpAddress"<<endl;
        port = p_Port->text().toInt();
        qDebug()<<"there_pPort"<<endl;
        socket->abort();
        qDebug()<<"thereabort"<<endl;
        socket->connectToHost(IP, port);
        qDebug()<<"thereConnctTo"<<endl;

        if(!socket->waitForConnected(10000))
        {
            qDebug() << "Connection failed!";
            return;
        }
        qDebug() << "Connect successfully!";
        p_goTo->setEnabled(true);
        p_connection->setText("Disconnect");
        connection_check = true;

    }
    else
    {
        socket->disconnectFromHost();
        p_connection->setText("connect");
        connection_check = false;
        p_goTo->setEnabled(false);
    }
}

/*
 * Implementation notes： socket_Disconnected
 * -----------------------------------------------------
 * This function is used to set the ready button disable and change
 * the text to connet while the connection failed
 */


void client::socket_Disconnected()
{
    p_goTo->setEnabled(false);
    p_connection->setText("connet");
    qDebug() << "Disconnected!";
    connection_check = true;
}

/*
 * Implementation notes： send_score
 * -----------------------------------------------------
 * get the signal of client's score
 */
//**
void client::send_score(){
    qDebug()<<"enter send_score"<<endl;
    isEndYour = true;
    char buff[128];//need to connect board and client
    memcpy(buff,&your_score,sizeof(your_score));
    socket->write(buff,128);
    socket->flush();
    emit finished();
    qDebug()<<"leave send_score"<<endl;
}

/*
 * Implementation notes： read_score
 * -----------------------------------------------------
 * read the score from server
 */
int client::read_score(){
    qDebug()<<"enter read_score"<<endl;
    QByteArray buffer;
    buffer = socket -> readAll();
    if(!buffer.isEmpty()){
        server_score = buffer.toInt();

    }
    isEndOp = true;
    qDebug()<<"Leave read_score"<<endl;
    return server_score;
}

/*
 * Implementation notes： competition
 * -----------------------------------------------------
 * check if signal in start_competition can be sent
 */
void client::competition(){
    if(isEndYour && isEndOp){
        qDebug()<<"enter competition"<<endl;
        result_Interface = new result_interface;
        connect(this,&client::send_OpScore,result_Interface,&result_interface::receiveOpScore);
        connect(this,&client::send_YourScore,result_Interface,&result_interface::receiveYourScore);
        connect(this,&client::start_Competition,result_Interface,&result_interface::displayResult);
        if(isEndOp){
            emit send_OpScore(server_score);
            if(isEndYour){
                emit send_YourScore(your_score);
            }
        }
        emit start_Competition();
        qDebug()<<"leave competition"<<endl;
    }
}
