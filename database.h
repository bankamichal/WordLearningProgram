#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QVector>
#include <QSqlQuery>
#include "user.h"
#include "word.h"
#include "encryption.h"

class DataBase
{
private:
    const QString DRIVER_NAME;
    const QString DATABASE_NAME;
    static DataBase* singletone;
    DataBase();
public:
    static DataBase* getInstance();
    QSqlDatabase db;

    void createTableWord();
    void createTableUser();
    void insertUser(User user);
    void insertWord(Word word);
    void deleteWord(const int& id);
    bool checkIfLoginAndPasswordCorrect(QString login, QString password);
    bool checkIfUserExists(const QString& login);
    QVector<Word> getWords();
    QVector<Word> getWords(const int& user_id);
    QVector<Word> getNWorstWords(const int& n, const int& user_id);
    int getResultOfWord(const int& wordId);
    QVector<int> IdsOfUsers();
    int getIdOfKnownLogin(const QString& login);
    void defaultWordBase(const QString& login);
    void deleteAllWords(const QString& login);
    void changeResultWord(const int& idOfWord, const int& change);

};

#endif // DATABASE_H
