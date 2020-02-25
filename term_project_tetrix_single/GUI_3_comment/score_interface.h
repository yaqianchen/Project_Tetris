#ifndef SCORE_INTERFACE_H
#define SCORE_INTERFACE_H

#include <QWidget>
#include <QVBoxLayout>


QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
QT_END_NAMESPACE

class score_interface : public QWidget
{
    Q_OBJECT
public:
    score_interface();
    //display score interface according to score and mode when the game is stop
    void displayScore(int score); //********************

signals:

public slots:

//    //receive the score and connect it to LCD
//    void receiveScore(int score);
    //receive the mode selection
    void determineScore(int passed_score); //********************
    void gameStop(bool state); //********************

private:
    QLCDNumber *scoreLCD;
    int score;
    int mode;
};

#endif // SCORE_INTERFACE_H
