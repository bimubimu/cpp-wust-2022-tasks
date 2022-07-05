#include "kregisterwidget.h"
#include "ui_kregisterwidget.h"

#include <QCalendarWidget>
#include <QSpinBox>
#include <QToolButton>
#include <QDebug>
#include <QMessageBox>
#include <QVector>
#include <QRegExp>
#include <QValidator>


KRegisterWidget::KRegisterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KRegisterWidget)
{
    ui->setupUi(this);

    m_pRegisterService = new KRegister;

    //初始化日历弹出、日期选择范围等操作
    initTime();
    initCalendar();

    //正则表达式限制输入
    initInputLimitCheckOut();
    initInputLimitQuery();

    // 初始化查询界面
    initTableView();

}

KRegisterWidget::~KRegisterWidget()
{
    delete ui;
    delete m_pRegisterService;
}

void KRegisterWidget::initTime()
{
    //设置显示当前时间
    ui->dateEditOccupancy->setDate(QDate::currentDate());
    ui->dateEditOccupancy->setDisplayFormat("yyyy/MM/dd");

    //限定离店日期范围
    QDateTime beginTime = QDateTime::currentDateTime().addDays(1);
    QDateTime endTime = beginTime.addDays(30);
    ui->dateEditLeave->setDate(QDate::currentDate().addDays(1));
    ui->dateEditLeave->setDateTimeRange(beginTime, endTime);

    //退房时间
    ui->dateEditCheckOut->setDate(QDate::currentDate());
    ui->dateEditCheckOut->setDisplayFormat("yyyy/MM/dd");

}

void KRegisterWidget::initCalendar()
{
    ui->dateEditOccupancy->setCalendarPopup(true);
    ui->dateEditLeave->setCalendarPopup(true);   //设置日历弹出
    ui->dateEditCheckOut->setCalendarPopup(true);

    QTextCharFormat format;  //字体风格
    format.setForeground(Qt::red);
    QCalendarWidget * dateEditCalendarWidget = ui->dateEditLeave->calendarWidget();

    dateEditCalendarWidget->setWeekdayTextFormat(Qt::Saturday, format);
    dateEditCalendarWidget->setWeekdayTextFormat(Qt::Sunday, format);

    dateEditCalendarWidget->setFixedSize(400,250);
    dateEditCalendarWidget->findChildren<QWidget*>().value(0)->setCursor(Qt::PointingHandCursor);
    dateEditCalendarWidget->findChildren<QSpinBox*>().value(0)->setAlignment(Qt::AlignCenter);

    dateEditCalendarWidget->findChildren<QSpinBox*>().value(0)->setButtonSymbols(QSpinBox::NoButtons);
    dateEditCalendarWidget->findChildren<QSpinBox*>().value(0)->setFocusPolicy(Qt::NoFocus);
    dateEditCalendarWidget->findChildren<QSpinBox*>().value(0)->setReadOnly(true);

    QList<QToolButton * > toolbtn_list = ui->dateEditLeave->calendarWidget()->findChildren<QToolButton*>();
    for (int var = 0; var < toolbtn_list.size(); ++var)
    {
        toolbtn_list.value(var)->setCursor(Qt::PointingHandCursor);
    }

    QSize s = QSize(32,32);
    QToolButton * toolbtn  = ui->dateEditLeave->calendarWidget()->findChild<QToolButton * >("qt_calendar_prevmonth");
    toolbtn->setIcon(QPixmap(":/calendar/image/left.png"));
    toolbtn->setIconSize(s);
    toolbtn = ui->dateEditLeave->calendarWidget()->findChild<QToolButton * >("qt_calendar_nextmonth");
    toolbtn->setIcon(QPixmap(":/calendar/image/right.png"));
    toolbtn->setIconSize(s);
}

void KRegisterWidget::initInputLimitCheckOut()
{
    //姓名  中英文不会同时出现
    QRegExp regxName("^([\u4e00-\u9fa5]{2,8}|[a-zA-Z.\\s]{2,20})$");
    QValidator *validatorName = new QRegExpValidator(regxName, this);
    ui->lineEditName->setValidator(validatorName);

    //手机号
    QRegExp regxPhoneNumber("^([1][3,4,5,6,7,8,9])[0-9]{9}$");
    QValidator *validatorPhoneNumber = new QRegExpValidator(regxPhoneNumber, this);
    ui->lineEditPhoneNumber->setValidator(validatorPhoneNumber);

    //身份证号
    QRegExp regxIdCard("^[1-9]\\d{5}(18|19|20|(3\\d))\\d{2}((0[1-9])|(1[0-2]))(([0-2][1-9])|10|20|30|31)\\d{3}[0-9Xx]$");
    QValidator *validatorIdCard = new QRegExpValidator(regxIdCard, this);
    ui->lineEditIdCard->setValidator(validatorIdCard);
}

