/*
 * File: character_board.cpp
 * -------------------------
 * This file implements the character board class.
 */

#include "character.h"
#include "character_board.h"
#include "game_interface.h"
#include <iostream>
#include <fstream>
#include <QWidget>
#include <QRect>
#include <QPainter>
#include <QPixmap>
#include <vector>
#include <QTextCodec>
#include <cstdio>
#include <QString>
#include <vector>
#include <QtWidgets>
#include <string>
#include <iostream>
#include <QFile>
#include <QResource>
using namespace std;

map<QString,vector<Character>> dictHumanity;
map<QString,vector<Character>> dictBiology;
map<QString,vector<Character>> dictGeology;


/* Implementation notes: mode_selection
 * -------------------------------------
 * This function receives information about which mode button
 * the player has selected and calls buildDictionary to read and store
 * characters.
 */
void CharacterBoard::mode_selection()
{
    std::lock_guard<std::mutex> guard(m_mutex7);
    QString ModeName = sender()->objectName();
    if (ModeName.compare("Bio") == 0){
        mode = 0;
    }else if (ModeName.compare("Geo") == 0){
        mode = 1;
    }else if (ModeName.compare("Lit") == 0){
        mode = 2;
    }
    buildDictionary();
    qDebug() << "mode selected!" << endl;
    qDebug() << next << endl;
}


/* Implementation notes:buildDictionary
 * ----------------------------------------
 * This function reads characters into the map corresponding to the mode chosed.
 * For example, when in mode Literature, the basic and humanity characters will
 * be read into map dictHumanity. The other two map will be kept empty.
 */
void CharacterBoard::buildDictionary(){
    QResource data(":/text/test.txt");
    QFile dataFile(data.absoluteFilePath());
    dataFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream instream(&dataFile);
    instream.setCodec(QTextCodec::codecForName("GBK"));
    while (!instream.atEnd()){
         QString line;
         line = instream.readLine();
         if (line == "") continue;
         qDebug() << line << "lala" << endl;
         unsigned int n1 = static_cast<unsigned int>(line.indexOf(" ",0));
         QString structure = line.left(static_cast<int>(n1));
         unsigned int n2 = static_cast<unsigned int>(line.indexOf(" ",static_cast<int>(n1+1)));
         QString category = line.mid(static_cast<int>(n1+1),static_cast<int>(n2-n1-1));
         unsigned int n3 = static_cast<unsigned int>(line.indexOf(" ",static_cast<int>(n2+1)));
         QString character = line.mid(static_cast<int>(n2+1),static_cast<int>(n3-n2-1));
         Character c;
         c.setStructure(structure);
         vector <QString> componentList;
         if (category != "基本"){
             c.isSpecial();
         }
         if (character.compare("加") == 0 || character.compare("增") == 0){
             c.isBonus();
         }
         if (structure == "上下"){
            unsigned int n4 = static_cast<unsigned int>(line.indexOf(" ",static_cast<int>(n3+1)));
            QString above = line.mid(static_cast<int>(n3+1),static_cast<int>(n4-n3-1));
            QString below = line.mid(static_cast<int>(n4+1),1);
            c.setComponent(character,above,below,"","","");
            componentList.push_back(above);
            if (above != below) componentList.push_back(below);
         } else if (structure == "左右"){
             unsigned int n4 = static_cast<unsigned int>(line.indexOf(" ",static_cast<int>(n3+1)));
             QString left = line.mid(static_cast<int>(n3+1),static_cast<int>(n4-n3-1));
             QString right = line.mid(static_cast<int>(n4+1),1);
             c.setComponent(character,"","",left,right,"");
             componentList.push_back(left);
             if (right != left) componentList.push_back(right);
         } else if (structure == "左中右"){
             unsigned int n4 = static_cast<unsigned int>(line.indexOf(" ",static_cast<int>(n3+1)));
             QString left = line.mid(static_cast<int>(n3+1),static_cast<int>(n4-n3-1));
             unsigned int n5 = static_cast<unsigned int>(line.indexOf(" ",static_cast<int>(n4+1)));
             QString right = line.mid(static_cast<int>(n4+1),static_cast<int>(n5-n4-1));
             QString middle = line.mid(static_cast<int>(n5+1),1);
             c.setComponent(character,"","",left,right,middle);
             componentList.push_back(left);
             if (middle != left) componentList.push_back(middle);
             if (right != left && right != middle) componentList.push_back(right);
         } else if (structure == "上左右"){
             unsigned int n4 = static_cast<unsigned int>(line.indexOf(" ",static_cast<int>(n3+1)));
             QString above = line.mid(static_cast<int>(n3+1),static_cast<int>(n4-n3-1));
             unsigned int n5 = static_cast<unsigned int>(line.indexOf(" ",static_cast<int>(n4+1)));
             QString left = line.mid(static_cast<int>(n4+1),static_cast<int>(n5-n4-1));
             QString right = line.mid(static_cast<int>(n5+1),1);
             c.setComponent(character,above,"",left,right,"");
             componentList.push_back(above);
             if (left != above) componentList.push_back(left);
             if (right != left && right != above) componentList.push_back(right);
         } else if (structure == "左右下"){
             unsigned int n4 = static_cast<unsigned int>(line.indexOf(" ",static_cast<int>(n3+1)));
             QString left = line.mid(static_cast<int>(n3+1),static_cast<int>(n4-n3-1));
             unsigned int n5 = static_cast<unsigned int>(line.indexOf(" ",static_cast<int>(n4+1)));
             QString right = line.mid(static_cast<int>(n4+1),static_cast<int>(n5-n4-1));
             QString below = line.mid(static_cast<int>(n5+1),1);
             c.setComponent(character,"",below,left,right,"");
             componentList.push_back(left);
             if (right != left) componentList.push_back(right);
             if (below != left && below != right) componentList.push_back(below);
         } else if (structure == "上中下"){
             unsigned int n4 = static_cast<unsigned int>(line.indexOf(" ",static_cast<int>(n3+1)));
             QString above = line.mid(static_cast<int>(n3+1),static_cast<int>(n4-n3-1));
             unsigned int n5 = static_cast<unsigned int>(line.indexOf(" ",static_cast<int>(n4+1)));
             QString middle = line.mid(static_cast<int>(n4+1),static_cast<int>(n5-n4-1));
             QString below = line.mid(static_cast<int>(n5+1),1);
             c.setComponent(character,above,below,"","",middle);
             componentList.push_back(above);
             if (middle != above) componentList.push_back(middle);
             if (below != above && below != middle) componentList.push_back(below);
         } else if (structure == "左上下"){
             unsigned int n4 = static_cast<unsigned int>(line.indexOf(" ",static_cast<int>(n3+1)));
             QString left = line.mid(static_cast<int>(n3+1),static_cast<int>(n4-n3-1));
             unsigned int n5 = static_cast<unsigned int>(line.indexOf(" ",static_cast<int>(n4+1)));
             QString above = line.mid(static_cast<int>(n4+1),static_cast<int>(n5-n4-1));
             QString below = line.mid(static_cast<int>(n5+1),1);
             c.setComponent(character,above,below,left,"","");
             componentList.push_back(left);
             if (above != left) componentList.push_back(above);
             if (below != left && below != above) componentList.push_back(below);
         }
         if ((mode == 2) && (category == "人文" || category == "基本")){
             for (QString component : componentList){
                 if (dictHumanity.find(component) != dictHumanity.end()){
                     dictHumanity[component].push_back(c);
                 } else {
                     vector<Character> list;
                     list.push_back(c);
                     dictHumanity[component] = list;
                 }
             }
         } else if ((mode == 0) && (category == "生物" || category == "基本")){
              for (QString component : componentList){
                     if (dictBiology.find(component) != dictBiology.end()){
                         dictBiology[component].push_back(c);
                     } else {
                         vector<Character> list;
                         list.push_back(c);
                         dictBiology[component] = list;
                     }
              }
         } else if ((mode == 1) && (category == "地质" || category == "基本")){
             for (QString component : componentList){
                    if (dictGeology.find(component) != dictGeology.end()){
                        dictGeology[component].push_back(c);
                    } else {
                        vector<Character> list;
                        list.push_back(c);
                        dictGeology[component] = list;
                    }
             }
        }
    }
}


