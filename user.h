#ifndef USER_H
#define USER_H
#include <QString>

class User
{
private:
    QString name;
    QString surname;
    int age;
    QString password;
    QString username;
public:
    User();
    User(QString name, QString surname, int age, QString password, QString username);

    QString getName();
    QString getSurname();
    int getAge();
    QString getPassword();
    QString getUsername();

    void setName(QString name);
    void setSurname(QString surname);
    void setAge(int age);
    void setPassword(QString password);
    void setUsername(QString username);
};

#endif // USER_H
