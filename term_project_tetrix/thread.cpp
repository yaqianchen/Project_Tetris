#include "thread.h"
#include <QDebug>
#include <QThread>
#include "character.h"
#include "character_board.h"

/*
 * File: thread.cpp
 * ---------------------------
 * This file implements the control of thread
 */
Thread::Thread(QObject *parent) :
    QThread(parent){
}

/*
 * Implementation notes: run
 * -----------------------------------------------------
 * This function is used control the six sub thread while the isStarted is true and
 * isPaused is false
 */
void Thread::run()
{
    //线程运行
    while(board->isStarted)
    {
        if(!board->isPaused)
        {
            board->oneLineDown();
            board->setRandomNext();
            board->mode_selection();
            board->start();
            board->pause();
            board->removeCombination();
        }
    }
}
