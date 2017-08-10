#include "editwordswindow.h"

EditWordsWindow::EditWordsWindow(QWidget *parent,QString login) : QWidget(parent)
{
    listOfWords = new QTableWidget();
    layoutButtons = new QGridLayout();
    this->login = login;



    pbAddWord = new QPushButton("Add word");
    pbDefaultWords = new QPushButton("Set default base of words");
    pbDeleteWords = new QPushButton("Delete all words");
    lePl = new QLineEdit();
    leEng = new QLineEdit();
    leCategory = new QLineEdit();
    lPl = new QLabel("Polish");
    lEng = new QLabel("English");
    lCategory = new QLabel("Category");
    lAdminInfo = new QPushButton("!");
    lAdminInfo->setStyleSheet("color: rgb(255, 0,0)");

    layoutButtons->addWidget(lPl,1,0);
    layoutButtons->addWidget(lePl,1,1);
    layoutButtons->addWidget(pbAddWord,1,2,1,2);
    layoutButtons->addWidget(lEng,2,0);
    layoutButtons->addWidget(leEng,2,1);
    layoutButtons->addWidget(lCategory,3,0);
    layoutButtons->addWidget(leCategory,3,1);
    layoutButtons->addWidget(pbDeleteWords, 3,2,1,2);
    layoutButtons->addWidget(listOfWords, 5,0,1,4);

    if (login == "admin")
    {
        pbDefaultWords->setDisabled(true);
        lAdminInfo->setToolTip("<font color=\"red\">You are admin. If normal user press 'Set default base of words' button, they will set your words' base.</font>");
        layoutButtons->addWidget(pbDefaultWords, 2,2,1,1);
        layoutButtons->addWidget(lAdminInfo,2,3,1,1);
    }
    else
    {
        layoutButtons->addWidget(pbDefaultWords, 2,2,1,2);
    }
    refreshWords();
    connect(pbDeleteWords, SIGNAL(clicked(bool)), this, SLOT(deleteAllwords()));
    connect(pbDefaultWords, SIGNAL(clicked(bool)), this, SLOT(defaultWords()));
    connect(pbAddWord, SIGNAL(clicked(bool)), this, SLOT(addWord()));

    resize(540,300);
    setLayout(layoutButtons);
}

void EditWordsWindow::addWord()
{
    Word word(lePl->text(), leEng->text(),leCategory->text(), 50, DataBase::getInstance()->getIdOfKnownLogin(login));

        if (lePl->text() != "" && leEng->text() != "" && leCategory->text() != "")
        {
            DataBase::getInstance()->insertWord(word);
            lePl->setText("");
            leEng->setText("");
            leCategory->setText("");
        }
        else
        {
            qDebug() << "Fill all lines!";
        }
        refreshWords();
}

void EditWordsWindow::defaultWords()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Set default base");
    msgBox.setText("Are you sure?");
    msgBox.setStandardButtons(QMessageBox::No);
    msgBox.addButton(QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::Yes){
        DataBase::getInstance()->defaultWordBase(login);
        refreshWords();
    }

}

void EditWordsWindow::refreshWords()
{
    QVector<Word> words = DataBase::getInstance()->getWords(DataBase::getInstance()->getIdOfKnownLogin(login));

    listOfWords->clear();
    listOfWords->setRowCount(words.size());
    listOfWords->setColumnCount(5);
    QVector<QPushButton*> pb;
    QSignalMapper* signalMapper = new QSignalMapper (this) ;

    for (int i = 0; i < words.size(); i++)
    {
        pb.push_back(new QPushButton("Delete"));
        listOfWords->setHorizontalHeaderItem(0,new QTableWidgetItem("Polish"));
        listOfWords->setHorizontalHeaderItem(1,new QTableWidgetItem("English"));
        listOfWords->setHorizontalHeaderItem(2,new QTableWidgetItem("Category"));
        listOfWords->setHorizontalHeaderItem(3,new QTableWidgetItem("Result"));
        listOfWords->setHorizontalHeaderItem(4,new QTableWidgetItem(""));
        listOfWords->setColumnWidth(4,100);
        listOfWords->setItem(i,0, new QTableWidgetItem(words[i].getPl()));
        listOfWords->setItem(i,1,new QTableWidgetItem(words[i].getEng()));
        listOfWords->setItem(i,2,new QTableWidgetItem(words[i].getCategory()));
        listOfWords->setItem(i,3,new QTableWidgetItem(QString::number(words[i].getResult())));
        listOfWords->setCellWidget(i,4, pb[i]);

        connect(pb[i], SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
        signalMapper->setMapping (pb[i], words[i].getId()) ;
    }
    connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(deleteWords(int)));
}

void EditWordsWindow::deleteAllwords()
{

    QMessageBox msgBox;
    msgBox.setWindowTitle("Delete all words");
    msgBox.setText("Are you sure?");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::Yes){
        DataBase::getInstance()->deleteAllWords(login);
        refreshWords();
    }

}

void EditWordsWindow::deleteWords(int a)
{
    DataBase::getInstance()->deleteWord(a);
    refreshWords();
}
