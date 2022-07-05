#ifndef KEMPLOYEE_H
#define KEMPLOYEE_H

#include <QObject>
#include <QVector>
#include <QSqlTableModel>
#include "database/kdatabase.h"

class KEmployee : public QObject
{
    Q_OBJECT
public:
    explicit KEmployee(QObject *parent = nullptr);
    ~KEmployee();

    void initSqlModel();
    QSqlTableModel* getTableModel();

    //注册
    void employeeRegister(const QVector<QString>& info);
    //修改信息
    void employeeUpdate(const QVector<QString>& info, const QString username);
    //删除员工
    void employeeDelete(int row);
    //获取所有用户的用户名进行检索
    void getEmployeeName(QVector<QString>& employeeName);
    //获取用户信息
    void getEmployeeInfo(QVector<QString>& info, const QString& username);

private:
    KDataBase * m_pDatabase;
    QSqlTableModel * m_model;
};

#endif // KEMPLOYEE_H
