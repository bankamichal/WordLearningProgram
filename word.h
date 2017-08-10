#ifndef WORD_H
#define WORD_H
#include <QString>

class Word
{
private:
    int id;
    QString pl;
    QString eng;
    QString category;
    int result;
    int user_id;
public:
    Word();
    Word(QString pl, QString eng, QString category, int result, int user_id);
    Word(int id, QString pl, QString eng, QString category, int result, int user_id);

    int getId() const;
    QString getPl() const;
    QString getEng() const;
    QString getCategory() const;
    int getResult() const;
    int getUser_id() const;

    void setId(const int& id);
    void setPl(const QString& pl);
    void setEng(const QString& eng);
    void setCategory(const QString& category);
    void setResult(const int& result);
    void setUser_id(const int& user_id);
};

#endif // WORD_H
