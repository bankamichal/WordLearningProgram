#include "loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent)
{

    stackedLayout = new QStackedLayout();
    centralW = new QWidget();
    DataBase::getInstance()->IdsOfUsers();

    pbLogin = new QPushButton("Login");
    pbRegister = new QPushButton("Register");
    pbCancel = new QPushButton("Exit");

    leLogin = new QLineEdit();
    lePassword = new QLineEdit();
    lePassword->setEchoMode(QLineEdit::Password);

    lLogin = new QLabel("Username");
    lPassword = new QLabel("Password");
    lMyGitHub = new QLabel("<a href=\"https://github.com/bankamichal\">My GitHub</a>");

    layoutMain = new QVBoxLayout();
    layoutLoginPass = new QGridLayout();
    layoutButtons = new QGridLayout();

    layoutButtons->addWidget(pbLogin,0,0);
    layoutButtons->addWidget(pbRegister,0,1);
    layoutButtons->addWidget(lMyGitHub,1,0);
    layoutButtons->addWidget(pbCancel,1,1);

    layoutLoginPass->addWidget(lLogin,0,0);
    layoutLoginPass->addWidget(leLogin,0,1);
    layoutLoginPass->addWidget(lPassword,1,0);
    layoutLoginPass->addWidget(lePassword,1,1);

    layoutMain->addLayout(layoutLoginPass);
    layoutMain->addLayout(layoutButtons);

    centralW->setLayout(layoutMain);
    setCentralWidget(centralW);


    connect(pbRegister, SIGNAL(clicked(bool)), this, SLOT(showRegisterWindow()));
    connect(pbCancel, SIGNAL(clicked(bool)), this, SLOT(closeLoginWindow()));
    connect(pbLogin, SIGNAL(clicked(bool)), this, SLOT(showMainMenu()));
}

void LoginWindow::showRegisterWindow()
{
    RegisterWindow* registerWindow = new RegisterWindow(0);
    registerWindow->show();
}

void LoginWindow::showMainMenu()
{
    if (DataBase::getInstance()->checkIfLoginAndPasswordCorrect(leLogin->text(),Encryption::encrypt(lePassword->text())))
    {
        PanelMainMenu* mainMenuWindow = new PanelMainMenu(0, leLogin->text());
        mainMenuWindow->show();
        this->close();
    }
    else
    {
        qDebug() << "Wrong password or login.";
        lePassword->setText("");
    }
}

void LoginWindow::closeLoginWindow()
{
    this->close();
}
