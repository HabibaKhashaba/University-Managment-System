#ifndef USER_H
#define USER_H

#include "QtCore/qstring.h"
class User
{
public:
    User();
    QString getEmail() const;
    void setEmail(const QString &newEmail);

    QString getPassword() const;
    void setPassword(const QString &newPassword);

    QString getName() const;
    void setName(const QString &newName);

signals:
    void passwordChanged();

private:
    QString email;
    QString password;
    QString name;
};

#endif // USER_H
