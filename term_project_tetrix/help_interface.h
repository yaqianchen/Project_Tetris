#ifndef HELP_INTERFACE_H
#define HELP_INTERFACE_H

#include <QWidget>

class help_interface : public QWidget
{
    Q_OBJECT
public:
    explicit help_interface(QWidget *parent = nullptr);

signals:

public slots:
    void displayHelp();

private:


};

#endif // HELP_INTERFACE_H
