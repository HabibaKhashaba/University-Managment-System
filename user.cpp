#include "user.h"

User::User() {}

QString User::getEmail() const
{
    return email;
}

void User::setEmail(const QString &newEmail)
{
    email = newEmail;
}

QString User::getPassword() const
{
    return password;
}

void User::setPassword(const QString &newPassword)
{
    if (password == newPassword)
        return;
    password = newPassword;
}

QString User::getName() const
{
    return name;
}

void User::setName(const QString &newName)
{
    name = newName;
}
