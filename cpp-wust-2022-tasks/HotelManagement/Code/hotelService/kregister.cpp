#include "kregister.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlRecord>
#include <QDateTime>

KRegister::KRegister(QObject *parent) : QObject(parent)
{
    QString connectionName = "registerConn";
    m_pDatabase = new KDataBase(connectionName);

    initSqlModel();
}

KRegister::~KRegister()
{
    delete m_model;
    delete m_pDatabase;
}

void KRegister::initSqlModel()
{
    m_model = new QSqlTableModel(this, m_pDatabase->getDatabase());

    m_model->setTable("customer");

    //设置手动提交
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //查询数据库
    m_model->select();

    m_model->removeColumn(0);
    m_model->setHeaderData(0, Qt::Horizontal, "姓名");
    m_model->setHeaderData(1, Qt::Horizontal, "身份证号");
    m_model->setHeaderData(2, Qt::Horizontal, "电话号码");
    m_model->setHeaderData(3, Qt::Horizontal, "房间号");
    m_model->setHeaderData(4, Qt::Horizontal, "用户状态");
    m_model->setHeaderData(5, Qt::Horizontal, "权限");
    m_model->setHeaderData(6, Qt::Horizontal, "入住时间");
    m_model->setHeaderData(7, Qt::Horizontal, "预约退房时间");
    m_model->setHeaderData(8, Qt::Horizontal, "实际退房时间");
    m_model->setHeaderData(9, Qt::Horizontal, "总房费");
}

QSqlTableModel *KRegister::getTableModel()
{
    return m_model;
}

bool KRegister::roomIsEmpty(const QString userRoomNumber)
{
    QSqlQuery query(m_pDatabase->getDatabase());
    QString sql = "select roomStatus from roomInfo where id = ?";

    query.prepare(sql);
    query.bindValue(0, userRoomNumber.toInt());

    bool ok = query.exec();
    if(!ok)
    {
        qDebug()<<"[KRegister::roomIsEmpty]: "<<query.lastError();
        return false;
    }

    query.first();
    if(query.value(0).toString() == "空房")
        return true;

    return false;
}

void KRegister::changeRoomState(const QString& userRoomNumber, const QString state)
{
    QSqlQuery query(m_pDatabase->getDatabase());
    QString sql = "update roomInfo set roomStatus = ? where id = ?";

    query.prepare(sql);
    query.bindValue(0, state);
    query.bindValue(1, userRoomNumber);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug()<<"[KRegister::changeRoomCheckIn]: "<<query.lastError();
        return;
    }
}

QString KRegister::changeCustomerState(const QString& roomNumber, const QString &timeCheckOut)
{
    //根据房间号和当前的入住状态确定当前客人的记录
    //更改用户的状态、实际退房时间、总房费
    QSqlQuery query(m_pDatabase->getDatabase());

    //确定当前用户权限,入住时间
    QString sql = "select userPermission,userCheckIn from customer where userRoomNumber = ? and userState = '入住'";
    query.prepare(sql);
    query.bindValue(0, roomNumber);
    bool ok = query.exec();
    if(!ok)
    {
        qDebug()<<"[KRegister::changeCustomerState]: "<<query.lastError();
        return"";
    }
    query.first();
    QString permission = query.value(0).toString();
    QString timeCheckIn = query.value(1).toString();
    QString consume = calculateConsume(timeCheckIn, timeCheckOut, permission, getRoomType(roomNumber));

    //修改用户状态
    sql = "update customer set userState = ?, realCheckOut = ?, userConsumeMoney = ? where userRoomNumber = ? and userState = '入住'";
    query.prepare(sql);
    query.bindValue(0, "离开");
    query.bindValue(1, timeCheckOut);
    query.bindValue(2, consume);
    query.bindValue(3, roomNumber);
    ok = query.exec();
    if(!ok)
    {
        qDebug()<<"[KRegister::changeCustomerState]: "<<query.lastError();
        return "";
    }

    return consume;
}

int KRegister::calculateRoomPrice(const QString &roomType, const QString &userPermission)
{
    //获得房间价格
    int price = 0;
    QSqlQuery query(m_pDatabase->getDatabase());
    if(userPermission == "VIP")
    {
        QString sql = "select roomVipPrice from roomPrice where roomType = ?";
        query.prepare(sql);
        query.bindValue(0, roomType);
        bool ok = query.exec();
        if(!ok)
        {
            qDebug()<<"[KRegister::calculateConsume]: "<<query.lastError();
            return 0;
        }
        query.next();
        price = query.value(0).toInt();
    }
    else
    {
        QString sql = "select roomTodayPrice from roomPrice where roomType = ?";
        query.prepare(sql);
        query.bindValue(0, roomType);
        bool ok = query.exec();
        if(!ok)
        {
            qDebug()<<"[KRegister::calculateConsume]: "<<query.lastError();
            return 0;
        }
        query.next();
        price = query.value(0).toInt();
    }
    return price;
}

