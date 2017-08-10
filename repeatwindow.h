#ifndef REPEATWINDOW_H
#define REPEATWINDOW_H

#include "word.h"
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVector>
#include <QGridLayout>
#include <QMessageBox>
#include "database.h"


class RepeatWindow : public QWidget
{
    Q_OBJECT
public:
    explicit RepeatWindow(QWidget *parent = 0, const QString& login = "");
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
    int idx;
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
    QMessageBox box;

};

#endif // REPEATWINDOW_H