/*
 * Implementation notes: CharacterBoard
 * ------------------------------------
 * The constructor initializes a new character board.
 */
CharacterBoard::CharacterBoard(QWidget* parent)
    :QFrame(parent)
{
    score_window = new score_interface; //*********************
    connect(this, &CharacterBoard::score_to_score_interface, score_window, &score_interface::determineScore); //************
    connect(this, &CharacterBoard::isStop, score_window, &score_interface::gameStop); //****************

    setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    isStarted = false;
    isPaused = false;
    clearBoard();
    m_thread = new Thread;
//    buildDictionary();
//    next = setRandomNext();

}


/* Implementation notes: newPiece
 * -----------------------------------
 * This functino generates a new character component piec. If
 * the new piece cannot fall down, the game is stopped.
 */
void CharacterBoard::newPiece(){
    current = next;
//    qDebug()<< "newPiece:"<<current;
//    next = setRandomNext();
//    showNextPiece();
    current_x = boardWidth / 2 - 1;
    current_y = boardHeight;
    if (!tryMove(current_x,current_y,0,-1)){   //这里要根据肖淞月的函数修改trymove的arguments
        current = "";
        isPaused = true;
        isStarted = false;
        isEnded = true;
        timer.stop();
        emit score_to_score_interface(score); //****************
        emit isStop(true); //****************
        return;
    }
    showNextPiece();
    qDebug()<< "newPiece:"<<current<< current_x << current_y << endl;         //////////////////////////////
}


/* Implementation notes: setNextPieceLabel
 * ---------------------------------------
 * This function passes the information about the label to
 * data field nextPieceLabel.
 */
void CharacterBoard::setNextPieceLabel(QLabel* label){
    nextPieceLabel = label;
}


/* Implementation notes: showNextPiece
 * ----------------------------------------
 * This function shows the next piece in the "Next" label box
 */
void CharacterBoard::showNextPiece(){
    std::lock_guard<std::mutex> guard(m_mutex6);
    qDebug()<< "showNextPiece:"<<current<< current_x << current_y << endl;  /////////////////////////////////////
    if (!nextPieceLabel){
        return;
    }
    next = setRandomNext();
    QPixmap pixmap(300,70);
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(),nextPieceLabel->palette().background());
    painter.drawText(pixmap.rect(),Qt::AlignCenter,next);
    nextPieceLabel->setPixmap(pixmap);
    qDebug()<< "showNextPiece:"<<current<< current_x << current_y << endl;  /////////////////////////////////////
}


/* Implementation notes: setRandomNext
 * -----------------------------------------
 * This function set the next piece to be a random character component,
 * which is chosen from the map corresponding to the mode
 */
