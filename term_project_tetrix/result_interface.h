#ifndef RESULT_INTERFACE_H
#define RESULT_INTERFACE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
QT_END_NAMESPACE


class result_interface : public QWidget
{
    Q_OBJECT
public:
    result_interface();


signals:

public slots:
    void receiveYourScore(int score);
    void receiveOpScore(int score);
    void displayResult();

private:
    int yourScore;
    int oppoScore;
    QLCDNumber *yourScoreLcd;
    QLCDNumber *oppoScoreLcd;
    QLabel *createLabel(const QString &text);

};

#endif // RESULT_INTERFACE_H
