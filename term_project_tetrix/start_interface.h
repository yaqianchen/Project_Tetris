#ifndef START_INTERFACE_H
#define START_INTERFACE_H

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
#include "game_interface.h"
#include "score_interface.h"
#include "character_board.h"
#include "help_interface.h"
class start_interface : public QWidget
{
    Q_OBJECT
public:
    start_interface(QWidget *parent = nullptr);
    ~start_interface();
    int YourScore;

signals:
    void ModeSend(QString);
    void start_client();
    void start_server();


public slots:
    void MusicState(bool state);
    //**
    void ModeSlot();
    void displayStart();

private slots:
    void start_CS();

private:
    QLabel *p_ImageLabel;
    QRadioButton *p_MusicButton;
    QPushButton *p_StartButton;
    QPushButton *p_HelpButton;
    QPushButton *p_BioButton;
    QPushButton *p_GeoButton;
    QPushButton *p_LitButton;
    QMediaPlayer *p_Player;
    QMediaPlaylist *p_Playlist;
    QMediaPlayer *p_ButtonPlayer;
    game_interface *game;
    score_interface *score;
    CharacterBoard *board;
    help_interface *help;

};

#endif // START_INTERFACE_H
