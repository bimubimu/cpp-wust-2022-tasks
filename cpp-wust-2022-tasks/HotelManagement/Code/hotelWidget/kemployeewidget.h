#ifndef KEMPLOYEEWIDGET_H
#define KEMPLOYEEWIDGET_H

#include <QWidget>
#include "hotelService/kemployee.h"

namespace Ui {
class KEmployeeWidget;
}

class KEmployeeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit KEmployeeWidget(QWidget *parent = 0);
    ~KEmployeeWidget();

    void inputLimit();
    void initComboBoxEmployeeName();
    void initTableView();
    void setUpdateInputDisabled(bool ok);

private slots:
    //注册
    void on_pushButtonRegister_clicked();
    //注册界面清空
    void on_pushButtonRegisterClean_clicked();
    //查询员工信息进行修改
    void on_pushButtonUpdateQuery_clicked();
    //切换用户更新
    void on_comboBoxUpdate_currentIndexChanged(int index);
    //修改
    void on_pushButtonUpdate_clicked();
    //更新界面清空
    void on_pushButtonUpdateClean_clicked();
    //删除员工
    void on_pushButtonDelete_clicked();
    //点击员工查询页面时更新
    void on_tabWidget_currentChanged(int index);

private:
    Ui::KEmployeeWidget *ui;
    KEmployee * m_employeeService;
};

#endif // KEMPLOYEEWIDGET_H
