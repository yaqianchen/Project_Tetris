#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDataStream>
#include <stdio.h>
#include <WinSock2.h>
#include <QTcpSocket>
#include <QTcpServer>
#include "start_interface.h"
#include "character_board.h"
#include "result_interface.h"

/*
 * File: server.h
 * --------------
 * This interface exports the server interface when clicked server in the client_server_interface
 * it contians the functions to set port number and connet to the client
 */

QT_BEGIN_NAMESPACE
class QPushButton;
QT_END_NAMESPACE

class server : public QWidget
{
    Q_OBJECT
public:
    server( QWidget *parent = nullptr);
    ~server();
    //**
    int client_score = -1;
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
     * send server's score to the result interface
     */
    void send_YourScore(int score);
    /*
     * Funciton: send_OpScore
     * Usage: send_OpScore
     * ------------------------------------------------------------------
     * send client's score to the result interface
     */
    void send_OpScore(int score);
    void finished();

public slots:
    /*
     * Funciton: displayServer
     * Usage: displaySever
     * ------------------------------------------------------------------
     * show the server interface
     */
    void displaySever();
    /*
     * Funciton: on_pusheButton_Listen_clicked
     * Usage: on_pushButton_Listen_clicked
     * ------------------------------------------------------------------
     * change the button text and state when server click the listen button
     */
    void on_pushButton_Listen_clicked();
    /*
     * Funciton: server_New_Connect
     * Usage: server_New_Connect
     * ------------------------------------------------------------------
     * it detect new connection
     */
    void server_New_Connect();
    /*
     * Funciton: socket_Disconnected
     * Usage: socket_Disconnected
     * ------------------------------------------------------------------
     * It change the button text and state when connection failed
     */
    void socket_Disconnected();
    /*
     * Funciton: read_score
     * Usage: read_score
     * ------------------------------------------------------------------
     * read client's score
     */
    int read_score();
    /*
     * Funciton: send_score
     * Usage: send_score
     * ------------------------------------------------------------------
     * send the server's score to the client
     */
    void send_score();
    /*
     * Funciton: competition
     * Usage: competition
     * ------------------------------------------------------------------
     * check if signal in start_competition can be sent
     */
    void competition();

private:
    QTcpServer* server_Tcp;
    QTcpSocket *socket;
    QPushButton *p_goTo;
    QPushButton *p_listen;
    QLineEdit *p_Port;
    QLabel *p_PortLabel;
    start_interface *start;
    bool connection_check;

    //**
    CharacterBoard * board;
    bool isEndOp = false;
    bool isEndYour = false;
    result_interface * result_Interface;
    void emitSignal();
};

#endif // SERVER_H
