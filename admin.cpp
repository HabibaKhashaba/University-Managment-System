#include "admin.h"

Admin::Admin() {}

QString Admin::getAdminId() const
{
    return adminId;
}

void Admin::setAdminId(const QString &newAdminId)
{
    adminId = newAdminId;
}
