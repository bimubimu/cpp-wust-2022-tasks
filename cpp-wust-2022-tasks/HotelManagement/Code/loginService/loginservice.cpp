#include "loginservice.h"

LoginService::LoginService(QObject *parent) : QObject(parent)
{
    QString connectionName = "LoginConn";
    m_pDatabase = new KDataBase(connectionName);
}

LoginService::~LoginService()
{
    delete m_pDatabase;
}

bool LoginService::checkUserInfo(const QString &username, const QString &password)
{
    if(username.isEmpty() || password.isEmpty())
        return false;

    return m_pDatabase->dbSearchUserInfo(username, password);
}