QString CharacterBoard::setRandomNext(){
    std::lock_guard<std::mutex> guard(m_mutex5);
    if (!dictHumanity.empty()){
        while (true){
            auto iter = dictHumanity.begin();
            std::advance(iter,static_cast<unsigned int>(rand()) % dictHumanity.size());
            QString key = iter->first;
            if (key == "" || key == " " || key == "\t" || key == "\n") continue;
            qDebug()<< "setRandomNext1:"<<key<< current_x << current_y << endl;       /////////////////////////////////
            return key;
        }
    } else if (!dictGeology.empty()){
        auto iter = dictGeology.begin();
        std::advance(iter,static_cast<unsigned int>(rand()) % dictGeology.size());
        QString key = iter->first;
        qDebug()<< "setRandomNext:"<<key<< current_x << current_y << endl;       /////////////////////////////////
        return key;
    } else {
        auto iter = dictBiology.begin();
        std::advance(iter,static_cast<unsigned int>(rand()) % dictBiology.size());
        QString key = iter->first;
        qDebug()<<  "setRandomNext:"<<current << current_x << current_y<< endl;       /////////////////////////////////
        return key;
    }
}



/* Implementation notes: adjustment
 * ------------------------------------
 * In this function, the combined characters are removed, the positions of the rest of the
 * characters are adjusted. Then this function set the timer to count down. When the timer
 * times out again, we will start the next round of removing.
 */
void CharacterBoard::adjustment(){
    cancle_sound = new QMediaPlayer; //************************
    cancle_sound->setMedia(QMediaContent(QUrl("qrc:/sounds/cancle.mp3"))); //************************
    if (waitingForAdjust){
        waitingForAdjust = false;
        int x = 0;
        while (x<100){
            positions[x][0] = -1;
            positions[x][0] = -1;
            toBeChecked[x] = "";
            x += 1;
        }
        int n = 0;
        while (n < numOfCombined){
            board[combined[n][0]][combined[n][1]] = "";
            combined[n][0] = -1;
            combined[n][1] = -1;
            n += 1;
        }
        numOfPos = 0;
        for (int i=0; i<boardWidth; i++){
            int column = -1;
            for (int j=0; j<boardHeight; j++){
                if (board[i][j].compare("") == 0){
                    for (int k = j+1; k<boardHeight; k++){
                        if (board[i][k].compare("") != 0){
                            column = i;
                            int diff = k - j;
                            for (int m=j; m<boardHeight-diff; m++){
                                board[i][m] = board[i][m+diff];
                            }
                            waitingForRemove = true;
                            break;
                        }
                    }
                }
            }
            int row = 0;
            if (column != -1){
                while (board[column][row].compare("") != 0){
                    positions[numOfPos][0] = column;
                    positions[numOfPos][1] = row;
                    toBeChecked[numOfPos] = board[column][row];
                    row += 1;
                    numOfPos += 1;
                }
            }
        }
        if (waitingForRemove){
            timer.start(timeout(),this);
        } else { timer.start(500,this);}
        update();
        cancle_sound->play(); //********************
    }
    qDebug()<<  "adjustment:"<<current<< current_x << current_y << endl;       /////////////////////////////////
}

/*
 * Implementation notes: clearBoard
 * --------------------------------
 * Clearing the board essencially means that assign "" to every entry
 * of the character board.
 */
void CharacterBoard::clearBoard(){
    std::lock_guard<std::mutex> guard(m_mutex9);
    for (int i = 0; i<boardHeight; i++){
        for (int j = 0; j<boardWidth; j++){
            QString empty = "";
            board[i][j] = empty;
        }
    }
    qDebug()<<"CharacterBoard:"<< current<< current_x << current_y << endl;       /////////////////////////////////
}


/* Implementation notes: paintEvent
 * ---------------------------------
 * This functin overrides the original paintEvent inherited from
 * QFrame. It will first paint all the pieces that have already
 * dropped to the bottom, then paint the current piece. Every time
 * this function is called, the pieces painted will all change color
 * at the same time.
 */
void CharacterBoard::paintEvent(QPaintEvent *event){
    std::cout << "paintEvent" << current_x << current_y << endl;      //////////////////
    qDebug()<< "paintEvent" << current<< endl;       /////////////////////////////////
    QFrame::paintEvent(event);
    QPainter painter(this);
    QRect rect = contentsRect();
    if (isPaused){
        if(!isEnded)//not end
        {painter.drawText(rect,Qt::AlignCenter,tr("Pause"));
        return;}else {
     painter.drawText(rect,Qt::AlignCenter,tr("Game Over"));}
    } else {
        for (int i = 0; i < boardHeight; i++){
            for (int j = 0; j < boardWidth; j++){
                QString s = board[j][i];
                if (s != ""){
                    QRect pieceRect(j*pieceWidth,(boardHeight-i-1)*pieceHeight,pieceWidth,pieceHeight);
                    paintPiece(painter,pieceRect,j*pieceWidth,(i)*pieceHeight,pieceWidth,pieceHeight,s);
                }
            }
        }
        if (current !=""){
            QRect pieceRect(current_x*pieceWidth,(boardHeight-current_y-1)*pieceHeight,pieceWidth,pieceHeight);
            QString cur = current;
            paintPiece(painter,pieceRect,current_x*pieceWidth,(boardHeight-current_y-1)*pieceHeight,pieceWidth,pieceHeight,cur);
            qDebug()<<"paintEvent"<< current<< current_x << current_y << endl;       /////////////////////////////////
        }
   }
}


/* Implementation notes: paintPiece
 * ---------------------------------------
 * This function paints a single piece and the character on it.
 */
