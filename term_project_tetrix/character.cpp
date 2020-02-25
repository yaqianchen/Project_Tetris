#include "character.h"
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <QTextCodec>
#include <QString>
using namespace std;

/* Implementation notes: setComponent
 * ----------------------------------
 * This function sets the content of a character,
 * basically what this character and its components
 * are
 */
void Character::setComponent(QString Character,QString Above,QString Below,
                        QString Left,QString Right,QString Middle){
    character = Character;
    above = Above;
    below = Below;
    left = Left;
    right = Right;
    middle = Middle;
}

/* Implementation notes: setStructure
 * -----------------------------------
 * This function sets structure of a character
 */
void Character::setStructure(QString Structure){
    if (Structure == "上下"){
        structure = AboveBelow;
    } else if (Structure == "左右"){
        structure = LeftRight;
    } else if (Structure == "左中右"){
        structure = LeftMiddleRight;
    } else if (Structure == "上左右"){
        structure = AboveLeftRight;
    } else if (Structure == "左右下"){
        structure = LeftRightBelow;
    } else if (Structure == "上中下"){
        structure = AboveMiddleBelow;
    } else if (Structure == "左上下"){
        structure = LeftAboveBelow;
    }
}
