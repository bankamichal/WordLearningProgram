#include "database.h"


DataBase* DataBase::singletone = NULL;

DataBase::DataBase() : DRIVER_NAME("QSQLITE"), DATABASE_NAME("./baza.db")
{
    db = QSqlDatabase::addDatabase(DRIVER_NAME);
    db.setDatabaseName(DATABASE_NAME);

    if (db.open())
    {
        qDebug() << "Connected with data base.";
    }
    else
    {
        qDebug() << db.lastError().text();
    }
}

DataBase *DataBase::getInstance()
{
    if (!singletone) {
           singletone = new DataBase();
           singletone->createTableUser();
           singletone->createTableWord();
       };
    return singletone;
}

void DataBase::createTableWord()
{
    if (db.isOpen())
    {
        QString createTableWord = "CREATE TABLE IF NOT EXISTS Word "
                                    "( "
                                    " id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                    " pl VARCHAR(64) NOT NULL, "
                                    " eng VARCHAR(64) NOT NULL, "
                                    " category varchar(32) NOT NULL, "
                                    " user_id int NOT NULL, "
                                    " result int NOT NULL"
                                    ")";
        QSqlQuery query;
        query.prepare(createTableWord);
        if (query.exec())
        {
            qDebug() << "'Word' table has been created.";
        }
        else
        {
            qDebug() << "'Word' table has NOT been created.";
            qDebug() << db.lastError().text();
        }
    }
}

void DataBase::createTableUser()
{
    if (db.isOpen())
    {
        QString createTableLekarz = "CREATE TABLE IF NOT EXISTS User "
                                    "( "
                                    " id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                    " name VARCHAR(32) NOT NULL, "
                                    " surname VARCHAR(64) NOT NULL, "
                                    " age int NOT NULL, "
                                    " username VARCHAR(32) NOT NULL, "
                                    " password VARCHAR(24) NOT NULL "
                                    ")";
        QSqlQuery query;
        query.prepare(createTableLekarz);
        if (query.exec())
        {
            qDebug() << "'User' table has been created.";
        }
        else
        {
            qDebug() << "'User' table has NOT been created.";
            qDebug() << db.lastError().text();
        }

        //when User table is created, admin account is registered automaticly
        User adm("admin","admin",99,Encryption::encrypt("admin"),"admin");
        if (!DataBase::getInstance()->checkIfUserExists(adm.getUsername()))
        {
            DataBase::getInstance()->insertUser(adm);
        }
    }

}

void DataBase::insertUser(User user)
{
    if (db.isOpen())
    {
        QString insertUser = "INSERT INTO User (name, surname, age, username, password) VALUES (:name, :surname, :age, :username, :password);";
        QSqlQuery query;
        query.prepare(insertUser);
        query.bindValue(":name", user.getName());
        query.bindValue(":surname", user.getSurname());
        query.bindValue(":age", user.getAge());
        query.bindValue(":username", user.getUsername());
        query.bindValue(":password", user.getPassword());
        if (query.exec())
        {
            qDebug() << "'User' has been added.";
        }
        else
        {
            qDebug() << "'User' has NOT been added.";
        }
    }
}

void DataBase::insertWord(Word word)
{
    if (db.isOpen())
    {
        QString insertWord = "INSERT INTO Word (pl, eng, category, user_id, result) VALUES "
                             "(:pl, :eng, :category, :user_id, :result);";
        QSqlQuery query;
        query.prepare(insertWord);
        query.bindValue(":pl", word.getPl());
        query.bindValue(":eng", word.getEng());
        query.bindValue(":category", word.getCategory());
        query.bindValue(":result", word.getResult());
        query.bindValue(":user_id", word.getUser_id());
        if (query.exec()) qDebug() << "'Word' has been added.";
        else
        {
            qDebug() << "'Word' has NOT been added.";
        }
    }
}

void DataBase::deleteWord(const int &id)
{

    if (db.isOpen())
    {
        QString deleteWord= "DELETE FROM Word WHERE id= :id;";
        QSqlQuery query;
        query.prepare(deleteWord);
        query.bindValue(":id", id);

        if (query.exec())
        {

            qDebug() << "Word has been deleted.";
        }
        else
        {
            qDebug() << "Word has NOT been deleted.";
        }
    }
}

bool DataBase::checkIfLoginAndPasswordCorrect(QString login, QString password)
{
    if (db.isOpen())
    {
        QString checkUsernamePassword = "SELECT * FROM User;";
        QSqlQuery query(checkUsernamePassword);
        query.exec();
        //not optimalized for big data bases
        while(query.next())
        {
            if (query.value(4).toString() == login && query.value(5).toString() == password) return true;
        }
    }
    return false;
}

