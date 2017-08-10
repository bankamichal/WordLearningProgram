#include "addwordwindow.h"

AddWordWindow::AddWordWindow(QWidget *parent) : QWidget(parent)
{
    pbAddWord = new QPushButton("Add word");
    pbClose = new QPushButton("Close");
    lePl = new QLineEdit();
    leEng = new QLineEdit();
    leCategory = new QLineEdit();

    lPl = new QLabel("Polish");
    lEng = new QLabel("English");
    lCategory = new QLabel("Category");

    layoutButtons = new QGridLayout();

    layoutButtons->addWidget(lPl,0,0);
    layoutButtons->addWidget(lePl,0,1,1,2);
    layoutButtons->addWidget(lEng,1,0);
    layoutButtons->addWidget(leEng,1,1,1,2);
    layoutButtons->addWidget(lCategory,2,0);
    layoutButtons->addWidget(leCategory,2,1,1,2);
    layoutButtons->addWidget(pbAddWord,3,0,1,2);
    layoutButtons->addWidget(pbClose,3,2,1,1);

    setLayout(layoutButtons);

    connect(pbAddWord, SIGNAL(clicked(bool)), this, SLOT(addWord()));
    connect(pbClose, SIGNAL(clicked(bool)), this, SLOT(closeWindow()));
}

void AddWordWindow::addWord()
{
    QVector<int> numberOfUsers = DataBase::getInstance()->IdsOfUsers();
    Word word;

    for (int i = 0 ; i < numberOfUsers.size(); i++)
    {
        word.setPl(lePl->text());
        word.setEng(leEng->text());
        word.setCategory(leCategory->text());
        word.setUser_id(numberOfUsers[i]);
        word.setResult(50);
        if (lePl->text() != "" && leEng->text() != "" && leCategory->text() != "")
        {
            DataBase::getInstance()->insertWord(word);
        }
        else
        {
            qDebug() << "Fill all lines!";
            break;
        }
    }



}

void AddWordWindow::closeWindow()
{
    this->close();
}
