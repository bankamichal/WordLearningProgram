#include "user.h"

User::User()
{

}

User::User(QString name, QString surname, int age, QString password, QString username)
{
    setName(name);
    setSurname(surname);
    setAge(age);
    setPassword(password);
    setUsername(username);
}

QString User::getName()
{
    return this->name;
}

QString User::getSurname()
{
    return this->surname;
}

int User::getAge()
{
    return this->age;
}

QString User::getPassword()
{
    return this->password;
}

QString User::getUsername()
{
    return this->username;
}

void User::setName(QString name)
{
    this->name = name;
}

void User::setSurname(QString surname)
{
    this->surname = surname;
}

void User::setAge(int age)
{
    this->age = age;
}

void User::setPassword(QString password)
{
    this->password = password;
}

void User::setUsername(QString username)
{
    this->username = username;
}