void KRegisterWidget::initInputLimitQuery()
{
    //限制房间号
    QRegExp regxRoomNumber("^[1-4][0][1-6]$");
    QValidator *validatorRoomNumber = new QRegExpValidator(regxRoomNumber, this);
    ui->lineEditQueryRoomNumber->setValidator(validatorRoomNumber);

    //限制姓名
    QRegExp regxName("^([\u4e00-\u9fa5]{2,8}|[a-zA-Z.\\s]{2,20})$");
    QValidator *validatorName = new QRegExpValidator(regxName, this);
    ui->lineEditQueryName->setValidator(validatorName);

    //限制身份证号
    QRegExp regxIdCard("^[1-9]\\d{5}(18|19|20|(3\\d))\\d{2}((0[1-9])|(1[0-2]))(([0-2][1-9])|10|20|30|31)\\d{3}[0-9Xx]$");
    QValidator *validatorIdCard = new QRegExpValidator(regxIdCard, this);
    ui->lineEditQueryIdCard->setValidator(validatorIdCard);
}

void KRegisterWidget::initTableView()
{
    //设置对应的model
    ui->tableView->setModel(m_pRegisterService->getTableModel());

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setMinimumHeight(40);
    ui->tableView->horizontalHeader()->setFont(QFont("微软雅黑", 10));
    ui->tableView->setFont(QFont("微软雅黑", 13));
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setFocusPolicy(Qt::NoFocus);
}

void KRegisterWidget::on_pushButtonRegister_clicked()
{
    //记录住店时间
    QString timeCheckIn = ui->dateEditOccupancy->text();
    QString timeCheckOut = ui->dateEditLeave->text();

    //记录客人信息
    QString name = ui->lineEditName->text();
    QString idCard = ui->lineEditIdCard->text();
    QString phoneNumber = ui->lineEditPhoneNumber->text();
    QString roomNumber = ui->comboBoxRoomNumber->currentText();

    //记录客人权限
    QString permission;
    if(ui->radioButtonNormal->isChecked())
        permission = "NORMAL";
    if(ui->radioButtonVIP->isChecked())
        permission = "VIP";

    if(name == "" || idCard == "" || phoneNumber == "" || roomNumber == "" || permission == "")
    {
        QMessageBox::information(this, "提示", "用户信息不完整");
        return;
    }

    if(idCard.size() != 18)
    {
        QMessageBox::information(this, "提示", "身份证号长度不合法");
        return;
    }

    if(phoneNumber.size() != 11)
    {
        QMessageBox::information(this, "提示", "手机号长度不合法");
        return;
    }

    //封装用户信息
    QVector<QString> customerInfo;
    customerInfo.push_back(name);
    customerInfo.push_back(idCard);
    customerInfo.push_back(phoneNumber);
    customerInfo.push_back(roomNumber);
    customerInfo.push_back(permission);
    customerInfo.push_back(timeCheckIn);
    customerInfo.push_back(timeCheckOut);

    //添加用户入住信息
    m_pRegisterService->checkIn(customerInfo);
}

void KRegisterWidget::on_pushButtonClean_clicked()
{
    initTime();
    ui->lineEditName->setText("");
    ui->lineEditIdCard->setText("");
    ui->lineEditPhoneNumber->setText("");
    ui->comboBoxRoomNumber->setCurrentIndex(0);
    ui->radioButtonVIP->setAutoExclusive(false);
    ui->radioButtonVIP->setChecked(false);
    ui->radioButtonVIP->setAutoExclusive(true);
    ui->radioButtonNormal->setAutoExclusive(false);
    ui->radioButtonNormal->setChecked(false);
    ui->radioButtonNormal->setAutoExclusive(true);
}

void KRegisterWidget::on_pushButtonCheckOut_clicked()
{
    QString roomNumber = ui->comboBoxCheckOut->currentText();
    QString timeCheckOut = ui->dateEditCheckOut->text();

    //客人姓名、(房间号)、房间类型、入住离开时间、(实际离开时间)、入住总时间、权限、房间单价、总价
    QVector<QString> info;
    m_pRegisterService->checkOut(roomNumber, timeCheckOut, info);
    if(info.size() == 0)
        return;

    QString userName = info[0];
    QString roomType = info[1];
    QString timeIn = info[2];
    QString timeOut = info[3];
    QString days = info[4];
    QString permission = info[5];
    QString price = info[6];
    QString consume = info[7];

    ui->textEdit->append("顾客姓名：" + userName);
    ui->textEdit->append("权限：" + permission);
    ui->textEdit->append("房间号：" + roomNumber);
    ui->textEdit->append("房间类型：" + roomType);
    ui->textEdit->append("房间单价:" + price);
    ui->textEdit->append("入住时间：" + timeIn);
    ui->textEdit->append("预约退房时间：" + timeOut);
    ui->textEdit->append("实际退房时间：" + timeCheckOut);
    ui->textEdit->append("入住天数(不满一天按一天计算)：" + days);
    ui->textEdit->append("总价应付：" + consume);
    ui->textEdit->append("退房成功!\t操作时间" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    ui->textEdit->append("----------------------------------------------------------------------------\n");
}

void KRegisterWidget::on_pushButtonRoomNumber_clicked()
{
    m_pRegisterService->queryInRoomNumber(ui->lineEditQueryRoomNumber->text());     //做输入限制
}

void KRegisterWidget::on_pushButtonName_clicked()
{
    m_pRegisterService->queryInName(ui->lineEditQueryName->text());
}

void KRegisterWidget::on_pushButtonIdCard_clicked()
{
    m_pRegisterService->queryInIdCard(ui->lineEditQueryIdCard->text());
}

void KRegisterWidget::on_tabWidget_currentChanged(int index)
{
    //界面切换后更新
    m_pRegisterService->getTableModel()->select();
    index = 0;
}