void CharacterBoard::paintPiece(QPainter &painter,QRect& rect,int x,int y,int blockW,int blockH,QString comp){
    static const QRgb colors[6] = {0xF0F8FF, 0xE6E6FA, 0xFFDAB9, 0x8FBC8F, 0xEEE5DE, 0xFAFAD2};
    QColor color = colors[colorNum % 6];
    painter.fillRect(rect,color);
//    painter.setPen(color.light());
//    painter.drawLine(x,y,x,y+pieceHeight);
//    painter.drawLine(x,y,x+pieceWidth,y);
//    painter.setPen(color.dark());
//    painter.drawLine(x,y,x+pieceWidth,y+pieceHeight);
//    painter.drawLine(x+blockW,y+blockH,x+blockW,y);
    painter.setPen("black");
    painter.drawText(rect,Qt::AlignCenter,comp);
    qDebug()<<"paintPiece:"<< current<< current_x << current_y << endl;       /////////////////////////////////
}


/* Implementation notes: timerEvent
 * ----------------------------------
 * This function reimplements the timerEvent inherited from
 * QFrame. Each time the basic timer times out, this function
 * will be called. We will decide what to do next according to
 * the value of waitingForRemove, waitingForNewPiece, isStarted,
 * and waitingForAdjust
 */
void CharacterBoard::timerEvent(QTimerEvent *event){
    if (event->timerId() == timer.timerId()){
        if (waitingForRemove){
            removeCombination();
        } else if (waitingForAdjust){
            adjustment();
        } else if (waitingForNewPiece){
            waitingForNewPiece = false;
            newPiece();
            if(isStarted){
                timer.start(timeout(),this);
            }
        } else {
            oneLineDown();
        }

    } else {
        QFrame::timerEvent(event);
    }
    qDebug()<<"timerEvent" << current<< current_x << current_y << endl;       /////////////////////////////////
}

/*
 * Implementation notes: oneLineDown
 * ---------------------------------
 * If the piece is allowed to move one line down, it will do so immediately.
 */
void CharacterBoard::oneLineDown(){
    std::lock_guard<std::mutex> guard(m_mutex1);
    if (!tryMove(current_x,current_y,0,-1)){
        droppedPiece();
    }
    qDebug()<<"oneLineDown" << current<< current_x << current_y << endl;       /////////////////////////////////
}

//处理已经不能再往下掉的方块
void CharacterBoard::droppedPiece(){
    std::lock_guard<std::mutex> guard(m_mutex2);
    board[current_x][current_y] = current;
    numPiecesDropped++;
    if (numPiecesDropped % 10 == 0){
        level++;
        timer.start(500,this);
        emit levelAltered(level);
    }
    waitingForRemove = true;
    waitingForAdjust = false;
    waitingForNewPiece = false;
    numOfPos = 1;
    colorNum++;
    positions[0][0] = current_x;
    positions[0][1] = current_y;
    toBeChecked[0] = current;
    update();
    timer.start(500,this);
    qDebug()<< "droppedPiece:" << current<< current_x << current_y << endl;       /////////////////////////////////
}


/*
 * Implementation notes: sizeHint, minimumSizeHint
 * -----------------------------------------------
 * These two functions override the sizeHint function and the minimumSizeHint
 * function in the QSize class.
 */
QSize CharacterBoard::sizeHint() const {
    return QSize(boardWidth*15 + frameWidth()*2, boardHeight*15 + frameWidth()*2);
}
QSize CharacterBoard::minimumSizeHint() const {
    return QSize(boardWidth*5 + frameWidth()*2, boardHeight*5 + frameWidth()*2);
}

/*
 * Implementation notes: start
 * ---------------------------
 * First, it checks whether the isStarted signal is on. If so, it will pause.
 * If not, the isStarted signal will turn on and initialize all parameters
 * related to grading. Meanwhile, it will emit signals of piecesRemovedAltered,
 * scoreAltered, and levelAltered to the labels in window.cpp. Lastly, it will
 * start the timer.
 */
void CharacterBoard::start() {
    std::lock_guard<std::mutex> guard(m_mutex8);
    if (isStarted) {
        pause();
    } else{
        isStarted = true;
        isPaused = false;
        waitingForNewPiece = true;
        numPiecesRemoved = 0;
        numPiecesDropped = 0;
        score = 0;
        level = 1;
        clearBoard();
        next = setRandomNext();
        emit piecesRemovedAltered(numPiecesRemoved);
        emit scoreAltered(score);
        emit levelAltered(level);

        timer.start(timeout(), this);
        qDebug()<< "start:" << current<< current_x << current_y << endl;       /////////////////////////////////
    }

}

/*
 * Implementation notes: pause
 * ---------------------------
 * First, it checkes whether the isPaused signal is on. If not, the timer will
 * directly stop. Otherwise, the timer will start. After that, the isPaused
 * signal will become its opposite.
 */
void CharacterBoard::pause() {
    if (!isPaused) {
        timer.stop();
    } else {
        timer.start(timeout(), this);
    }
    isPaused = !isPaused;
    update();
}

/*
 * Implementation notes: keyPressEvent
 * -----------------------------------
 * First, it checkes whether there is any character on the board. If not, it
 * will directly end. Otherwise, a switch statement will be used to detect
 * which key the user presses and calls the corresponding function.
 */
void CharacterBoard::keyPressEvent(QKeyEvent *event) {
    if (!waitingForAdjust && !waitingForRemove && !waitingForNewPiece){
        if (!isStarted || isPaused || current == "") {
            QFrame::keyPressEvent(event);
            return;
        }

        switch (event->key()) {
        case Qt::Key_Left:
            tryMove(current_x, current_y,-1,0);
            break;
        case Qt::Key_Right:
            tryMove(current_x, current_y, 1,0);
            break;
        case Qt::Key_Space:
            dropToBottom();
            break;
        case Qt::Key_D:
            oneLineDown();
            break;
        default:
            QFrame::keyPressEvent(event);
        }
        qDebug()<< "keyPressEvent:" <<current<< current_x << current_y << endl;       /////////////////////////////////
    }
}


