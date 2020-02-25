#include "score_interface.h"
#include <QtWidgets>

score_interface::score_interface()
{

    scoreLCD = new QLCDNumber(4);
    scoreLCD->setFixedSize(300,65);
    scoreLCD->setDecMode();
    scoreLCD->setSegmentStyle(QLCDNumber::Filled);
    scoreLCD->setStyleSheet("QLCDNumber{color:black;background:white;border:white}");

    QVBoxLayout * vlayout = new QVBoxLayout(this);
    vlayout->addWidget(scoreLCD,0,Qt::AlignCenter|Qt::AlignBottom);
    vlayout->addSpacing(310);

    setLayout(vlayout);

    setMaximumSize(700,600);
    setMinimumSize(700,600);

    setAutoFillBackground(true);

}

void score_interface::determineScore(int passed_score)
{
    score = passed_score;
}

void score_interface::displayScore(int score)
{
    QPalette scorePal = this->palette();
    scoreLCD->display(score);
    if (score <= 10 && score >=0){
        scorePal.setBrush(QPalette::Background,QBrush(QPixmap(":/images/geo_bronze.png")));
    } else if (score > 10 && score <= 30){
        scorePal.setBrush(QPalette::Background,QBrush(QPixmap(":/images/geo_gold.png")));
    } else if(score > 30){
        scorePal.setBrush(QPalette::Background,QBrush(QPixmap(":/images/geo_diamond.png")));
    }
    setPalette(scorePal);
    this->show();
}

void score_interface::gameStop(bool state)
{
    if (state == true){
        displayScore(score);
    }
}
