#ifndef PANELLOGIN_H
#define PANELLOGIN_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include <QHBoxLayout>
#include <QGridLayout>
#include "registerwindow.h"
#include "panelmainmenu.h"


class PanelLogin : public QWidget
{
    Q_OBJECT
public:
    explicit PanelLogin(QWidget *parent = 0);
signals:
public slots:
    void showRegisterPanelPanel();
    void closePanelLogin();
    void showMenu();
private:


};

#endif // PANELLOGIN_H
