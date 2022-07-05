#include "kroominfo.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

KRoomInfo::KRoomInfo(QObject *parent) : QObject(parent)
{
    QString connectionName = "roomInfoConn";
    m_pDatabase = new KDataBase(connectionName);
}

KRoomInfo::~KRoomInfo()
{
    delete m_pDatabase;
}

void KRoomInfo::getRoomInfo(int index, QString &id, QString &roomType, QString &roomStatus)
{
    QSqlQuery query(m_pDatabase->getDatabase());

    query.prepare("select * from roomInfo");

    bool ok = query.exec();
    if(!ok)
    {
        qDebug()<<"[KRoomInfo::getRoomInfo]: "<<query.lastError().text();
        return;
    }

    query.next();
    for(int i = 0; i < index; i ++)
        query.next();

    id = query.value(0).toString();
    roomType = query.value(1).toString();
    roomStatus = query.value(2).toString();
}
