#include "kdatabase.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QByteArray>
#include <QCoreApplication>

KDataBase::KDataBase(const QString& connectionName, QObject *parent) : QObject(parent)
{
    initDatabase(connectionName);
}

KDataBase::~KDataBase()
{
    if(m_db.isOpen())
        m_db.close();
}

void KDataBase::initDatabase(const QString& connectionName)
{
    bool ok;

    m_db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    m_db.setDatabaseName("hotel.db");

    ok = m_db.open();
    if(!ok)
    {
        qDebug()<<"[KDataBase::initDatabase]: "<<m_db.lastError().text();
        return;
    }

    createTableUsers();
    createTableRoomPrice();
    createTableRoomInfo();
    createCustomer();
}

void KDataBase::createTableUsers()
{
    bool ok;

    QSqlQuery query(m_db);

    //创建管理员表
    QString sql = "create table if not exists users(id integer primary key autoincrement,"
                                     "username text not null,"
                                     "password text not null,"
                                     "name text not null,"
                                     "sex text check(sex = '男' or sex = '女') not null,"
                                     "phoneNumber text not null,"
                                     "email text not null,"
                                     "birthday text not null,"
                                     "address text not null,"
                                     "avatar blob)";

    //执行sql语句
    ok = query.exec(sql);
    if(!ok)
    {
        qDebug()<<"[KDataBase::createTableUsers]: "<<query.lastError().text();
        return;
    }

    //插入管理员信息
    //插入头像
    QFile file("://image/avatar.jpg");
    file.open(QIODevice::ReadOnly);
    QByteArray byteArray = file.readAll();
    sql = "insert or ignore into users(id,username,password,name,sex,phoneNumber,email,birthday,address,avatar)"
          " values(1, 'admin', '123456', '王子懿', '男', '13264790807', '3417767446@qq.com', '2001/01/20', '湖北',?)";
    query.prepare(sql);
    query.bindValue(0, byteArray);
    ok = query.exec();
    if(!ok)
    {
        qDebug()<<"[KDataBase::createTableUsers]: "<<query.lastError().text();
        return;
    }
}

void KDataBase::createTableRoomPrice()
{
    bool ok;

    QSqlQuery query(m_db);

    //创建客房价格表
    QString sql = "create table if not exists roomPrice(id integer primary key,"
                                     "roomType text not null,"
                                     "roomTodayPrice int not null,"
                                     "roomNormalPrice int not null,"
                                     "roomVipPrice text int null,"
                                     "roomPixmap blob)";

    ok = query.exec(sql);
    if(!ok)
    {
        qDebug()<<"[KDataBase::createTableRoomPrice]: "<<query.lastError().text();
        return;
    }

    QFile fileOne(":/image/one.jpg");
    QFile fileTwo(":/image/two.jpg");
    QFile fileThree(":/image/three.jpg");
    QFile fileFour(":/image/four.jpg");
    QFile fileFive(":/image/five.jpg");
    fileOne.open(QIODevice::ReadOnly);
    fileTwo.open(QIODevice::ReadOnly);
    fileThree.open(QIODevice::ReadOnly);
    fileFour.open(QIODevice::ReadOnly);
    fileFive.open(QIODevice::ReadOnly);
    QByteArray byteArrayOne = fileOne.readAll();
    QByteArray byteArrayTwo = fileTwo.readAll();
    QByteArray byteArrayThree = fileThree.readAll();
    QByteArray byteArrayFour = fileFour.readAll();
    QByteArray byteArrayFive = fileFive.readAll();

    //插入房间价格信息
    sql = "insert or ignore into roomPrice values(1,'单人间',120,160,100,?)";
    query.prepare(sql);
    query.bindValue(0,byteArrayOne);
    query.exec();
    sql = "insert or ignore into roomPrice values(2,'标准间',180,220,160,?)";
    query.prepare(sql);
    query.bindValue(0,byteArrayTwo);
    query.exec();
    sql = "insert or ignore into roomPrice values(3,'大床房',160,200,140,?)";
    query.prepare(sql);
    query.bindValue(0,byteArrayThree);
    query.exec();
    sql = "insert or ignore into roomPrice values(4,'商务套房',200,240,180,?)";
    query.prepare(sql);
    query.bindValue(0,byteArrayFour);
    query.exec();
    sql = "insert or ignore into roomPrice values(5,'豪华套房',300,340,200,?)";
    query.prepare(sql);
    query.bindValue(0,byteArrayFive);
    query.exec();
}

void KDataBase::createTableRoomInfo()
{
    bool ok;

    QSqlQuery query(m_db);

    //创建客房信息表
    QString sql = "create table if not exists roomInfo(id integer primary key,"
                                     "roomType text not null,"
                                     "roomStatus text check(roomStatus = '空房' or roomStatus = '入住') not null)";

    ok = query.exec(sql);
    if(!ok)
    {
        qDebug()<<"[KDataBase::createTableRoomInfo]: "<<query.lastError().text();
        return;
    }

    //存入房间信息
    sql = "insert or ignore into roomInfo values(101,'单人间','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(102,'单人间','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(103,'单人间','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(104,'单人间','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(105,'单人间','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(106,'单人间','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(201,'标准间','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(202,'标准间','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(203,'标准间','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(204,'标准间','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(205,'标准间','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(206,'标准间','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(301,'大床房','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(302,'大床房','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(303,'大床房','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(304,'大床房','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(305,'大床房','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(306,'大床房','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(401,'商务套房','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(402,'商务套房','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(403,'商务套房','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(404,'豪华套房','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(405,'豪华套房','空房')";
    query.exec(sql);
    sql = "insert or ignore into roomInfo values(406,'豪华套房','空房')";
    query.exec(sql);
}

void KDataBase::createCustomer()
{
    bool ok;

    QSqlQuery query(m_db);

    //创建顾客信息表
    QString sql = "create table if not exists customer"
            "("
                "id integer primary key autoincrement,"
                "name text not null,"
                "idCard text not null,"
                "userPhone text not null,"
                "userRoomNumber text not null,"
                "userState text check(userState = '入住' or userState = '离开') not null,"
                "userPermission text check(userPermission = 'VIP' or userPermission = 'NORMAL') not null,"
                "userCheckIn text not null,"
                "userCheckOut text not null,"
                "realCheckOut text,"
                "userConsumeMoney text not null"
            ");";

    ok = query.exec(sql);
    if(!ok)
    {
        qDebug()<<"[KDataBase::createCustomer]: "<<query.lastError().text();
        return;
    }
}

QSqlDatabase &KDataBase::getDatabase()
{
    return m_db;
}

bool KDataBase::dbSearchUserInfo(const QString &username, const QString &password)
{
    bool ok;

    QSqlQuery query(m_db);

    QString sql = "select * from users where username = ? and password = ?";

    query.prepare(sql);
    query.bindValue(0, username);
    query.bindValue(1, password);

    ok = query.exec();
    if(!ok)
    {
        qDebug()<<"[KDataBase::dbSearchUserInfo]: "<<query.lastError().text();
        return false;
    }

    if(query.next())
        return true;

    return false;
}
