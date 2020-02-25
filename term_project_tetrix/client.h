#ifndef CLIENT_H
#define CLIENT_H

/*
 * File: client.h
 * --------------
 * This interface exports the the interface when clicked client in the client_server_interface
 * it contain the functions to set port and IP number, connect to the server and send information to the server.
 */

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDataStream>
#include <stdio.h>
#include <WinSock2.h>
#include <QMainWindow>
#include <QTcpSocket>
#include "start_interface.h"
#include "character_board.h"
#include "result_interface.h"

QT_BEGIN_NAMESPACE
class QPushButton;
QT_END_NAMESPACE

class client : public QWidget
{
    Q_OBJECT
public:
    client(QWidget *parent = nullptr);
    ~client();
    //**
    int server_score = -1;
    int your_score;

signals:
    /*
     * Funciton: start_Competition
     * Usage: start_Competition()
     * ------------------------------------------------------------------
     * to display the competition result
     */
    void start_Competition();
    /*
     * Funciton: send_YourScore
     * Usage: send_YourScore
     * ------------------------------------------------------------------
     * send client's score to the result interface
     */
    void send_YourScore(int score);
    /*
     * Funciton: send_OpScore
     * Usage: send_OpScore
     * ------------------------------------------------------------------
     * send server's score to the result interface
     */
    void send_OpScore(int score);
    void finished();

public slots:
    /*
     * Funciton: displayClient
     * Usage: displayClient
     * ------------------------------------------------------------------
     * show the client interface
     */
    void displayClient();
    /*
     * Funciton: on_pushButton_Connect_clicked()
     * Usage: on_pushButton_Connet_clicked()
     * ------------------------------------------------------------------
     * do a series maniplation while the client click the connection button
     */
    void on_pushButton_Connect_clicked();
    /*
     * Funciton: socket_Disconnectioned()
     * Usage: socket_Disconnectioned()
     * ------------------------------------------------------------------
     * change the state and button text while the network is disconnected
     */
    void socket_Disconnected();
    //**
//    void connection();
    //    void connection();
        /*
         * Funciton: send_score
         * Usage: send_score
         * ------------------------------------------------------------------
         * send the client's score to the client
         */
    void send_score();
    /*
     * Funciton: read_score
     * Usage: read_score
     * ------------------------------------------------------------------
     * read server's score
     */
    int read_score();
    /*
     * Funciton: competition
     * Usage: competition
     * ------------------------------------------------------------------
     * check if signal in start_competition can be sent
     */
    void competition();
    /*
     * Funciton: client_recieve
     * Usage: client_recieve
     * ------------------------------------------------------------------
     * send the signal you got from send_YourScore
     */
    void client_recieve();

private:
    QTcpSocket *socket;
    QPushButton *p_goTo;
    QLineEdit *p_IpAddress;
    QLineEdit *p_Port;
    QLabel *p_IpLabel;
    QLabel *p_PortLabel;
    QPushButton *p_connection;
    start_interface *start;

    bool connection_check;
    //**
    CharacterBoard *board;
    bool isEndOp = false;
    bool isEndYour = false;
    result_interface * result_Interface;
};

#endif // CLIENT_H