/*
 * Implementation notes: dropToBottom
 * ----------------------------------
 * This functions first tries to move the character by the largest height
 * and then calls the droppedPiece function.
 */
void CharacterBoard::dropToBottom() {
    std::lock_guard<std::mutex> guard(m_mutex4);
    int dropHeight = 0;
    int newY = current_y;
    while (newY > 0) {
        if (!tryMove(current_x,newY,0,-1)) {
            break;
        }
        newY--;
        dropHeight++;
    }
    droppedPiece();
    qDebug()<< "dropToBottom:" << current<< current_x << current_y << endl;       /////////////////////////////////
}

/*
 * Implementation notes: tryMove
 * -----------------------------
 * First, it calculates the possible new position of the character. Then it checks
 * whether the position is out of the board or whether the position has been
 * occupied. If not, the character will occupy the new piece.
 */
bool CharacterBoard::tryMove(int x, int y, int dx, int dy) {
    std::lock_guard<std::mutex> guard(m_mutex3);
    int newX = x + dx;
    int newY = y + dy;

    if (newX < 0 || newX >= boardWidth || newY < 0 || newY >= boardHeight) {
        return false;
    }
    QString empty = "";
    if (board[newX][newY] != empty){
        return false;
    }
    if (board[newX][newY-1] != empty){
        current_x = newX;
        current_y = newY;
        update();
        return false;
    }
    current_x = newX;
    current_y = newY;
    update();
//    timer.start(500,this);
    qDebug()<<  "tryMove:" <<current<< current_x << current_y << endl;       /////////////////////////////////
    return true;
}

