#include "result_interface.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QtWidgets>

result_interface::result_interface()
{
}

void result_interface::displayResult()
{
    setMaximumSize(700,600);
    setMinimumSize(700,600);

    //display score
    yourScoreLcd = new QLCDNumber(3);
    yourScoreLcd->setFixedSize(200,65);
    yourScoreLcd->setDecMode();
    yourScoreLcd->setSegmentStyle(QLCDNumber::Filled);
    yourScoreLcd->setStyleSheet("QLCDNumber{color:black;background:white;border:white}");

    oppoScoreLcd = new QLCDNumber(3);
    oppoScoreLcd->setFixedSize(200,65);
    oppoScoreLcd->setDecMode();
    oppoScoreLcd->setSegmentStyle(QLCDNumber::Filled);
    oppoScoreLcd->setStyleSheet("QLCDNumber{color:black;background:white;border:white}");

    //layout
    QVBoxLayout *vlayout = new QVBoxLayout;
    QHBoxLayout *h0layout = new QHBoxLayout;
    QHBoxLayout *h1layout = new QHBoxLayout;
    vlayout->addLayout(h0layout);
    h0layout->addWidget(createLabel(tr("YOUR SCORE:")),yourScore,Qt::AlignCenter);
    h0layout->addWidget(createLabel(tr("OPPONENT'S SCORE:")),oppoScore,Qt::AlignCenter);
    vlayout->addLayout(h1layout);
    h1layout->addWidget(yourScoreLcd,yourScore,Qt::AlignCenter);
    h1layout->addWidget(oppoScoreLcd,oppoScore,Qt::AlignCenter);
    vlayout->addSpacing(300);
    setLayout(vlayout);

    qDebug()<<"displayyyyyyyyyy,your score:"<<yourScore<<"dis"<<oppoScore<<endl;
    QPalette resultPal = this->palette();
    if (yourScore < oppoScore){
        resultPal.setBrush(QPalette::Background,QBrush(QPixmap(":/images/LOSE.jpeg ")));
    }
    if (yourScore > oppoScore){
        resultPal.setBrush(QPalette::Background,QBrush(QPixmap(":/images/WIN.jpeg ")));
    }
    if (yourScore == oppoScore){
        resultPal.setBrush(QPalette::Background,QBrush(QPixmap(":/images/DRAW.jpeg ")));
    }
    setPalette(resultPal);
    this->show();
}

QLabel *result_interface::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    label->setFixedHeight(30);
    label->setStyleSheet("QLabel{color:green}");
    return label;
}

void result_interface::receiveOpScore(int opScore){
    qDebug()<<"receiveOpScore:"<<opScore<<endl;
    oppoScore = opScore;
}

void result_interface::receiveYourScore(int yourS){
    qDebug()<<"receive your score"<<yourScore<<endl;
    yourScore = yourS;
}
