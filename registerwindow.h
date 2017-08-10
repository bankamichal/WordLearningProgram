#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
#include <QStackedLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QStackedLayout>
#include <QMessageBox>
#include "user.h"
#include "encryption.h"
#include "database.h"


class RegisterWindow : public QWidget
{
    Q_OBJECT
public:
    //explicit NowyWidget(QWidget *parent, Person* person, QWidget* w2);
    explicit RegisterWindow(QWidget *parent);

signals:
public slots:
    void closeWindow();
    void registerNewUser();
private:
    QPushButton* btnRegister;
    QPushButton* btnCancel;

    QLineEdit* leName;
    QLineEdit* leSurname;
    QLineEdit* leAge;
    QLineEdit* leUsername;
    QLineEdit* lePassword;

    QLabel* lName;
    QLabel* lSurname;
    QLabel* lAge;
    QLabel* lUsername;
    QLabel* lPassword;

    QGridLayout* layoutFields;
    QHBoxLayout* layoutOperationButtons;
    QVBoxLayout* layoutMain;

};

#endif // REGISTERWINDOW_H
