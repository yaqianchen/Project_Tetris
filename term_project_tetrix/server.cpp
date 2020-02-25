#include "server.h"
#include <qdebug.h>
#include <QtWidgets>
//**
//#include "character_board.h"

//#include "character_board.h"
/*
 * File: server.cpp
 * ---------------------------
 * This file implements the server interface while the player chose server in the client_server_interface
 */

/*
 * Implementation notes： server
 * -----------------------------------------------------
 * This function is used initialize the server class including build the server GUI and connect
 * buttons with signal, connet client and server with socket
 */

server::server(QWidget *parent) : QWidget (parent)
{
    setMaximumSize(700, 600);
    setMinimumSize(700, 600);
    QPalette server = this->palette();
    server.setBrush(QPalette::Background,QBrush(QPixmap(":/images/Background.png")));
    setPalette(server);

    start = new start_interface;
    p_goTo = new QPushButton();
    p_Port = new QLineEdit();
    p_PortLabel = new QLabel();
    p_listen = new QPushButton();
    server_Tcp = new QTcpServer();
    socket = new QTcpSocket();


    QString buttonStyle = "QPushButton:pressed{color:black;background:rgb(238,210,238);border-radius:10px;border-style:inset;}"
            "QPushButton{color:white;background:rgb(139,123,139);border-radius:10px;border-style:outset;}";

    p_goTo->setFixedSize(150,50);
    p_goTo->setStyleSheet(buttonStyle);
    p_Port->setFixedSize(200,50);
    p_PortLabel->setFixedSize(100,50);
    p_listen->setFixedSize(150,50);
    p_listen->setStyleSheet(buttonStyle);

    p_goTo->setText(QStringLiteral("ready"));
    p_listen->setText((QStringLiteral("listen")));
    p_PortLabel->setText(QStringLiteral("Port"));
    p_Port->setText("8765");

    QGridLayout *playout = new QGridLayout();
    playout->addWidget(p_goTo,0,0,2,1);
    playout->addWidget(p_listen,1,0,2,1);
    playout->addWidget(p_Port,1,1,1,1);
    playout->addWidget(p_PortLabel,1,2,1,1);
    playout->setHorizontalSpacing(40);
    playout->setVerticalSpacing(10);
    playout->setContentsMargins(30,30,30,30);
    setLayout(playout);

    connect(p_goTo, &QPushButton::clicked, start, &start_interface::displayStart);
    connect(p_listen,&QPushButton::clicked,this,&server::on_pushButton_Listen_clicked);
    QObject::connect(server_Tcp,&QTcpServer::newConnection,this,&server::server_New_Connect);
    p_goTo->setEnabled(false);
    connection_check = false;
}

void server::displaySever(){
    this->show();
    //**
    emitSignal();
}

void server::emitSignal(){
    your_score = start->YourScore;
    qDebug()<<"isEnd,send_score"<<endl;
    this->send_score();
    qDebug()<<"sad"<<endl;
   connect(start,&start_interface::start_server,this,&server::send_score);
    qDebug()<<"readyRead"<<endl;
   connect(socket,&QTcpSocket::readyRead,this,&server::read_score);
   qDebug()<<"isEnd,competition"<<endl;
     connect(start,&start_interface::start_server,this,&server::competition);
     connect(this,&server::finished,this,&server::competition);
}
/*
 * Implementation notes：~server
 * -----------------------------------------------------
 * This function is used to delete the server interface
 */

server::~server()
{
    delete this->socket;
}

//void on_pushButton_Listen_clicked();
////    void on_pushButton_Send_clicked();
//void server_New_Connect();
////    void socket_Read_Data();
//void socket_Disconnected();

/*
 * Implementation notes： on_pushButton_Listen_clicked
 * -----------------------------------------------------
 * This function is used to do a sereies of operation including change the text, allows others to connect to
 * this server while the network is originally disconnected
 * It will also change the text and disable the ready button while the network is originally connected
 */
void server::on_pushButton_Listen_clicked()
{
    if(p_listen->text() == tr("listen"))
        {

            int port = p_Port->text().toInt();


            if(!server_Tcp->listen(QHostAddress::Any, port))
            {

                qDebug()<<server_Tcp->errorString();
                return;
            }

            p_listen->setText("cancel");
            qDebug()<< "Listen succeessfully!";
        }
        else
        {

            if(connection_check)
            {

                socket->disconnectFromHost();
            }

            server_Tcp->close();

            p_listen->setText("listen");

           p_goTo->setEnabled(false);
        }
}

/*
 * Implementation notes： server_New_Connect
 * -----------------------------------------------------
 * This function is used to detect the new connection
 */
void server::server_New_Connect()
{

    socket = server_Tcp->nextPendingConnection();
    QObject::connect(socket, &QTcpSocket::disconnected, this, &server::socket_Disconnected);

    p_goTo->setEnabled(true);

    qDebug() << "A Client connect!";
    connection_check = true;
}

/*
 * Implementation notes： socket_Disconnected
 * -----------------------------------------------------
 * This function is used to change button text and disable the ready button while
 * connection failed
 */

void server::socket_Disconnected()
{
    p_goTo->setEnabled(false);
    qDebug() << "Disconnected!";
    connection_check = true;
}

/*
 * Implementation notes： read_score
 * -----------------------------------------------------
 * read the score from server
 */
int server::read_score(){
    QByteArray buffer;
    buffer = socket->readAll();
    if(!buffer.isEmpty()){
        client_score = buffer.toInt();
    }
    isEndOp = true;
//    emit start_Competition();
    qDebug()<<"opp's score:"<<client_score<<endl;
    return  client_score;
}

/*
 * Implementation notes： send_score
 * -----------------------------------------------------
 * get the signal of client's score
 */
void server::send_score(){
    isEndYour = true;
    char buff[128];//need to connct board and server
    memcpy(buff,&your_score,sizeof(your_score));
    socket->write(buff,128);
    socket->flush();
    emit finished();
}

/*
 * Implementation notes： competition
 * -----------------------------------------------------
 * check if signal in start_competition can be sent
 */
void server::competition(){
    if(isEndYour){
        result_Interface = new result_interface;
        connect(this,&server::send_OpScore,result_Interface,&result_interface::receiveOpScore);
        connect(this,&server::send_YourScore,result_Interface,&result_interface::receiveYourScore);
        connect(this,&server::start_Competition,result_Interface,&result_interface::displayResult);
        emit send_OpScore(client_score);
        if(isEndOp){
            emit send_YourScore(your_score);
           emit start_Competition();
        }


    }
}
