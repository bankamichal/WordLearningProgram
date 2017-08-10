#include <QApplication>
#include "loginwindow.h"


int main(int argc, char* argv[])
{
    srand(time(NULL));
    qDebug() << "=========================================";
    QApplication a(argc, argv);
    LoginWindow app;
    DataBase* db = DataBase::getInstance();

    app.show();
    return a.exec();
}
