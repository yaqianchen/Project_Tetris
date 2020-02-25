#include "client_server_interface.h"
#include <qdebug.h>
#include <QString>

/*
 * File: client_server_interface.cpp
 * ---------------------------
 * This file implements the interface for players to choose if they want to be client or server during the network
 */

/*
 * Implementation notes：client_server_interface
 * -----------------------------------------------------
 * This function is used initialize the client_server_interface class including
 * GUI, connection between buttons and signals and jump to another interface
 */

client_server_interface::client_server_interface(QWidget *parent) : QWidget(parent)
{

    start = new start_interface;
    game = new game_interface;
    client_test = new client;
    server_test = new server;
    score = new score_interface;
    QLabel *p_ImageLabel = new QLabel(this);


    QPushButton *p_client = new QPushButton(this);
    QPushButton *p_server = new QPushButton(this);

    QString buttonStyle = "QPushButton:pressed{color:black;background:rgb(238,210,238);border-radius:10px;border-style:inset;}"
            "QPushButton{color:white;background:rgb(139,123,139);border-radius:10px;border-style:outset;}";

    p_client->setFixedSize(150, 50);
    p_client->setStyleSheet(buttonStyle);
    p_server->setFixedSize(150, 50);
    p_server->setStyleSheet(buttonStyle);


    // 主题图传入
    QPixmap pixmap(":/images/Title.jpeg");
    p_ImageLabel->setFixedSize(300, 90);
    p_ImageLabel->setPixmap(pixmap);
    p_ImageLabel->setScaledContents(true);

    // 按钮文本
    p_client->setText(QStringLiteral("client"));
    p_server->setText(QStringLiteral("server"));

    QGridLayout *pLayout = new QGridLayout();
    // 主题图
    pLayout->addWidget(p_ImageLabel, 0, 0, 2, 1);
    // biology mode
    pLayout->addWidget(p_client, 2, 2, 1, 1);
    // geology mode
    pLayout->addWidget(p_server,3, 2, 1, 1);
    // literature mode

    // 设置水平间距
    pLayout->setHorizontalSpacing(40);
    // 设置垂直间距
    pLayout->setVerticalSpacing(10);
    // 设置外间距
    pLayout->setContentsMargins(30, 30, 30, 30);
    setLayout(pLayout);

    p_client->setObjectName("Client");
    p_server->setObjectName("Server");
//    p_LitButton->setObjectName("Lit");
    connect(p_client, &QPushButton::clicked, client_test, &client::displayClient);
    connect(p_server, &QPushButton::clicked, server_test, &server::displaySever);

}
/*
 * Implementation notes：~client_server_interface
 * -----------------------------------------------------
 * This function is used to delete the interface
 */
client_server_interface::~client_server_interface(){
}

