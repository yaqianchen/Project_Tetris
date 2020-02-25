#include "widget.h"
#include <QApplication>
#include "game_interface.h"
#include "start_interface.h"
#include "score_interface.h"
#include "client_server_interface.h"
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    client_server_interface widget;
// 背景图
    widget.setAutoFillBackground(true);
    QPalette pal = widget.palette();
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/images/Background.png")));
    widget.setPalette(pal);
    // 设定尺寸
    widget.resize(700, 600);
    // 设定透明度
    widget.setWindowOpacity(0.95);
    // 显示
    widget.show();
    return a.exec();
}
