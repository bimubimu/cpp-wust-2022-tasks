#ifndef KPRICEINFO_H
#define KPRICEINFO_H

#include <QObject>
#include <QSqlTableModel>
#include <QPixmap>
#include "database/kdatabase.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

class KPriceInfo : public QObject
{
    Q_OBJECT
public:
    explicit KPriceInfo(QObject *parent = nullptr);
    ~KPriceInfo();

    void initSqlModel();
    QSqlTableModel* getTableModel();

    QPixmap getRoomPicture(int id);

private:
    QSqlTableModel * m_model;
    KDataBase * m_pDatabase;
};

#endif // KPRICEINFO_H
