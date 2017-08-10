#ifndef LEARNINGWINDOW_H
#define LEARNINGWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QVector>
#include <QMessageBox>
//#include "word.h"
#include "database.h"

class LearningWindow : public QWidget
{
    Q_OBJECT
public:
    explicit LearningWindow(QWidget *parent = 0, QString login = "");
signals:

public slots:
    void randomWord();
    void refreshWindow();
    void check();
    void nextWord();
    void finishBtn();
private:
    bool finish;
    int goodAnswers;
    int totalAnswers;
    int amountOfAttempts;
    QString login;
    QLabel* lTitle;
    QLabel* lPl;
    QLabel* lEng;
    QLabel* lCategory;
    QLabel* lResult;
    QLabel* lAmount;
    QLineEdit* lePl;
    QLineEdit* leEng;
    QPushButton* pbCheck;
    QPushButton* pbNextWord;
    QPushButton* pbFinish;
    QGridLayout* layoutMain;
    Word word;
    QVector<Word> words;
    QVector<Word> knownWords;
    int idx;
    QMessageBox box;
};

#endif // LEARNINGWINDOW_H
