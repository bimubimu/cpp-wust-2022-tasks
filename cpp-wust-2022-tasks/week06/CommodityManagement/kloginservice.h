#ifndef KLOGINSERVICE_H
#define KLOGINSERVICE_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QObject>
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class KLoginService : public QObject
{
    Q_OBJECT
public:
    explicit KLoginService(QObject *parent = nullptr);
    ~KLoginService();

    void createSqlConn();
    bool checkUserInfo(const QString& userId,const QString& password);

private:
    QSqlDatabase m_db;
};

#endif // KLOGINSERVICE_H
