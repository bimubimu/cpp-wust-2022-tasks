#include "kemployee.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QByteArray>

KEmployee::KEmployee(QObject *parent) : QObject(parent)
{
    QString connectionName = "employeeConn";
    m_pDatabase = new KDataBase(connectionName);

    initSqlModel();
}

KEmployee::~KEmployee()
{
    delete m_pDatabase;
    delete m_model;
}

void KEmployee::initSqlModel()
{
    m_model = new QSqlTableModel(this, m_pDatabase->getDatabase());

    m_model->setTable("users");

    //设置手动提交
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //查询数据库
    m_model->select();

    m_model->removeColumn(0);
    m_model->removeColumn(1);
    m_model->removeColumn(7);
    m_model->setHeaderData(0, Qt::Horizontal, "用户名");
    m_model->setHeaderData(1, Qt::Horizontal, "姓名");
    m_model->setHeaderData(2, Qt::Horizontal, "性别");
    m_model->setHeaderData(3, Qt::Horizontal, "电话号码");
    m_model->setHeaderData(4, Qt::Horizontal, "邮箱");
    m_model->setHeaderData(5, Qt::Horizontal, "出生日期");
    m_model->setHeaderData(6, Qt::Horizontal, "地址");
}

QSqlTableModel *KEmployee::getTableModel()
{
    return m_model;
}

void KEmployee::employeeRegister(const QVector<QString> &info)
{
    QSqlQuery query(m_pDatabase->getDatabase());

    //检查该用户名是否已存在
    QString sql = "select * from users where username = ?";
    query.prepare(sql);
    query.bindValue(0, info[0]);
    bool ok = query.exec();
    if(!ok)
    {
        qDebug()<<"[KEmployee::employeeRegister]: "<<query.lastError();
        return;
    }
    if(query.first())
    {
        QMessageBox::information(NULL, "提示", "用户名已存在");
        return;
    }

    //插入注册用户信息
    QFile file(":/image/defaultAvatar.png");
    file.open(QIODevice::ReadOnly);
    QByteArray byteArray = file.readAll();
    sql = "insert into users(username,password,name,sex,birthday,phoneNumber,address,email,avatar) values(?,?,?,?,?,?,?,?,?)";
    query.prepare(sql);
    query.bindValue(0, info[0]);
    query.bindValue(1, info[1]);
    query.bindValue(2, info[2]);
    query.bindValue(3, info[3]);
    query.bindValue(4, info[4]);
    query.bindValue(5, info[5]);
    query.bindValue(6, info[6]);
    query.bindValue(7, info[7]);
    query.bindValue(8, byteArray);
    ok = query.exec();

    if(!ok)
    {
        qDebug()<<"[KEmployee::employeeRegister]: "<<query.lastError();
        return;
    }

    QMessageBox::information(NULL, "提示", "注册成功!");
}

void KEmployee::employeeUpdate(const QVector<QString> &info, const QString username)
{
    QSqlQuery query(m_pDatabase->getDatabase());

    //检查该用户名是否已存在
    QString sql = "update users set username = ?,password = ?, name = ?, sex = ?,phoneNumber = ?, email = ?, birthday = ?, address = ? where username = ?";
    query.prepare(sql);

    //info存储顺序  username, passwordOne, name, sex, birthday, phoneNumber, address, eMail
    query.bindValue(0, info[0]);
    query.bindValue(1, info[1]);
    query.bindValue(2, info[2]);
    query.bindValue(3, info[3]);
    query.bindValue(4, info[5]);
    query.bindValue(5, info[7]);
    query.bindValue(6, info[4]);
    query.bindValue(7, info[6]);
    query.bindValue(8, username);

    bool ok = query.exec();
    if(!ok)
    {
        qDebug()<<"[KEmployee::employeeUpdate]: "<<query.lastError();
        return;
    }

    QMessageBox::information(NULL, "提示", "用户信息修改成功!");
}

void KEmployee::employeeDelete(int row)
{
    m_model->setTable("users");
    m_model->select();

    m_model->removeRow(row);
    m_model->submitAll();
    m_model->select();

    m_model->removeColumn(0);
    m_model->removeColumn(1);
    m_model->removeColumn(7);
    m_model->setHeaderData(0, Qt::Horizontal, "用户名");
    m_model->setHeaderData(1, Qt::Horizontal, "姓名");
    m_model->setHeaderData(2, Qt::Horizontal, "性别");
    m_model->setHeaderData(3, Qt::Horizontal, "电话号码");
    m_model->setHeaderData(4, Qt::Horizontal, "邮箱");
    m_model->setHeaderData(5, Qt::Horizontal, "出生日期");
    m_model->setHeaderData(6, Qt::Horizontal, "地址");
}

void KEmployee::getEmployeeName(QVector<QString>& employeeName)
{
    QSqlQuery query(m_pDatabase->getDatabase());
    QString sql = "select name, username from users";
    query.prepare(sql);
    bool ok = query.exec();
    if(!ok)
    {
        qDebug()<<"[KEmployee::getEmployeeName]: "<<query.lastError();
        return;
    }

    while(query.next())
    {
        QString name = query.value(0).toString();
        QString username = query.value(1).toString();
        QString userInfo = name + "(" +  username + ")";
        employeeName.push_back(userInfo);
    }
}

void KEmployee::getEmployeeInfo(QVector<QString> &info, const QString& username)
{
    QSqlQuery query(m_pDatabase->getDatabase());
    QString sql = "select * from users where username = ?";
    query.prepare(sql);
    query.bindValue(0, username);
    bool ok = query.exec();
    if(!ok)
    {
        qDebug()<<"[KEmployee::getEmployeeInfo]: "<<query.lastError();
        return;
    }
    query.first();
    for(int i = 1; i <= 8; i ++)
        info.push_back(query.value(i).toString());
}
