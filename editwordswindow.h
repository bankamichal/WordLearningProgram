#ifndef EDITWORDSWINDOW_H
#define EDITWORDSWINDOW_H

#include <QWidget>
#include <QStackedLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QTableWidget>
#include <QVector>
#include <QCheckBox>
#include <QSignalMapper>
#include <QMessageBox>
#include "database.h"

class EditWordsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit EditWordsWindow(QWidget *parent = 0, QString login = "");

signals:

public slots:
    void addWord();
    void defaultWords();
    void refreshWords();
    void deleteAllwords();
    void deleteWords(int a);
private:
    QString login;
    QTableWidget* listOfWords;

    QPushButton* pbAddWord;
    QPushButton* pbDeleteWords;
    QPushButton* pbDefaultWords;
    QLineEdit* lePl;
    QLineEdit* leEng;
    QLineEdit* leCategory;
    QLabel* lPl;
    QLabel* lEng;
    QLabel* lCategory;
    QPushButton* lAdminInfo;


    QGridLayout* layoutButtons;
};

#endif // EDITWORDSWINDOW_H