bool DataBase::checkIfUserExists(const QString &login)
{
    if (db.isOpen())
    {
        QString checkIfExists= "SELECT username FROM User;";
        QSqlQuery query(checkIfExists);
        query.exec();
        while(query.next())
        {
            if (query.value(0).toString() == login) return true;
        }
    }
    return false;
}

QVector<Word> DataBase::getWords()
{
    QVector<Word> words;
    QString selectWords = "SELECT * FROM Word;";
    QSqlQuery query(selectWords);
    while(query.next())
    {
        int id = query.value(0).toInt();
        QString pl = query.value(1).toString();
        QString eng = query.value(2).toString();
        QString category = query.value(3).toString();
        int user_id = query.value(4).toInt();
        int result = query.value(5).toInt();
        words.push_back(Word(id,pl,eng,category,result, user_id));
    }

    return words;
}

QVector<Word> DataBase::getWords(const int &user_id)
{
    QVector<Word> words;
    QString selectWords = "SELECT * FROM Word WHERE user_id = :user_id";
    QSqlQuery query;
    query.prepare(selectWords);
    query.bindValue(":user_id", user_id);
    query.exec();
    while(query.next())
    {
        int id = query.value(0).toInt();
        QString pl = query.value(1).toString();
        QString eng = query.value(2).toString();
        QString category = query.value(3).toString();
        int user_id = query.value(4).toInt();
        int result = query.value(5).toInt();
        words.push_back(Word(id,pl,eng,category,result, user_id));
    }
    return words;
}

QVector<Word> DataBase::getNWorstWords(const int& n, const int& user_id)
{
    QVector<Word> words;
    QString nWorstWordsStr = "SELECT * FROM Word WHERE user_id = :user_id ORDER BY result LIMIT :n";
    QSqlQuery query;
    query.prepare(nWorstWordsStr);
    query.bindValue(":user_id", user_id);
    query.bindValue(":n", n);
    query.exec();
    while(query.next())
    {
        int id = query.value(0).toInt();
        QString pl = query.value(1).toString();
        QString eng = query.value(2).toString();
        QString category = query.value(3).toString();
        int user_id = query.value(4).toInt();
        int result = query.value(5).toInt();
        words.push_back(Word(id,pl,eng,category,result, user_id));
    }

    return words;
}

int DataBase::getResultOfWord(const int &wordId)
{
    int res = 0;
    QString result = "SELECT result FROM Word WHERE id = :id";
    QSqlQuery query;
    query.prepare(result);
    query.bindValue(":id", wordId);
    query.exec();
    if (query.next())
    {
        res = query.value(0).toInt();
        qDebug() << "Result has been found.";
    }
    else qDebug() << "Result has NOT been found";
    return res;
}

QVector<int> DataBase::IdsOfUsers()
{
    QVector<int> ids;
    QString selectNumber = "SELECT id FROM User";
    QSqlQuery query(selectNumber);
    while (query.next())
    {
        ids.push_back(query.value(0).toInt());
    }
    return ids;
}

int DataBase::getIdOfKnownLogin(const QString& login)
{
    if (db.isOpen())
    {
        int id = 0;
        QString selectNumber = "SELECT id FROM User WHERE username = :username ";
        QSqlQuery query;
        query.prepare(selectNumber);
        query.bindValue(":username",login);
        query.exec();
        while (query.next())
        {
            id = query.value(0).toInt();
        }      
        return id;
    }
}



void DataBase::defaultWordBase(const QString& login)
{
    DataBase::getInstance()->deleteAllWords(login);

    QVector<Word> words = DataBase::getInstance()->getWords(DataBase::getInstance()->getIdOfKnownLogin("admin"));
    foreach (Word w, words) {
        w.setUser_id(DataBase::getInstance()->getIdOfKnownLogin(login));
        w.setResult(50);
        DataBase::getInstance()->insertWord(w);
    }
    qDebug() << "Default words has been added.";
}

void DataBase::deleteAllWords(const QString &login)
{
    int id = DataBase::getInstance()->getIdOfKnownLogin(login);
    QString deleteAllWords = "DELETE FROM Word WHERE user_id = :id";
    QSqlQuery query;
    query.prepare(deleteAllWords);
    query.bindValue(":id",  id);
    query.exec();
    while (query.next())
    {
        qDebug() << "All words has been deleted.";
    }
}

void DataBase::changeResultWord(const int& idOfWord, const int &change)
{
    int lastResult = DataBase::getInstance()->getResultOfWord(idOfWord);
    lastResult += change;
    QString changeStr = "UPDATE Word SET result = :result WHERE id = :id ";
    QSqlQuery query;
    query.prepare(changeStr);
    query.bindValue(":result", lastResult);
    query.bindValue(":id", idOfWord);
    //query.exec();
    if (query.exec())
    {
        qDebug() << "Result has been updated.";
    }
    else
    {
        qDebug() << "Result has NOT been updated.";
    }
}
