#ifndef KMAINWINDOW_H
#define KMAINWINDOW_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QMainWindow>
#include <QPainter>
#include <QToolBar>
#include <QToolButton>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlRecord>
#include <QMessageBox>
#include <QDateTime>



namespace Ui {
class KMainWindow;
}

class KMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit KMainWindow(QString userId, QWidget *parent = 0);
    ~KMainWindow();

    //建立数据库连接
    void createSqlConn();

    void initLimit();
    void initTableView();
    void initToolBar(QString userId);
    void initComboBox();
    void initOrders();

public slots:
    //入库管理:
    //点击入库
    void onPushButtonStorageClicked();
    //点击清仓
    void onPushButtonClearClicked();


    //订单管理:
    //选择类型
    void onComboBoxTypeSellCurrentIndexChanged();
    //选择商品
    void onComboBoxNameSellCurrentIndexChanged();
    //选择出售数量
    void onSpinBoxSellNumberValueChanged();
    //出售
    void onPushButtonSellClicked();
    //下单
    void onPushButtonOrderClicked();

private:
    Ui::KMainWindow *ui;
    QSqlDatabase m_db;
    QSqlTableModel * m_model;
    QString m_userId;

    int m_orderId;
    double m_orderTotalPrice;
};

#endif // KMAINWINDOW_H
