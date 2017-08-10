#include "panellogin.h"

PanelLogin::PanelLogin(QWidget *parent) : QWidget(parent)
{


    connect(pbLogin, SIGNAL(pressed()), this, SLOT(showMenu()));
}

void PanelLogin::showRegisterPanelPanel()
{
    RegisterWindow* registerWindow = new RegisterWindow(0);
    registerWindow->show();
}

void PanelLogin::closePanelLogin()
{
    window()->close();
}

void PanelLogin::showMenu()
{

}




