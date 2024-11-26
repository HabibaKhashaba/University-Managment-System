#ifndef ADMIN_H
#define ADMIN_H

#include "QtCore/qstring.h"
class Admin
{
public:
    Admin();
    QString getAdminId() const;
    void setAdminId(const QString &newAdminId);

private:
    QString adminId;
};

#endif // ADMIN_H
