#include "encryption.h"

int Encryption::key = 3;

Encryption::Encryption()
{

}

QString Encryption::encrypt(const QString& pass)
{
    QString hiddenPass = "";
    for (int i = 0; i < pass.size(); i++)
    {
        if (pass[i] <= 'Z' && pass[i] >= 'A')
        {
            if (pass[i] <= 'Z' - key && pass[i] >= 'A')
            {
                hiddenPass += (pass[i] + key);
            }
            else
            {
                hiddenPass += ('A' - 'Z' + key - 1 - (int)pass[i].digitValue());
            }
        }
        else if (pass[i] <= 'z' && pass[i] >= 'a')
        {
            if (pass[i] <= 'z' - key && pass[i] >= 'a')
            {                
                hiddenPass.append((char)(pass[i].toLatin1() + key));
            }
            else
            {
                hiddenPass += ('a' + (key - ('z' - (pass[i].digitValue() - 1))));
            }
        }
        else hiddenPass += pass[i];
    }
    return hiddenPass;
}
