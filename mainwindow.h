#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedLayout>

#include <QMenu>
#include <QAction>

#include "panellogin.h"
#include "registerwindow.h"

class mainwindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainwindow(QWidget *parent = 0);

signals:
public slots:
    void showLoginPanel();
    void setCurrentLayoutToMainMenu();

private:
    PanelLogin* panelLogin;
    PanelMainMenu* panelMainMenu;
    QStackedLayout* stackedLayout;
    QWidget* centralW;
};

#endif // MAINWINDOW_H