//检查可不可以消去，如果可以则消去.
void CharacterBoard::removeCombination(){
    combine_sound = new QMediaPlayer; //************************
    combine_sound->setMedia(QMediaContent(QUrl("qrc:/sounds/combine.mp3"))); //************************

    std::lock_guard<std::mutex> guard(m_mutex10);
    std::cout << "removeCommbination:" << current_x << current_y << endl;        /////////////////////////////////////////////////////////
    qDebug()<<  "removeCommbination:" <<current<< endl;       /////////////////////////////////
    //vector <Character>::iterator iter;
    map<QString,vector<Character>>* mp;
    if (!dictHumanity.empty()){
        mp = &dictHumanity;
        qDebug() << "humanity dict selected" << endl;
    } else if (!dictGeology.empty()){
        mp = &dictGeology;
    } else {
        mp = &dictBiology;
    }
    remove = false;
    waitingForRemove = false;
    numOfCombined = 0;
    int i = 0;
    //以下这一部分是游戏的核心逻辑
    while(i < numOfPos){
        QString s = toBeChecked[i];
        int j = 0;
        while (j < static_cast<int>((*mp)[s].size())){
            qDebug() << j << endl;
            Character c = (*mp)[s][j];
            qDebug() << c.getCharacter() << endl;
            if (c.getStructure() == LeftMiddleRight){
                if ((positions[i][0]+2)< boardWidth && board[positions[i][0]][positions[i][1]] == c.getLeft() &&
                        board[positions[i][0]+1][positions[i][1]] == c.getMiddle() &&
                        board[positions[i][0]+2][positions[i][1]] == c.getRight()){
                    board[positions[i][0]+1][positions[i][1]] = c.getCharacter();
                    combine_sound->play(); //************************
                    board[positions[i][0]][positions[i][1]] = "";
                    board[positions[i][0]+2][positions[i][1]] = "";
                    remove = true;
                    if ((*mp)[s][j].bonusOrNot()){
                        score += 30;
                    } else if (c.specialOrNot()){
                        score += 20;
                    } else {
                        score += 10;
                    }
                    combined[numOfCombined][0] = positions[i][0] + 1;
                    combined[numOfCombined][1] = positions[i][1];
                    numOfCombined += 1;
                    break;
                }else if ((positions[i][0]+1) < boardWidth && (positions[i][0]-1)>= 0 && board[positions[i][0]][positions[i][1]] == c.getMiddle() &&
                           board[positions[i][0]-1][positions[i][1]] == c.getLeft() &&
                           board[positions[i][0]+1][positions[i][1]] == c.getRight()){
                    board[positions[i][0]][positions[i][1]] = c.getCharacter();
                    combine_sound->play(); //************************
                    board[positions[i][0]-1][positions[i][1]] = "";
                    board[positions[i][0]+1][positions[i][1]] = "";
                    remove = true;
                    if (c.bonusOrNot()){
                        score += 30;
                    } else if (c.specialOrNot()){
                        score += 20;
                    } else {
                        score += 10;
                    }
                    combined[numOfCombined][0] = positions[i][0];
                    combined[numOfCombined][1] = positions[i][1];
                    numOfCombined += 1;
                    break;
                } else if ((positions[i][0]-2)>=0 && board[positions[i][0]][positions[i][1]] == c.getRight() &&
                           board[positions[i][0]-1][positions[i][1]] == c.getMiddle() &&
                           board[positions[i][0]-2][positions[i][1]] == c.getLeft()){
                    board[positions[i][0]-1][positions[i][1]] = c.getCharacter();
                    combine_sound->play(); //************************
                    board[positions[i][0]][positions[i][1]] = "";
                    board[positions[i][0]-2][positions[i][1]] = "";
                    remove = true;
                    if (c.bonusOrNot()){
                        score += 30;
                    } else if (c.specialOrNot()){
                        score += 20;
                    } else {
                        score += 10;
                    }
                    combined[numOfCombined][0] = positions[i][0] - 1;
                    combined[numOfCombined][1] = positions[i][1];
                    numOfCombined += 1;
                    break;
                }
            } else if (c.getStructure() == AboveLeftRight){
                if ((positions[i][1]-1)>= 0 && positions[i][0]+1 <boardWidth &&
                        board[positions[i][0]][positions[i][1]] == c.getAbove() &&
                        board[positions[i][0]][positions[i][1] - 1] == c.getLeft() &&
                        board[positions[i][0] + 1][positions[i][1] - 1] == c.getRight()){
                    board[positions[i][0]][positions[i][1] - 1] = c.getCharacter();
                    combine_sound->play(); //************************
                    board[positions[i][0]][positions[i][1]] = "";
                    board[positions[i][0] + 1][positions[i][1] - 1] = "";
                    remove = true;
                    if (c.bonusOrNot()){
                        score += 30;
                    } else if (c.specialOrNot()){
                        score += 20;
                    } else {
                        score += 10;
                    }
                    combined[numOfCombined][0] = positions[i][0];
                    combined[numOfCombined][1] = positions[i][1] - 1;
                    numOfCombined += 1;
                    break;
                } else if (positions[i][0]-1 >=0 &&
                           board[positions[i][0]][positions[i][1]] == c.getRight() &&
                           board[positions[i][0] - 1][positions[i][1] + 1] == c.getAbove() &&
                           board[positions[i][0] - 1][positions[i][1]] == c.getLeft()){
                    board[positions[i][0] - 1][positions[i][1]] = c.getCharacter();
                    combine_sound->play(); //************************
                    board[positions[i][0]][positions[i][1]] = "";
                    board[positions[i][0] - 1][positions[i][1] + 1] = "";
                    remove = true;
                    if (c.bonusOrNot()){
                        score += 30;
                    } else if (c.specialOrNot()){
                        score += 20;
                    } else {
                        score += 10;
                    }
                    combined[numOfCombined][0] = positions[i][0] - 1;
                    combined[numOfCombined][1] = positions[i][1];
                    numOfCombined += 1;
                    break;
                } else if ((positions[i][1]-1)>= 0 && positions[i][0]-1>=boardWidth &&
                           board[positions[i][0]][positions[i][1]] == c.getAbove() &&
                           board[positions[i][0] - 1][positions[i][1] - 1] == c.getLeft() &&
                           board[positions[i][0]][positions[i][1] - 1] == c.getRight()){
                    board[positions[i][0]][current_y - 1] = c.getCharacter();
                    combine_sound->play(); //************************
                    board[positions[i][0]][current_y] = "";
                    board[positions[i][0] - 1][positions[i][1] - 1] = "";
                    remove = true;
                    if (c.bonusOrNot()){
                        score += 30;
                    } else if (c.specialOrNot()){
                        score += 20;
                    } else {
                        score += 10;
                    }
                    combined[numOfCombined][0] = positions[i][0];
                    combined[numOfCombined][1] = positions[i][1] - 1;
                    numOfCombined += 1;
                    break;
                } else if (positions[i][0]+1 <boardWidth &&
                           board[positions[i][0]][positions[i][1]] == c.getLeft() &&
                           board[positions[i][0] + 1][positions[i][1]] == c.getRight() &&
                           board[positions[i][0] + 1][positions[i][1] + 1] == c.getAbove()){
                    board[positions[i][0] + 1][positions[i][1]] = c.getCharacter();
                    combine_sound->play(); //************************
                    board[positions[i][0]][positions[i][1]] = "";
                    board[positions[i][0] + 1][positions[i][1] + 1] = "";
                    remove = true;
                    if (c.bonusOrNot()){
                        score += 30;
                    } else if (c.specialOrNot()){
                        score += 20;
                    } else {
                        score += 10;
                    }
                    combined[numOfCombined][0] = positions[i][0] + 1;
                    combined[numOfCombined][1] = positions[i][1];
                    numOfCombined += 1;
                    break;
                }
            } else if (c.getStructure() == LeftRightBelow){
                if (positions[i][1]-1>=0 && positions[i][0]+1<boardWidth &&
                        board[positions[i][0]][positions[i][1]] == c.getLeft() &&
                        board[positions[i][0] + 1][positions[i][1]] == c.getRight() &&
                        board[positions[i][0]][positions[i][1] - 1] == c.getBelow()){
                    board[positions[i][0]][positions[i][1] - 1] = c.getCharacter();
                    combine_sound->play(); //************************
                    board[positions[i][0]][positions[i][1]] = "";
                    board[positions[i][0] + 1][positions[i][1]] = "";
                    remove = true;
                    if (c.bonusOrNot()){
                        score += 30;
                    } else if (c.specialOrNot()){
                        score += 20;
                    } else {
                        score += 10;
                    }
                    combined[numOfCombined][0] = positions[i][0];
                    combined[numOfCombined][1] = positions[i][1] - 1;
                    numOfCombined += 1;
                    break;
                } else if (positions[i][1]-1>=0 && positions[i][0]-1>=0 &&
                           board[positions[i][0]][positions[i][1]] == c.getRight() &&
                           board[positions[i][0] - 1][positions[i][1]] == c.getLeft() &&
                           board[positions[i][0] - 1][positions[i][1] - 1] == c.getBelow()){
                    board[positions[i][0] - 1][positions[i][1] - 1] = c.getCharacter();
                    combine_sound->play(); //************************
                    board[positions[i][0]][positions[i][1]] = "";
                    board[positions[i][0] - 1][positions[i][1]] = "";
                    remove = true;
                    if (c.bonusOrNot()){
                        score += 30;
                    } else if (c.specialOrNot()){
                        score += 20;
                    } else {
                        score += 10;
                    }
                    combined[numOfCombined][0] = positions[i][0] - 1;
                    combined[numOfCombined][1] = positions[i][1] - 1;
                    numOfCombined += 1;
                    break;
                } else if (positions[i][1]-1>=0 && positions[i][0]+1<boardWidth &&
                           board[positions[i][0]][positions[i][1]] == c.getLeft() &&
                           board[positions[i][0] + 1][positions[i][1]] == c.getRight() &&
                           board[positions[i][0] + 1][positions[i][1] - 1] == c.getBelow()){
                    board[positions[i][0] + 1][positions[i][1] - 1] = c.getCharacter();
                    combine_sound->play(); //************************
                    board[positions[i][0]][positions[i][1]] = "";
                    board[positions[i][0] + 1][positions[i][1]] = "";
                    remove = true;
                    if (c.bonusOrNot()){
                        score += 30;
                    } else if (c.specialOrNot()){
                        score += 20;
                    } else {
                        score += 10;
                    }
                    combined[numOfCombined][0] = positions[i][0];
                    combined[numOfCombined][1] = positions[i][1] - 1;
                    numOfCombined += 1;
                    break;
                } else if (positions[i][1]-1>=0 && positions[i][0]-1>=0 &&
                           board[positions[i][0]][positions[i][1]] == c.getRight() &&
                           board[positions[i][0] - 1][positions[i][1]] == c.getLeft() &&
                           board[positions[i][0]][positions[i][1] - 1] == c.getBelow()){
                    board[positions[i][0]][positions[i][1] - 1] = c.getCharacter();
                    combine_sound->play(); //************************
                    board[positions[i][0]][positions[i][1]] = "";
                    board[positions[i][0] - 1][positions[i][1]] = "";
                    remove = true;
                    if (c.bonusOrNot()){
                        score += 30;
                    } else if (c.specialOrNot()){
                        score += 20;
                    } else {
                        score += 10;
                    }
                    combined[numOfCombined][0] = positions[i][0];
                    combined[numOfCombined][1] = positions[i][1] - 1;
                    numOfCombined += 1;
                    break;
                }
            } else if (c.getStructure() == AboveMiddleBelow){
                if (positions[i][1]-2>=0 &&
                        board[positions[i][0]][positions[i][1]] == c.getAbove() &&
                        board[positions[i][0]][positions[i][1] - 1] == c.getMiddle() &&
                        board[positions[i][0]][positions[i][1] - 2] == c.getBelow()){
                    board[positions[i][0]][positions[i][1] - 2] = c.getCharacter();
                    combine_sound->play(); //************************
                    board[positions[i][0]][positions[i][1]] = "";
                    board[positions[i][0]][positions[i][1] - 1] = "";
                    remove = true;
                    if (c.bonusOrNot()){
                        score += 30;
                    } else if (c.specialOrNot()){
                        score += 20;
                    } else {
                        score += 10;
                    }
                    combined[numOfCombined][0] = positions[i][0];
                    combined[numOfCombined][1] = positions[i][1] - 2;
                    numOfCombined += 1;
                    break;
                } else if (positions[i][1]-1>=0 &&
                           board[positions[i][0]][positions[i][1] - 1] == c.getBelow() &&
                           board[positions[i][0]][positions[i][1]] == c.getMiddle() &&
                           board[positions[i][0]][positions[i][1] + 1] == c.getAbove()){
                    board[positions[i][0]][positions[i][1]] = "";
                    board[positions[i][0]][positions[i][1] + 1] = "";
                    board[positions[i][0]][positions[i][1] - 1] = c.getCharacter();
                    combine_sound->play(); //************************
                    remove = true;
                    if (c.bonusOrNot()){
                        score += 30;
                    } else if (c.specialOrNot()){
                        score += 20;
                    } else {
                        score += 10;
                    }
                    combined[numOfCombined][0] = positions[i][0];
                    combined[numOfCombined][1] = positions[i][1] - 1;
                    numOfCombined += 1;
                    break;
                }
            } else if (c.getStructure() == LeftAboveBelow){
                if (positions[i][0]+1<boardWidth && positions[i][1]-1>=0 &&
                        board[positions[i][0]][positions[i][1]] == c.getLeft() &&
                        board[positions[i][0] + 1][positions[i][1]] == c.getAbove() &&
                        board[positions[i][0] + 1][positions[i][1] - 1] == c.getBelow()){
                    board[positions[i][0] + 1][positions[i][1] -1] = c.getCharacter();
                    combine_sound->play(); //************************
                    board[positions[i][0]][positions[i][1]] = "";
                    board[positions[i][0] + 1][positions[i][1]] = "";
                    remove = true;
                    if (c.bonusOrNot()){
                        score += 30;
                    } else if (c.specialOrNot()){
                        score += 20;
                    } else {
                        score += 10;
                    }
                    combined[numOfCombined][0] = positions[i][0];
                    combined[numOfCombined][1] = positions[i][1] - 1;
                    numOfCombined += 1;
                    break;
                } else if (positions[i][0]-1>=0 && positions[i][1] -1>=0 &&
                            board[positions[i][0]][positions[i][1]] == c.getAbove() &&
                            board[positions[i][0] - 1][positions[i][1]] == c.getLeft() &&
                            board[positions[i][0]][positions[i][1] - 1] == c.getBelow()){
                    board[positions[i][0]][positions[i][1] -1] = c.getCharacter();
                    combine_sound->play(); //************************
                    board[positions[i][0]][positions[i][1]] = "";
                    board[positions[i][0] - 1][positions[i][1]] = "";
                    remove = true;
                    if (c.bonusOrNot()){
                        score += 30;
                    } else if (c.specialOrNot()){
                        score += 20;
                    } else {
                        score += 10;
                    }
                    combined[numOfCombined][0] = positions[i][0];
                    combined[numOfCombined][1] = positions[i][1] - 1;
                    numOfCombined += 1;
                    break;
                } else if (positions[i][0]+1<boardWidth &&
                           board[positions[i][0]][positions[i][1]] == c.getLeft() &&
                           board[positions[i][0] + 1][positions[i][1] + 1] == c.getAbove() &&
                           board[positions[i][0] + 1][positions[i][1]] == c.getBelow()){
                    board[positions[i][0] + 1][positions[i][1]] = c.getCharacter();
                    combine_sound->play(); //************************
                    board[positions[i][0]][positions[i][1]] = "";
                    board[positions[i][0] + 1][positions[i][1] + 1] = "";
                    remove = true;
                    if (c.bonusOrNot()){
                        score += 30;
                    } else if (c.specialOrNot()){
                        score += 20;
                    } else {
                        score += 10;
                    }
                    combined[numOfCombined][0] = positions[i][0] + 1;
                    combined[numOfCombined][1] = positions[i][1];
                    numOfCombined += 1;
                    break;
                } else if (positions[i][0]-1>=0 && positions[i][1] -1>=0 &&
                           board[positions[i][0]][positions[i][1]] == c.getAbove() &&
                           board[positions[i][0] - 1][positions[i][1] - 1] == c.getLeft() &&
                           board[positions[i][0]][positions[i][1] - 1] == c.getBelow()){
                    board[positions[i][0]][positions[i][1] - 1] = c.getCharacter();
                    combine_sound->play(); //************************
                    board[positions[i][0]][positions[i][1]] = "";
                    board[positions[i][0] - 1][positions[i][1] - 1] = "";
                    remove = true;
                    if (c.bonusOrNot()){
                        score += 30;
                    } else if (c.specialOrNot()){
                        score += 20;
                    } else {
                        score += 10;
                    }
                    combined[numOfCombined][0] = positions[i][0];
                    combined[numOfCombined][1] = positions[i][1] - 1;
                    numOfCombined += 1;
                    break;
                }
            } else if (c.getStructure() == LeftRight){
                if ((positions[i][0]+1) < boardWidth && board[positions[i][0]][positions[i][1]] == c.getLeft()
                        && board[positions[i][0] + 1][positions[i][1]] == c.getRight()){
                    qDebug() << "Positions: "<< positions[i][0] << " " << positions[i][1]-1 << endl;
                    board[positions[i][0]][positions[i][1]] = c.getCharacter();
                    combine_sound->play(); //************************
                    board[positions[i][0] + 1][positions[i][1]] = "";
                    remove = true;
                    if (c.bonusOrNot()){
                        score += 30;
                    } else if (c.specialOrNot()){
                        score += 20;
                    } else {
                        score += 10;
                    }
                    combined[numOfCombined][0] = positions[i][0];
                    combined[numOfCombined][1] = positions[i][1];
                    numOfCombined += 1;
                    break;
                } else if ((positions[i][0]-1)>=0 && board[positions[i][0]][positions[i][1]] == c.getRight()
                           && board[positions[i][0] - 1][positions[i][1]] == c.getLeft()){
                    qDebug() << "Positions: "<< positions[i][0] << " " << positions[i][1]-1 << endl;
                    board[positions[i][0] - 1][positions[i][1]] = c.getCharacter();
                    combine_sound->play(); //************************
                    board[positions[i][0]][positions[i][1]] = "";
                    remove = true;
                    if (c.bonusOrNot()){
                        score += 30;
                    } else if (c.specialOrNot()){
                        score += 20;
                    } else {
                        score += 10;
                    }
                    combined[numOfCombined][0] = positions[i][0] - 1;
                    combined[numOfCombined][1] = positions[i][1];
                    numOfCombined += 1;
                    break;
                }
            } else if (c.getStructure() == AboveBelow){
                if (((positions[i][0]-1) >= 0) && board[positions[i][0]][positions[i][1]] == c.getAbove() &&
                        board[positions[i][0]][positions[i][1] - 1] == c.getBelow()){
                    qDebug() << "Positions: "<< positions[i][0] << " " << positions[i][1]-1 << endl;
                    board[positions[i][0]][positions[i][1] - 1] = c.getCharacter();
                    combine_sound->play(); //************************
                    board[positions[i][0]][positions[i][1]] = "";
                    remove = true;
                    if (c.bonusOrNot()){
                        score += 30;
                    } else if (c.specialOrNot()){
                        score += 20;
                    } else {
                        score += 10;
                    }
                    combined[numOfCombined][0] = positions[i][0];
                    combined[numOfCombined][1] = positions[i][1] - 1;
                    numOfCombined += 1;
                    break;
                }
           }
           j++;
        }
        i++;
    }
    if (remove){
        emit scoreAltered(score);
        waitingForAdjust = true;
        timer.start(500,this);
        current = ""; //避免current被画上去
        update();
    } else {
        waitingForAdjust = false;
        waitingForNewPiece = true;
        //timer.start(500,this);
    }
    qDebug()<<"removeCommbination"<< current<< current_x << current_y << endl;       /////////////////////////////////
}
