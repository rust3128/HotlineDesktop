#include "dynamiicbutton.h"

DynamiicButton::DynamiicButton(int clientID, QWidget *parent) :
    QPushButton(parent)
{
    buttonID = clientID;
}

int DynamiicButton::getButtonID()
{
    return buttonID;
}
