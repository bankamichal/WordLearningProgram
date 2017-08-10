#ifndef PANELMAINMENU_H
#define PANELMAINMENU_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "editwordswindow.h"
#include "addwordwindow.h"
#include "learningwindow.h"
#include "repeatwindow.h"


class PanelMainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit PanelMainMenu(QWidget *parent = 0, QString login = "");

signals:
public slots:
    void showEditWordWindow();
    void showLearningWindow();
    void showRepeatWindow();
private:
    QString loginOfUser;
    QPushButton* pbStartLearning;
    QPushButton* pbRepeat;
    QPushButton* pbEdition;

    //QStackedLayout* layoutButtons;
    QGridLayout* layout1;

};

#endif // PANELMAINMENU_H
