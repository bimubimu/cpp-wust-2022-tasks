#ifndef KROOMINFO_H
#define KROOMINFO_H

#include <QObject>
#include "database/kdatabase.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

class KRoomInfo : public QObject
{
    Q_OBJECT
public:
    explicit KRoomInfo(QObject *parent = nullptr);
    ~KRoomInfo();

    void getRoomInfo(int index, QString& id, QString& roomType, QString& roomStatus);

private:
    KDataBase * m_pDatabase;
};

#endif // KROOMINFO_H
