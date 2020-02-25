#include "help_interface.h"

help_interface::help_interface(QWidget *parent) : QWidget(parent)
{
    setMaximumSize(700, 600);
    setMinimumSize(700, 600);
    setAutoFillBackground(true);
}

void help_interface::displayHelp(){
    QPalette instruction = this->palette();
    instruction.setBrush(QPalette::Background, QBrush(QPixmap(":/images/help.png")));
    setPalette(instruction);
    this->show();
}
