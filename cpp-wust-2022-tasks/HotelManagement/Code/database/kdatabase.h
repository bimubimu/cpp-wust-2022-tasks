#ifndef KDATABASE_H
#define KDATABASE_H

#include <QObject>
#include <QSqlDatabase>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

class KDataBase : public QObject
{
    Q_OBJECT
public:
    explicit KDataBase(const QString& connectionName, QObject *parent = nullptr);
    ~KDataBase();

    void initDatabase(const QString& connectionName);
    void createTableUsers();
    void createTableRoomPrice();
    void createTableRoomInfo();
    void createCustomer();

    QSqlDatabase& getDatabase();

    bool dbSearchUserInfo(const QString &username, const QString &password);

private:
    QSqlDatabase m_db;
};

#endif // KDATABASE_H
