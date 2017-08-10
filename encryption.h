#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include <QString>
#include <QDebug>

class Encryption
{
private:
    static int key;
    Encryption();
public:
    static QString encrypt(const QString& pass);
};

#endif // ENCRYPTION_H
