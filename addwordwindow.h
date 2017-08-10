#ifndef ADDWORDWINDOW_H
#define ADDWORDWINDOW_H

#include <QWidget>
#include <QStackedLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include "database.h"

class AddWordWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AddWordWindow(QWidget *parent = 0);

signals:
public slots:
    void addWord();
    void closeWindow();
private:

    QPushButton* pbAddWord;
    QPushButton* pbClose;
    QLabel* lPl;
    QLabel* lEng;
    QLabel* lCategory;
    QLineEdit* lePl;
    QLineEdit* leEng;
    QLineEdit* leCategory;
    QGridLayout* layoutButtons;
};

#endif // ADDWORDWINDOW_H
