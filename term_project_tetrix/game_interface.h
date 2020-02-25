#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include <QFrame>
#include <QWidget>
#include "character_board.h"


QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
class CharacterBoard;
QT_END_NAMESPACE

class game_interface : public QWidget
{
    Q_OBJECT

public:
    game_interface();
    int score;

 signals:
    void game_start();


public slots:
    void displayGame();
    void board_game();

private:
    QLabel *createLabel(const QString &text);

    QLabel *foreshowLabel;
    QLCDNumber *scoreLcd;
    QPushButton *startPauseButton;
    QPushButton *quitButton;
    QPushButton *downButton;
    QPushButton *leftButton;
    QPushButton *rightButton;
    CharacterBoard *board;

};

#endif // GAME_INTERFACE_H
