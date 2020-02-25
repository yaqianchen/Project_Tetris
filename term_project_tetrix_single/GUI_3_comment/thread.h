#ifndef THREAD_H
#define THREAD_H
#include <QThread>
//#include "character_board.h"


class CharacterBoard;

/**
 * 使Shape下落
 */
class Thread : public QThread
{
    Q_OBJECT
public:
    explicit Thread(QObject *parent = 0);

    void run();

private :

    long m_sleepTime; //线程休眠时间
    CharacterBoard* board;
};

#endif // THREAD_H
