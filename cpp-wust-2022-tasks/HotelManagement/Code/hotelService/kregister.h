#ifndef KREGISTER_H
#define KREGISTER_H

#include <QObject>
#include <QSqlTableModel>
#include <QVector>
#include "database/kdatabase.h"

class KRegister : public QObject
{
    Q_OBJECT
public:
    explicit KRegister(QObject *parent = nullptr);
    ~KRegister();

    void initSqlModel();
    QSqlTableModel* getTableModel();

    void checkIn(const QVector<QString>& customerInfo);   //登记入住
    void checkOut(const QString& roomNumber, const QString& timeCheckOut, QVector<QString>& info);  //登记退房
    void queryInRoomNumber(const QString& roomNumber);   //以房间号查询
    void queryInName(const QString& name);   //以姓名查询
    void queryInIdCard(const QString& idCard);   //以身份证查询

    bool roomIsEmpty(const QString userRoomNumber);    //检查房间是否为空
    void changeRoomState(const QString& userRoomNumber, const QString state);   //修改房间状态
    QString changeCustomerState(const QString& roomNumber, const QString& timeCheckOut);   //修改客人状态
    int calculateRoomPrice(const QString& roomType, const QString& userPermission);   //计算房价单日价格
    QString calculateConsume(const QString& timeCheckIn, const QString& timeCheckOut,
                             const QString& userPermission, const QString& roomType);  //计算总花费
    QString getRoomType(const QString& roomNumber);

private:
    QSqlTableModel * m_model;
    KDataBase * m_pDatabase;
};

#endif // KREGISTER_H
