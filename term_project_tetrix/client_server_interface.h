#ifndef CLIENT_SERVER_INTERFACE_H
#define CLIENT_SERVER_INTERFACE_H

/*
 * File: client_server_interface.h
 * --------------
 * This interface exports the interface which allows the player to choose if they want to be client or server
 */
#include <QWidget>
#include <QtGui>
#include <QPushButton>
#include <QGridLayout>
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QRadioButton>
#include <QString>
#include "start_interface.h"
#include "game_interface.h"
#include "score_interface.h"
#include "client.h"
#include "server.h"

class client_server_interface : public QWidget
{
    Q_OBJECT
public:
    /*
     * Funciton: client_server_interface
     * Usage: client_server_interface (*parent)
     * ------------------------------------------------------------------
     * initialize the interface
     */
    client_server_interface(QWidget *parent = nullptr);
    /*
     * Funciton: ~client_server_interface
     * Usage: client_server_interface()
     * ------------------------------------------------------------------
     * delete the interface
     */
    ~client_server_interface();

signals:
    void ModeSend(QString);


private:
    QLabel *p_ImageLabel;
    QPushButton *p_client;
    QPushButton *p_server;
    QRadioButton *p_MusicButton;
    QPushButton *p_StartButton;
    QPushButton *p_HelpButton;
    QPushButton *p_BioButton;
    QPushButton *p_GeoButton;
    QPushButton *p_LitButton;
    QMediaPlayer *p_Player;
    QMediaPlaylist *p_Playlist;
    start_interface *start;
    game_interface *game;
    score_interface *score;
    client *client_test;
    server *server_test;
};

#endif // CLIENT_SERVER_INTERFACE_H
