#ifndef DYNAMIICBUTTON_H
#define DYNAMIICBUTTON_H

#include <QCommandLinkButton>
#include <QPushButton>

class DynamiicButton : public QPushButton
{
public:
    explicit DynamiicButton(int clientID, QWidget *parent = nullptr);
    int getButtonID();
private:
    int buttonID=0;
};

#endif // DYNAMIICBUTTON_H
