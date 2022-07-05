
#include "kloginservice.h"

KLoginService::KLoginService(QObject *parent) : QObject(parent)
{
    createSqlConn();
}

KLoginService::~KLoginService()
{
    m_db.close();
}

void KLoginService::createSqlConn()
{
    //连接数据库
    QString connectionName = "loginServiceConnection";
    m_db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    m_db.setDatabaseName("company.db");
    bool ok = m_db.open();
    if(!ok)
    {
        QMessageBox::warning(NULL, "数据库操作", "数据库打开失败",QMessageBox::Yes, QMessageBox::Yes);
        qDebug()<<m_db.lastError().text();
        return;
    }
}

bool KLoginService::checkUserInfo(const QString& userId, const QString& password)
{
    QSqlQuery query(m_db);
    query.prepare("select password from employee where id = ?");
    query.bindValue(0, userId);
    query.exec();

    if(query.next() && query.value(0) == password)
        return true;
    else
        return false;
}
