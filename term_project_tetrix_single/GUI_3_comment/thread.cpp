#include "thread.h"
#include <QDebug>
#include <QThread>
#include "character.h"
#include "character_board.h"

Thread::Thread(QObject *parent) :
    QThread(parent){
}

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
