#include "mainwindow.h"

mainwindow::mainwindow(QWidget *parent) : QMainWindow(parent)
{
    panelLogin = new PanelLogin(this);
    panelMainMenu = new PanelMainMenu(this);
    stackedLayout = new QStackedLayout();
    stackedLayout->addWidget(panelLogin);
    stackedLayout->addWidget(panelMainMenu);
    centralW = new QWidget();
    centralW->setLayout(stackedLayout);
    setCentralWidget(centralW);
    //idx: 0 - panelLogin
    //1 - panelmainMenu
}

void mainwindow::setCurrentLayoutToMainMenu()
{
    //idx: 0 - panelLogin
    //1 - panelmainMenu
    stackedLayout->setCurrentIndex(1);
}


