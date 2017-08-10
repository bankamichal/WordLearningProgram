#include "repeatwindow.h"

RepeatWindow::RepeatWindow(QWidget *parent, const QString& login) : QWidget(parent)
{
    finish = false;

    words = DataBase::getInstance()->getNWorstWords(5,DataBase::getInstance()->getIdOfKnownLogin(login));
    amountOfAttempts = 0;
    totalAnswers = 0;
    goodAnswers = 0;
    knownWords.clear();

    this->login = login;
    lTitle = new QLabel("Repeating mode (5 the worst words)");
    lTitle->setStyleSheet("font-weight: bold;");
    lPl = new QLabel("Polish");
    lEng = new QLabel("English");
    lCategory = new QLabel("Category");
    lePl = new QLineEdit();
    leEng = new QLineEdit();
    lResult = new QLabel();
    lAmount = new QLabel();
    leEng->setReadOnly(true);

    pbCheck = new QPushButton("Check!");
    pbNextWord = new QPushButton("Next word...");
    pbFinish = new QPushButton("Finish");
    layoutMain = new QGridLayout();

    layoutMain->addWidget(lTitle,0,0,1,3,Qt::AlignCenter);
    layoutMain->addWidget(lCategory,1,0,1,3,Qt::AlignCenter);
    layoutMain->addWidget(lEng,2,0);
    layoutMain->addWidget(leEng,2,1,1,2);
    layoutMain->addWidget(lPl,3,0);
    layoutMain->addWidget(lePl,3,1,1,2);
    layoutMain->addWidget(pbCheck,4,1);
    layoutMain->addWidget(pbNextWord,5,0,1,3,Qt::AlignCenter);
    layoutMain->addWidget(lResult,6,0,Qt::AlignCenter);
    layoutMain->addWidget(lAmount,6,1,1,2,Qt::AlignCenter);
    layoutMain->addWidget(pbFinish,7,0,1,3);
    randomWord();
    refreshWindow();

    connect(pbCheck, SIGNAL(clicked(bool)), this, SLOT(check()));
    connect(pbNextWord, SIGNAL(clicked(bool)), this, SLOT(nextWord()));
    connect(pbFinish, SIGNAL(clicked(bool)), this, SLOT(finishBtn()));

    setLayout(layoutMain);
}

void RepeatWindow::randomWord()
{
    int idxOfWord;
    if (words.size() != 0 && finish == false)
    {
        idxOfWord = rand() % words.size();
        idx = idxOfWord;
        amountOfAttempts = 0;
        lAmount->setText("You didn't try yet.");
        leEng->setText(words[idxOfWord].getEng());
        lCategory->setText("Category: " + words[idxOfWord].getCategory());
        this->word = words[idxOfWord];
    }
    else
    {
        double avrg = 0;
        foreach (Word w, knownWords) {
            avrg += w.getResult();
        }
        avrg /= knownWords.size();
        int a = (double)goodAnswers / (double)totalAnswers * 100.0;

        if(finish == false)
        {
            if (words.size() == 0)
            {
                box.setText("No more words to repeat.\n"
                            "YOUR STATISTICS\n"
                            "-Averge result: " + QString::number(avrg) + "%\n"
                            "-Good answers in this try: " + QString::number(a) + "%\n");
                box.exec();
            }
        }
        else
        {
            if(totalAnswers == 0)
            {
                box.setText("You finished.\n"
                            "YOUR STATISTICS\n"
                            "-Averge result: 0%\n"
                            "-Good answers in this try: 0%\n");
                box.exec();
            }
            else
            {
                box.setText("You finished.\n"
                            "YOUR STATISTICS\n"
                            "-Averge result: " + QString::number(avrg) + "%\n"
                            "-Good answers in this try: " + QString::number(a) + "%\n");
                box.exec();
            }
        }
        this->close();
    }
}

void RepeatWindow::refreshWindow()
{
    lResult->setText("Word result: " + QString::number(word.getResult()));
    if (amountOfAttempts <= 0)
    {
        pbNextWord->setText("You must try at least once to skip word");
        pbNextWord->setDisabled(true);
    }
    else
    {
        pbNextWord->setText("Next word");
        pbNextWord->setDisabled(false);
    }
}

void RepeatWindow::check()
{
    amountOfAttempts++;
    if (lePl->text().toLower() == word.getPl().toLower())
    {
       totalAnswers++;
       goodAnswers++;
       switch (amountOfAttempts)
       {
       case 1:
           if (word.getResult() <= 95)
           {
                word.setResult(word.getResult()+5);
                DataBase::getInstance()->changeResultWord(word.getId(),5);
                box.setText("Correct!\nYou tried " + QString::number(amountOfAttempts) + " time.\n+5 points.");
           }
           else
           {
               int x = 100-word.getResult();
               DataBase::getInstance()->changeResultWord(word.getId(),100-word.getResult());
               box.setText("Correct!\nYou tried " + QString::number(amountOfAttempts) + " time.\n+" + x + " points.");
               word.setResult(100);
           }
           break;

       case 2:
           if(word.getResult() <= 97)
           {
                word.setResult(word.getResult()+3);
                DataBase::getInstance()->changeResultWord(word.getId(),3);
                box.setText("Correct!\nYou tried " + QString::number(amountOfAttempts) + " times.\n+3 points.");
           }
           else
           {
               int x = 100-word.getResult();
               DataBase::getInstance()->changeResultWord(word.getId(),100-word.getResult());
               box.setText("Correct!\nYou tried " + QString::number(amountOfAttempts) + " time.\n+" + x + " points.");
               word.setResult(100);
           }
           break;

       case 3:
           if(word.getResult() <= 99)
           {
                word.setResult(word.getResult()+1);
                DataBase::getInstance()->changeResultWord(word.getId(),1);
                box.setText("Correct!\nYou tried " + QString::number(amountOfAttempts) + " times.\n+1 point.");
           }
           else
           {
               int x = 100-word.getResult();
               DataBase::getInstance()->changeResultWord(word.getId(),100-word.getResult());
               box.setText("Correct!\nYou tried " + QString::number(amountOfAttempts) + " time.\n+" + x + " points.");
               word.setResult(100);
           }
           break;
       default:
           box.setText("Correct!\nYou tried " + QString::number(amountOfAttempts) + " times.\nIt didn't give you any points.");
           break;
       }
       knownWords.push_back(word);
       words.erase(words.begin() + idx);
       lePl->setText("");
       box.exec();
       randomWord();
       amountOfAttempts = 0;
       refreshWindow();
    }
    else
    {
        totalAnswers++;
        if (word.getResult() >= 3)
        {
            word.setResult(word.getResult()-3);
            DataBase::getInstance()->changeResultWord(word.getId(),-3);
            lAmount->setText("You tried " + QString::number(amountOfAttempts) + ". times.");
            box.setText("Wrong, -3 points!");
            box.exec();
        }
        else
        {

            DataBase::getInstance()->changeResultWord(word.getId(),word.getResult()*(-1));
            lAmount->setText("You tried " + QString::number(amountOfAttempts) + ". times.");
            box.setText("Wrong, -" + QString::number(word.getResult()) + " points!");
            box.exec();
            word.setResult(0);
        }
        refreshWindow();
    }
}

void RepeatWindow::nextWord()
{
    if(words.size() > 1)
    {
        randomWord();
        refreshWindow();
    }
    else
    {
        box.setText("This is the last word in base.");
        box.exec();
    }

}

void RepeatWindow::finishBtn()
{
    finish = true;
    randomWord();
}