QString KRegister::calculateConsume(const QString &timeCheckIn, const QString &timeCheckOut,
                                    const QString& userPermission, const QString& roomType)
{
    QDateTime timeIn = QDateTime::fromString(timeCheckIn, "yyyy/MM/dd");
    QDateTime timeOut = QDateTime::fromString(timeCheckOut, "yyyy/MM/dd");
    //计算时间差
    int days = timeIn.daysTo(timeOut);
    //不满一天按照一天计算
    if(days == 0)
        days ++;

    //计算房间单日价格
    int price = calculateRoomPrice(roomType, userPermission);
    return QString::number(price * days);
}

QString KRegister::getRoomType(const QString &roomNumber)
{
    switch(roomNumber.toInt())
    {
    case 101:
    case 102:
    case 103:
    case 104:
    case 105:
    case 106:   return "单人间";
    case 201:
    case 202:
    case 203:
    case 204:
    case 205:
    case 206:   return "标准间";
    case 301:
    case 302:
    case 303:
    case 304:
    case 305:
    case 306:   return "大床房";
    case 401:
    case 402:
    case 403:   return "商务套房";
    case 404:
    case 405:
    case 406:   return "豪华套房";
    default:    return "";
    }
}

void KRegister::checkIn(const QVector<QString> &customerInfo)
{
    //记录用户信息
    QString name = customerInfo[0];
    QString idCard = customerInfo[1];
    QString userPhone = customerInfo[2];
    QString userRoomNumber = customerInfo[3];
    QString userState = "入住";    //入住时状态默认为入住
    QString userPermission = customerInfo[4];
    QString userCheckIn = customerInfo[5];
    QString userCheckOut = customerInfo[6];
    QString userConsumeMoney = "0";   //入住时默认消费为0

    //如果入住房间不为空直接返回
    if(!roomIsEmpty(userRoomNumber))
    {
        QMessageBox::information(NULL, "提示", "该房间已有客人入住");
        return;
    }

    //插入用户登记信息
    int line = m_model->rowCount();
    m_model->insertRow(line);

    m_model->setData(m_model->index(line, 0), name);
    m_model->setData(m_model->index(line, 1), idCard);
    m_model->setData(m_model->index(line, 2), userPhone);
    m_model->setData(m_model->index(line, 3), userRoomNumber);
    m_model->setData(m_model->index(line, 4), userState);
    m_model->setData(m_model->index(line, 5), userPermission);
    m_model->setData(m_model->index(line, 6), userCheckIn);
    m_model->setData(m_model->index(line, 7), userCheckOut);
    m_model->setData(m_model->index(line, 9), userConsumeMoney);

    m_model->submitAll();

    //成功入住后立刻修改房间入住信息
    changeRoomState(userRoomNumber, "入住");

    QMessageBox::information(NULL, "提示", "入住登记成功！");
}

void KRegister::checkOut(const QString& roomNumber, const QString& timeCheckOut, QVector<QString>& info)
{
    if(roomIsEmpty(roomNumber))
    {
        QMessageBox::information(NULL, "提示", "当前房间没有客人入住");
        return;
    }

    //修改当前房间状态
    changeRoomState(roomNumber, "空房");

    //获取信息进行打印  客人姓名、(房间号)、房间类型、入住离开时间、(实际离开时间)、入住总时间、权限、房间单价、总价
    QSqlQuery query(m_pDatabase->getDatabase());
    QString sql = "select name,userCheckIn, userCheckOut,userPermission from customer where userState = '入住' and userRoomNumber = ?";
    query.prepare(sql);
    query.bindValue(0, roomNumber);
    bool ok = query.exec();
    if(!ok)
    {
        qDebug()<<"[KRegister::checkOut] "<<query.lastError();
        return;
    }

    query.first();
    QString name = query.value(0).toString();
    QString roomType = getRoomType(roomNumber);
    QString timeIn = query.value(1).toString();
    QString timeOut = query.value(2).toString();
    QString days = QString::number(QDateTime::fromString(timeIn, "yyyy/MM/dd").daysTo(QDateTime::fromString(timeOut, "yyyy/MM/dd")));
    QString Permission = query.value(3).toString();
    QString price = QString::number(calculateRoomPrice(roomType, Permission));
    //修改顾客信息状态  返回总价
    QString consume = changeCustomerState(roomNumber, timeCheckOut);

    info.push_back(name);
    info.push_back(roomType);
    info.push_back(timeIn);
    info.push_back(timeOut);
    info.push_back(days);
    info.push_back(Permission);
    info.push_back(price);
    info.push_back(consume);
}

void KRegister::queryInRoomNumber(const QString& roomNumber)
{
    m_model->setFilter(tr("userRoomNumber = '%1'").arg(roomNumber));
    m_model->select();
}

void KRegister::queryInName(const QString &name)
{
    m_model->setFilter(tr("name = '%1'").arg(name));
    m_model->select();
}

void KRegister::queryInIdCard(const QString &idCard)
{
    m_model->setFilter(tr("idCard = '%1'").arg(idCard));
    m_model->select();
}


