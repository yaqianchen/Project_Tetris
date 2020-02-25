/*
 * File: character_board.h
 * -----------------------
 * This file defines the character board class, which is the place where pieces
 * drop, combine, and then are removed.
 */

#ifndef CHARACTERBOARD_H
#define CHARACTERBOARD_H

#pragma once
#include <QMediaPlayer>
#include "score_interface.h"
#include <QtWidgets>
#include <QFrame>
#include "character.h"
#include <QBasicTimer>
#include "thread.h"
#include <mutex>
//using namespace std;

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

/*
 * Class: CharacterBoard
 * ---------------------
 * This class works as the place where characters appear and interact with
 * each other.
 */
class CharacterBoard : public QFrame{
    Q_OBJECT

public:

    /*
     * Constructor: CharacterBoard
     * Usage: CharacterBoard board;
     * ----------------------------
     * Initializes a new character board.
     */
    CharacterBoard(QWidget *parent=nullptr);

    /*
     * Method: oneLineDown
     * -------------------
     * Moves down the piece one line faster.
     */
    void oneLineDown();

    /*
     * Method: dropToBottom
     * --------------------
     * Moves the character down to the bottom of the board.
     */
    void dropToBottom();

    /*
     * Method: sizeHint, minimumSizeHint
     * ---------------------------------
     * sizeHint() sets the size of the board.
     * minimumSizeHint() sets the minimum size of the board.
     */
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    QString setRandomNext(); //随机产生下一个
    void showNextPiece();
    void setNextPieceLabel(QLabel* label);
    void removeCombination();  //检验与合并

    bool isStarted;
    bool isPaused;
    bool isEnded = false;

public slots:

    void mode_selection();

    /*
     * Method: start, pause
     * --------------------
     * start() will be called when the start/pause button is pressed in window.cpp.
     * pause() will be called when the pause button is pressed in window.cpp.
     */
    void start();
    void pause();


signals:

    /*
     * Method: scoreAltered, levelAltered, piecesRemovedAltered
     * --------------------------------------------------------
     * scoreAltered(int score) will emit signal to the score label in window.cpp
     * when score chenges.
     * levelAltered(int level) will emit signal to the level label in window.cpp
     * when level chenges.
     * piecesRemovedAltered(int numPieces) will emit signal to the pieceRemoved
     * label in window.cpp when labels combine and disappear.
     */
    void scoreAltered(int score);
    void levelAltered(int level);
    void piecesRemovedAltered(int numPieces);

    void score_to_score_interface(int score); //*************
    void isStop(bool state); //***************

protected:

    /*
     * Method: keyPressEvent
     * ---------------------
     * keyPressEvent(QKeyEvent *event) will detect which key the user presses and
     * call the corresponding function.
     */
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:

    /*
     * Method: clearBoard
     * ------------------
     * Clears all characters on the board.
     */
    void clearBoard();


    /*
     * Method: tryMove
     * ---------------
     * Judges whether there is empty space for the piece to move
     */
    bool tryMove(int x, int y, int newX, int newY);

    void newPiece();  //产生一个新块
    void droppedPiece();  //处理已经不能再下降的块块
    int timeout(){return 1000 / (1 + level);}  //设置倒计时时长
    void adjustment();
    void paintPiece(QPainter &painter,QRect& rect,int x,int y,int blockW,int blockH,QString comp);
    void buildDictionary();

    /* Instance variables */
    const static int boardHeight = 10;  //表示共10行
    const static int boardWidth = 10;  //10列
    const int pieceHeight = 30;  //每个piece的高度
    const int pieceWidth = 30;   //每个piece的宽度
    int mode;
    QMediaPlayer *combine_sound;
    QMediaPlayer *cancle_sound;
    score_interface *score_window;
    QPointer<QLabel> nextPieceLabel;
    QString board[boardHeight][boardWidth];  //用于储存每个位置的信息
    QString current;  //当前字符
    QString next;  //下一字符
    int current_x;  //当前字符位置 x坐标
    int current_y;  //当前字符位置 y坐标
    bool waitingForNewPiece=true; //表示移除完了，正在等待新块
    bool waitingForRemove=false; //等待检验和移除
    bool waitingForAdjust=false;  //调整位置
    bool remove=false;  //表示有没有更多的块被合并,默认值为false
    int positions[100][2];  // 记录发生变化的位置
    int combined[100][2];  //记录被结合的字的位置
    QString toBeChecked[100];  // 记录位置发生了变化时需再次检验的字
    int numOfPos=0;  //记录多少个位置发生了变化
    int numOfCombined; //记录多少个被结合了的字
    QBasicTimer timer;  //倒计时
    int numPiecesDropped;  //掉了多少个块了？
    int numPiecesRemoved;  //消了多少个块
    int level;  //等级
    int score = 0;  //分数
    int colorNum = 0;

    Thread *m_thread;
    std::mutex m_mutex1,m_mutex2,m_mutex3,m_mutex4,m_mutex5;
    std::mutex m_mutex6,m_mutex7,m_mutex8,m_mutex9,m_mutex10;
};


#endif // CHARACTERBOARD_H
