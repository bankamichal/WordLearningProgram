#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedLayout>

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include <QHBoxLayout>
#include <QGridLayout>

#include <QMenu>
#include <QAction>

#include "registerwindow.h"
#include "panelmainmenu.h"
#include "database.h"

class LoginWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = 0);

signals:

public slots:
    void showRegisterWindow();
    void showMainMenu();
    void closeLoginWindow();
private:
    QStackedLayout* stackedLayout;
    QWidget* centralW;
    QPushButton* pbLogin;
    QPushButton* pbRegister;
    QPushButton* pbCancel;

    QLineEdit* leLogin;
    QLineEdit* lePassword;

    QLabel* lLogin;
    QLabel* lPassword;
    QLabel* lMyGitHub;

    QGridLayout* layoutLoginPass;
    QGridLayout* layoutButtons;
    QVBoxLayout* layoutMain;
};

#endif // LOGINWINDOW_H
