#include "game_interface.h"
#include "character_board.h"
#include <QGridLayout>
#include <QtWidgets>
#include <QPushButton>
#include <QHBoxLayout>

game_interface::game_interface()
{
    board = new CharacterBoard;

    board->setFixedSize(300,300);

    //buttons
    //set button style
    QString buttonStyle = "QPushButton:pressed{color:black;background:rgb(238,210,238);border-radius:10px;border-style:inset;}"
            "QPushButton{color:white;background:rgb(139,123,139);border-radius:10px;border-style:outset;}";

    startPauseButton = new QPushButton(tr("&Start / Pause"));
    startPauseButton->setFocusPolicy(Qt::NoFocus);
    startPauseButton->setStyleSheet(buttonStyle);
    startPauseButton->setFixedSize(125,40);

    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);
    quitButton->setStyleSheet(buttonStyle);
    quitButton->setFixedSize(125,40);

    downButton = new QPushButton(tr("&Down"));
    downButton->setFocusPolicy(Qt::NoFocus);
    downButton->setStyleSheet(buttonStyle);
    downButton->setFixedSize(125,40);

    leftButton = new QPushButton(tr("&Left"));
    leftButton->setFocusPolicy(Qt::NoFocus);
    leftButton->setStyleSheet(buttonStyle);
    leftButton->setFixedSize(125,40);

    rightButton = new QPushButton(tr("&Right"));
    rightButton->setFocusPolicy(Qt::NoFocus);
    rightButton->setStyleSheet(buttonStyle);
    rightButton->setFixedSize(125,40);


    //foreshow
    foreshowLabel = new QLabel;
    foreshowLabel->setFrameStyle(QFrame::Box | QFrame::Sunken);
    foreshowLabel->setFixedSize(300,70);
    foreshowLabel->setAlignment(Qt::AlignCenter);
    foreshowLabel->setStyleSheet("QLabel{background:white}");
    board->setNextPieceLabel(foreshowLabel);


    //LCD
    scoreLcd = new QLCDNumber(4);
    scoreLcd->setFixedSize(300,70);
    scoreLcd->setDecMode();
    scoreLcd->setSegmentStyle(QLCDNumber::Filled);
    scoreLcd->setStyleSheet("QLCDNumber{color:black;background:white}");

    //connection
    connect(quitButton,&QPushButton::clicked,qApp,&QApplication::quit);

    connect(board,&CharacterBoard::scoreAltered,
            scoreLcd, QOverload<int>::of(&QLCDNumber::display));
    connect(startPauseButton,&QPushButton::clicked,board,&CharacterBoard::start);

    //layout
    QGridLayout *layout = new QGridLayout;
    QHBoxLayout *hlayout = new QHBoxLayout;
    layout->addWidget(board,0,0,8,1);
    layout->addWidget(createLabel(tr("NEXT")),0,1);
    layout->addWidget(foreshowLabel,1,1);
    layout->addWidget(createLabel(tr("SCORE")),2,1);
    layout->addWidget(scoreLcd,3,1);
    layout->addLayout(hlayout,4,1);
    hlayout->addWidget(leftButton,0,Qt::AlignCenter); // center: no white space
    hlayout->addWidget(rightButton,0,Qt::AlignCenter);
    layout->addWidget(downButton,5,1,Qt::AlignCenter);
    layout->addWidget(startPauseButton,6,1,Qt::AlignCenter);
    layout->addWidget(quitButton,7,1,Qt::AlignCenter);
    setLayout(layout);

    //window interface
    setWindowTitle(tr("Playing"));
    setAutoFillBackground(true);
    QPalette gamePal = this->palette();
    gamePal.setBrush(QPalette::Background,QBrush(QPixmap(":/images/Background.png")));
    setPalette(gamePal);
    setMaximumSize(700,600);
    setMinimumSize(700,600);
    connect(board,&CharacterBoard::isEnd,this,&game_interface::board_game);
}


void game_interface::board_game(){
    score = board->score;
    emit game_start();
}

QLabel *game_interface::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    label->setFixedHeight(30);
    label->setStyleSheet("QLabel{color:black}");
    return label;
}

void game_interface::displayGame()
{
    this->show();
}
