#ifndef LOGINSERVICE_H
#define LOGINSERVICE_H

#include <QObject>
#include "database/kdatabase.h"

class LoginService : public QObject
{
    Q_OBJECT
public:
    explicit LoginService(QObject *parent = nullptr);
    ~LoginService();

    bool checkUserInfo(const QString &username, const QString &password);

private:
    KDataBase * m_pDatabase;
};

#endif // LOGINSERVICE_H
