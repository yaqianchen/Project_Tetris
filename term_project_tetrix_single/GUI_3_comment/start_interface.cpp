#include "start_interface.h"

#include <qdebug.h>
#include <QString>


start_interface::start_interface(QWidget *parent) : QWidget(parent)
{

    game = new game_interface;
    score = new score_interface;
    board = new CharacterBoard;
    help = new help_interface;
    p_Player = new QMediaPlayer;
    p_Playlist = new QMediaPlaylist;

    QLabel *p_ImageLabel = new QLabel(this);
    QRadioButton *p_MusicButton = new QRadioButton(this);

    QPushButton *p_HelpButton = new QPushButton(this);
    QPushButton *p_BioButton = new QPushButton(this);
    QPushButton *p_GeoButton = new QPushButton(this);
    QPushButton *p_LitButton = new QPushButton(this);

    QString buttonStyle = "QPushButton:pressed{color:black;background:rgb(238,210,238);border-radius:10px;border-style:inset;}"
            "QPushButton{color:white;background:rgb(139,123,139);border-radius:10px;border-style:outset;}";

    p_BioButton->setFixedSize(150, 50);
    p_BioButton->setStyleSheet(buttonStyle);
    p_GeoButton->setFixedSize(150, 50);
    p_GeoButton->setStyleSheet(buttonStyle);
    p_LitButton->setFixedSize(150, 50);
    p_LitButton->setStyleSheet(buttonStyle);
    p_HelpButton->setFixedSize(150, 50);
    p_HelpButton->setStyleSheet(buttonStyle);

    // 主题图传入
//    QPixmap pixmap("/Users/apple/Desktop/GUI_3/WechatIMG209.jpeg");
    QPixmap pixmap(":/images/Title.jpeg");
    p_ImageLabel->setFixedSize(300, 90);
    p_ImageLabel->setPixmap(pixmap);
    p_ImageLabel->setScaledContents(true);

    // 按钮文本
    p_MusicButton->setText(QStringLiteral("Music"));
    p_MusicButton->setStyleSheet("QRadioButton{color:black}");
    p_HelpButton->setText(QStringLiteral("Help"));
    p_BioButton->setText(QStringLiteral("Biology Mode"));
    p_GeoButton->setText(QStringLiteral("Geology Mode"));
    p_LitButton->setText(QStringLiteral("Literature Mode"));

    QGridLayout *pLayout = new QGridLayout();
    // 主题图
    pLayout->addWidget(p_ImageLabel, 0, 0, 2, 1);
    // biology mode
    pLayout->addWidget(p_BioButton, 2, 2, 1, 1);
    // geology mode
    pLayout->addWidget(p_GeoButton,3, 2, 1, 1);
    // literature mode
    pLayout->addWidget(p_LitButton, 4, 2, 1, 1);
    // 帮助
    pLayout->addWidget(p_HelpButton, 5, 2, 1, 1);
    // 音乐
    pLayout->addWidget(p_MusicButton, 0, 2, 1, 1, Qt::AlignRight | Qt::AlignTop);

    // 设置水平间距
    pLayout->setHorizontalSpacing(40);
    // 设置垂直间距
    pLayout->setVerticalSpacing(10);
    // 设置外间距
    pLayout->setContentsMargins(30, 30, 30, 30);
    setLayout(pLayout);

    //music signal connection
    connect(p_MusicButton, SIGNAL(clicked(bool)), this, SLOT(MusicState(bool)));

    //modes signal connection
    p_BioButton->setObjectName("Bio");
    p_GeoButton->setObjectName("Geo");
    p_LitButton->setObjectName("Lit");
    connect(p_BioButton, &QPushButton::clicked, game, &game_interface::displayGame);
//    connect(p_BioButton, &QPushButton::clicked, score, &score_interface::determineMode); //****************delete
    connect(p_BioButton, &QPushButton::clicked, board, &CharacterBoard::mode_selection);

    connect(p_GeoButton, &QPushButton::clicked, game, &game_interface::displayGame);
//    connect(p_GeoButton, &QPushButton::clicked, score, &score_interface::determineMode); //****************delete
    connect(p_GeoButton, &QPushButton::clicked, board, &CharacterBoard::mode_selection);

    connect(p_LitButton, &QPushButton::clicked, game, &game_interface::displayGame);
//    connect(p_LitButton, &QPushButton::clicked, score, &score_interface::determineMode); //****************delete
    connect(p_LitButton, &QPushButton::clicked, board, &CharacterBoard::mode_selection);

    //test
    connect(p_HelpButton, &QPushButton::clicked, help, &help_interface::displayHelp);

}

start_interface::~start_interface(){
}


// music slot
void start_interface::MusicState(bool state){
    p_Playlist->addMedia(QUrl("qrc:/sounds/bgm.mp3"));
    p_Playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    p_Playlist->setCurrentIndex(1);
    p_Player->setPlaylist(p_Playlist);
    p_Player->setVolume(80);

    if (state) {
        p_Player->play();
    }
    else {
        p_Player->pause();
    }
}


//void start_interface::ModeSlot(){
//    hide();
//    game = new game_interface();
//    game->show();
//}
