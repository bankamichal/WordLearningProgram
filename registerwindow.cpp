#include "registerwindow.h"

RegisterWindow::RegisterWindow(QWidget *parent) : QWidget(parent)
{
    btnRegister = new QPushButton("Register");
    btnCancel = new QPushButton("Cancel");

    leName = new QLineEdit();
    leSurname = new QLineEdit();
    leAge = new QLineEdit();
    leUsername = new QLineEdit();
    lePassword = new QLineEdit();
    lePassword->setEchoMode(QLineEdit::Password);

    lName = new QLabel("Name");
    lSurname = new QLabel("Surname");
    lAge = new QLabel("Age");
    lUsername = new QLabel("Username");
    lPassword = new QLabel("Password");

    layoutFields = new QGridLayout();
    layoutOperationButtons =new QHBoxLayout();
    layoutMain =new QVBoxLayout();

    layoutFields->addWidget(lName,0,0);
    layoutFields->addWidget(leName,0,1);
    layoutFields->addWidget(lSurname,1,0);
    layoutFields->addWidget(leSurname,1,1);
    layoutFields->addWidget(lAge,2,0);
    layoutFields->addWidget(leAge,2,1);
    layoutFields->addWidget(lUsername,3,0);
    layoutFields->addWidget(leUsername,3,1);
    layoutFields->addWidget(lPassword,4,0);
    layoutFields->addWidget(lePassword,4,1);

    layoutOperationButtons->addWidget(btnRegister);
    layoutOperationButtons->addWidget(btnCancel);

    layoutMain->addLayout(layoutFields);
    layoutMain->addLayout(layoutOperationButtons);

    setLayout(layoutMain);

    connect(btnCancel, SIGNAL(clicked(bool)), this, SLOT(closeWindow()));
    connect(btnRegister, SIGNAL(clicked(bool)), this, SLOT(registerNewUser()));
}

void RegisterWindow::closeWindow()
{
    this->close();
}

void RegisterWindow::registerNewUser()
{
    if (leName->text().length() >= 1 && leSurname->text().length() >= 1 && leAge->text().toInt() > 0 && lePassword->text().length() >= 5 && leUsername->text().length() >= 5)
    {
        User newUser(leName->text(), leSurname->text(), leAge->text().toInt(), Encryption::encrypt(lePassword->text()), leUsername->text());
        if (!DataBase::getInstance()->checkIfUserExists(newUser.getUsername()))
        {
            DataBase::getInstance()->insertUser(newUser);
            this->close();
        }
        else
        {
            QMessageBox* msgBox = new QMessageBox();
            msgBox->setText("This username is taken.\nTry diffrent one.");
            leName->setText("");
            leSurname->setText("");
            leAge->setText("");
            lePassword->setText("");
            leUsername->setText("");
            msgBox->show();
        }
    }
    else
    {
        QMessageBox* msgBox = new QMessageBox();
        msgBox->setText("You must fill all labels correctly\n"
                        "   -At least 5 characters in username and password.\n"
                        "   -Age at least 1.\n"
                        "   -Not empty name and surname.");
        msgBox->show();
    }
}
