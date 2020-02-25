#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <map>
#include <QString>
using namespace std;

/* This enum type defines the 7 kinds of structures of Chinese
 * characters we will take into consideration
 */
enum Structure{LeftRight,AboveBelow,LeftMiddleRight,AboveLeftRight,LeftRightBelow,
              AboveMiddleBelow,LeftAboveBelow};

class Character{
public:

    /* Constructor */
    Character(){}

    /* Method: setComponent
     * ---------------------
     * This function sets the components of the character
     */
    void setComponent(QString Character="",QString Above="",QString Below="",
                      QString Left="",QString Right="",QString Middle="");

    /* Method: setStructure
     * --------------------
     * This function sets the structure of a character
     */
    void setStructure(QString Structure);  //设定结构

    /* Method: isSpecial
     * --------------------
     * This function sets the character to be special, namely
     * only belonging to that mode.
     */
    void isSpecial(){special=true;}  //是属于某一类的特定字

    /* Method: isBonus
     * --------------------
     * This function sets the character to be a bonus character, like "加"
     */
    void isBonus(){bonus=true;}  //是“加”这样的特殊字符

    /* Method: specialOrNot
     * ----------------------
     * This function returns a boolean to indicates
     *  whether it is a special character
     */
    bool specialOrNot(){return special;}  //判断是否是特定类的字

    /* Method: bonudOrNot
     * ------------------
     * This function returns a boolean to indicate whether
     * the character is a bonus one
     */
    bool bonusOrNot(){return bonus;}  //判断是否是加 增等

    /* The following are some get functions to return
     * the information about the character object
     */
    Structure getStructure(){return structure;}
    QString getCharacter(){return character;}
    QString getAbove(){return above;}
    QString getBelow(){return below;}
    QString getMiddle(){return middle;}
    QString getLeft(){return left;}
    QString getRight(){return right;}

private:
    QString character;
    QString above;
    QString below;
    QString left;
    QString right;
    QString middle;
    bool special=false;
    bool bonus=false;
    Structure structure;
};


/* These are the 3 character dictionaries, each for one mode */
extern map<QString,vector<Character>> dictHumanity;
extern map<QString,vector<Character>> dictBiology;
extern map<QString,vector<Character>> dictGeology;

#endif // CHARACTER_H
