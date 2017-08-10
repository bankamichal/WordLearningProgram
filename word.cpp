#include "word.h"

Word::Word()
{

}

Word::Word(QString pl, QString eng, QString category, int result, int user_id)
{
    setPl(pl);
    setEng(eng);
    setCategory(category);
    setResult(result);
    setUser_id(user_id);
}

Word::Word(int id, QString pl, QString eng, QString category, int result, int user_id)
{
    setId(id);
    setPl(pl);
    setEng(eng);
    setCategory(category);
    setResult(result);
    setUser_id(user_id);
}

int Word::getId() const
{
    return this->id;
}

QString Word::getPl() const
{
    return this->pl;
}

QString Word::getEng() const
{
    return this->eng;
}

QString Word::getCategory() const
{
    return this->category;
}

int Word::getResult() const
{
    return this->result;
}

int Word::getUser_id() const
{
    return this->user_id;
}

void Word::setId(const int &id)
{
    this->id = id;
}

void Word::setPl(const QString &pl)
{
    this->pl = pl;
}

void Word::setEng(const QString &eng)
{
    this->eng = eng;
}

void Word::setCategory(const QString &category)
{
    this->category = category;
}

void Word::setResult(const int &result)
{
    this->result = result;
}

void Word::setUser_id(const int &user_id)
{
    this->user_id = user_id;
}
