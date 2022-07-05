#include "kemployeewidget.h"
#include "ui_kemployeewidget.h"
#include <QMessageBox>
#include <QRegExp>
#include <QValidator>
#include <QSpinBox>
#include <QToolButton>
#include <QCalendarWidget>
#include <QVector>
#include <QDebug>

KEmployeeWidget::KEmployeeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KEmployeeWidget)
{
    ui->setupUi(this);
    m_employeeService = new KEmployee;

    inputLimit();
    initComboBoxEmployeeName();
    initTableView();
}

KEmployeeWidget::~KEmployeeWidget()
{
    delete ui;
    delete m_employeeService;
}

void KEmployeeWidget::inputLimit()
{
    //用户名 密码
    QRegExp regxUsername("^[a-zA-Z0-9_-]{1,16}$");
    QValidator *validatorUsername = new QRegExpValidator(regxUsername, this);
    ui->lineEditRegisterUserName->setValidator(validatorUsername);
    ui->lineEditRegisterPasswordOne->setValidator(validatorUsername);
    ui->lineEditRegisterPasswordTwo->setValidator(validatorUsername);
    ui->lineEditUpdateUserName->setValidator(validatorUsername);
    ui->lineEditUpdatePasswordOne->setValidator(validatorUsername);
    ui->lineEditUpdatePasswordTwo->setValidator(validatorUsername);

    //姓名
    QRegExp regxName("^([\u4e00-\u9fa5]{2,8}|[a-zA-Z.\\s]{2,20})$");
    QValidator *validatorName = new QRegExpValidator(regxName, this);
    ui->lineEditRegisterName->setValidator(validatorName);
    ui->lineEditUpdateName->setValidator(validatorName);

    //生日
    ui->dateEditRegisterBirthday->setCalendarPopup(true);
    ui->dateEditUpdateBirthday->setCalendarPopup(true);
    //限定年龄范围  18-40
    ui->dateEditRegisterBirthday->setDate(QDate::currentDate().addDays(-14600));
    ui->dateEditUpdateBirthday->setDate(QDate::currentDate().addDays(-14600));
    QDateTime beginTime = QDateTime::currentDateTime().addDays(-14600);
    QDateTime endTime = QDateTime::currentDateTime().addDays(-6570);
    ui->dateEditRegisterBirthday->setDateTimeRange(beginTime, endTime);
    ui->dateEditRegisterBirthday->setDisplayFormat("yyyy/MM/dd");
    ui->dateEditUpdateBirthday->setDateTimeRange(beginTime, endTime);
    ui->dateEditUpdateBirthday->setDisplayFormat("yyyy/MM/dd");
    //日历样式
    QSize s = QSize(32,32);
    QToolButton * toolbtn  = ui->dateEditRegisterBirthday->calendarWidget()->findChild<QToolButton * >("qt_calendar_prevmonth");
    toolbtn->setIcon(QPixmap(":/calendar/image/left.png"));
    toolbtn->setIconSize(s);
    toolbtn = ui->dateEditRegisterBirthday->calendarWidget()->findChild<QToolButton * >("qt_calendar_nextmonth");
    toolbtn->setIcon(QPixmap(":/calendar/image/right.png"));
    toolbtn->setIconSize(s);
    toolbtn = ui->dateEditUpdateBirthday->calendarWidget()->findChild<QToolButton * >("qt_calendar_prevmonth");
    toolbtn->setIcon(QPixmap(":/calendar/image/left.png"));
    toolbtn->setIconSize(s);
    toolbtn = ui->dateEditUpdateBirthday->calendarWidget()->findChild<QToolButton * >("qt_calendar_nextmonth");
    toolbtn->setIcon(QPixmap(":/calendar/image/right.png"));
    toolbtn->setIconSize(s);

    //手机号
    QRegExp regxPhoneNumber("^([1][3,4,5,6,7,8,9])[0-9]{9}$");
    QValidator *validatorPhoneNumber = new QRegExpValidator(regxPhoneNumber, this);
    ui->lineEditRegisterPhoneNumber->setValidator(validatorPhoneNumber);
    ui->lineEditUpdatePhoneNumber->setValidator(validatorPhoneNumber);

    //地址[\u4E00-\u9FA5]$
    QRegExp regxAddress("^[\u4E00-\u9FA5]{2,20}$");
    QValidator *validatorAddress = new QRegExpValidator(regxAddress, this);
    ui->lineEditRegisterAdress->setValidator(validatorAddress);
    ui->lineEditUpdateAdress->setValidator(validatorAddress);

    //邮箱  [a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\.[a-zA-Z0-9_-]+)+
    QRegExp regxEMail("^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)+$");
    QValidator *validatorEMail = new QRegExpValidator(regxEMail, this);
    ui->lineEditRegisterEMail->setValidator(validatorEMail);
    ui->lineEditRegisterEMail->setMaxLength(22);
    ui->lineEditUpdateEMail->setValidator(validatorEMail);
    ui->lineEditUpdateEMail->setMaxLength(22);
}

void KEmployeeWidget::initComboBoxEmployeeName()
{
    //先将索引清空
    ui->comboBoxUpdate->clear();

    QVector<QString> employeeName;
    m_employeeService->getEmployeeName(employeeName);
    //添加员工姓名索引
    for(int i = 0; i < employeeName.size(); i ++)
        ui->comboBoxUpdate->addItem(employeeName[i]);

    //默认不显示员工姓名
    ui->comboBoxUpdate->setCurrentIndex(-1);

    //输入框清空
    on_pushButtonUpdateClean_clicked();

    //输入框设置为不可用
    setUpdateInputDisabled(true);
}

void KEmployeeWidget::initTableView()
{
    //设置对应的model
    ui->tableView->setModel(m_employeeService->getTableModel());

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

void KEmployeeWidget::setUpdateInputDisabled(bool ok)
{
    ui->lineEditUpdateUserName->setDisabled(ok);
    ui->lineEditUpdatePasswordOne->setDisabled(ok);
    ui->lineEditUpdatePasswordTwo->setDisabled(ok);
    ui->lineEditUpdateName->setDisabled(ok);
    ui->radioButtonUpdateMale->setDisabled(ok);
    ui->radioButtonUpdateFemale->setDisabled(ok);
    ui->dateEditUpdateBirthday->setDisabled(ok);
    ui->lineEditUpdatePhoneNumber->setDisabled(ok);
    ui->lineEditUpdateAdress->setDisabled(ok);
    ui->lineEditUpdateEMail->setDisabled(ok);
}

void KEmployeeWidget::on_pushButtonRegister_clicked()
{
    //注册新员工
    QString username = ui->lineEditRegisterUserName->text();
    QString passwordOne = ui->lineEditRegisterPasswordOne->text();
    QString passwordOTwo = ui->lineEditRegisterPasswordTwo->text();
    QString name = ui->lineEditRegisterName->text();
    QString sex = "";
    if(ui->radioButtonRegisterMale->isChecked())
        sex = "男";
    if(ui->radioButtonRegisterFemale->isChecked())
        sex = "女";
    QString birthday = ui->dateEditRegisterBirthday->text();
    QString phoneNumber = ui->lineEditRegisterPhoneNumber->text();
    QString address = ui->lineEditRegisterAdress->text();
    QString eMail = ui->lineEditRegisterEMail->text();

    if(username == "" || passwordOne == "" || passwordOTwo == "" || name == "" || sex == "" ||
            birthday == "" || phoneNumber == "" || address =="" || eMail == "")
    {
        QMessageBox::information(this, "提示", "当前信息不完整");
        return;
    }

    if(passwordOne != passwordOTwo)
    {
        QMessageBox::information(this, "提示", "确认密码有误");
        return;
    }

    if(passwordOne.size() < 6 || passwordOTwo.size() < 6)
    {
        QMessageBox::information(this, "提示", "密码长度不合法");
        return;
    }

    if(phoneNumber.size() != 11)
    {
        QMessageBox::information(this, "提示", "手机号长度不合法");
        return;
    }


    QVector<QString> info = {username, passwordOne, name, sex, birthday, phoneNumber, address, eMail};
    m_employeeService->employeeRegister(info);

    //注册员工后更新一遍员工姓名索引
    initComboBoxEmployeeName();
}

void KEmployeeWidget::on_pushButtonRegisterClean_clicked()
{
    ui->lineEditRegisterUserName->clear();
    ui->lineEditRegisterPasswordOne->clear();
    ui->lineEditRegisterPasswordTwo->clear();
    ui->lineEditRegisterName->clear();
    ui->radioButtonRegisterMale->setAutoExclusive(false);
    ui->radioButtonRegisterMale->setChecked(false);
    ui->radioButtonRegisterMale->setAutoExclusive(true);
    ui->radioButtonRegisterFemale->setAutoExclusive(false);
    ui->radioButtonRegisterFemale->setChecked(false);
    ui->radioButtonRegisterFemale->setAutoExclusive(true);
    ui->dateEditRegisterBirthday->setDate(QDate::currentDate().addDays(-14600));
    ui->lineEditRegisterPhoneNumber->clear();
    ui->lineEditRegisterAdress->clear();
    ui->lineEditRegisterEMail->clear();
}


void KEmployeeWidget::on_pushButtonUpdateQuery_clicked()
{
    //截取索引信息中的用户名
    QString indexInfo = ui->comboBoxUpdate->currentText();
    if(indexInfo == "")
        return;
    QString username = "";
    for(int i = 0; i < indexInfo.size(); i ++)
    {
        if(indexInfo[i] == '(')
        {
            for(int j = i + 1; j < indexInfo.size() - 1; j ++)
                username += indexInfo[j] ;
            break;
        }
    }

    //通过用户名获取用户信息展现在信息框内
    QVector<QString> info;
    m_employeeService->getEmployeeInfo(info, username);
    //将输入框设置为可用
    setUpdateInputDisabled(false);

    ui->lineEditUpdateUserName->setText(info[0]);
    ui->lineEditUpdatePasswordOne->setText(info[1]);
    ui->lineEditUpdatePasswordTwo->setText(info[1]);
    ui->lineEditUpdateName->setText(info[2]);
    if(info[3] == "男")
        ui->radioButtonUpdateMale->setChecked(true);
    if(info[3] == "女")
        ui->radioButtonUpdateFemale->setChecked(true);
    ui->lineEditUpdatePhoneNumber->setText(info[4]);
    ui->lineEditUpdateEMail->setText(info[5]);
    ui->dateEditUpdateBirthday->setDate(QDate::fromString(info[6], "yyyy/MM/dd"));
    ui->lineEditUpdateAdress->setText(info[7]);
}

void KEmployeeWidget::on_comboBoxUpdate_currentIndexChanged(int index)
{
    on_pushButtonUpdateClean_clicked();
    setUpdateInputDisabled(true);
    index = 0;
}

void KEmployeeWidget::on_pushButtonUpdate_clicked()
{
    QString username = ui->lineEditUpdateUserName->text();
    QString passwordOne = ui->lineEditUpdatePasswordOne->text();
    QString passwordOTwo = ui->lineEditUpdatePasswordTwo->text();
    QString name = ui->lineEditUpdateName->text();
    QString sex = "";
    if(ui->radioButtonUpdateMale->isChecked())
        sex = "男";
    if(ui->radioButtonUpdateFemale->isChecked())
        sex = "女";
    QString birthday = ui->dateEditUpdateBirthday->text();
    QString phoneNumber = ui->lineEditUpdatePhoneNumber->text();
    QString address = ui->lineEditUpdateAdress->text();
    QString eMail = ui->lineEditUpdateEMail->text();

    if(username == "" || passwordOne == "" || passwordOTwo == "" || name == "" || sex == "" ||
            birthday == "" || phoneNumber == "" || address =="" || eMail == "")
    {
        QMessageBox::information(this, "提示", "当前信息不完整");
        return;
    }

    if(passwordOne != passwordOTwo)
    {
        QMessageBox::information(this, "提示", "确认密码有误");
        return;
    }

    if(passwordOne.size() < 6 || passwordOTwo.size() < 6)
    {
        QMessageBox::information(this, "提示", "密码长度不合法");
        return;
    }

    if(phoneNumber.size() != 11)
    {
        QMessageBox::information(this, "提示", "手机号长度不合法");
        return;
    }

    //截取索引信息中的用户名
    QString indexInfo = ui->comboBoxUpdate->currentText();
    QString preUsername = "";
    for(int i = 0; i < indexInfo.size(); i ++)
    {
        if(indexInfo[i] == '(')
        {
            for(int j = i + 1; j < indexInfo.size() - 1; j ++)
                preUsername += indexInfo[j] ;
            break;
        }
    }

    //检查用户名修改后是否会引起重名
    if(ui->lineEditUpdateUserName->text() != preUsername)
    {
        QMessageBox::information(this, "提示", "用户名不可修改");
        return;
    }

    //进行修改
    QVector<QString> info = {username, passwordOne, name, sex, birthday, phoneNumber, address, eMail};
    m_employeeService->employeeUpdate(info, preUsername);

    //重置修改界面
    initComboBoxEmployeeName();
}

void KEmployeeWidget::on_pushButtonUpdateClean_clicked()
{
    ui->lineEditUpdateUserName->clear();
    ui->lineEditUpdatePasswordOne->clear();
    ui->lineEditUpdatePasswordTwo->clear();
    ui->lineEditUpdateName->clear();
    ui->radioButtonUpdateMale->setAutoExclusive(false);
    ui->radioButtonUpdateMale->setChecked(false);
    ui->radioButtonUpdateMale->setAutoExclusive(true);
    ui->radioButtonUpdateFemale->setAutoExclusive(false);
    ui->radioButtonUpdateFemale->setChecked(false);
    ui->radioButtonUpdateFemale->setAutoExclusive(true);
    ui->dateEditUpdateBirthday->setDate(QDate::currentDate().addDays(-14600));
    ui->lineEditUpdatePhoneNumber->clear();
    ui->lineEditUpdateAdress->clear();
    ui->lineEditUpdateEMail->clear();
}

void KEmployeeWidget::on_pushButtonDelete_clicked()
{
    int row = ui->tableView->currentIndex().row();
    if(row == -1)
        return;
    if(row == 0)
    {
        QMessageBox::information(this, "提示", "管理员账号不能删除");
        return;
    }

    QMessageBox ::StandardButton result = QMessageBox::information(this, "提示", "确定要删除该员工信息吗？", QMessageBox::Yes|QMessageBox::No, QMessageBox::No);
    if(result == QMessageBox::No)
        return;
    else
    {
        m_employeeService->employeeDelete(row);
        initComboBoxEmployeeName();
    }
}

void KEmployeeWidget::on_tabWidget_currentChanged(int index)
{
    m_employeeService->getTableModel()->select();
    index = 0;
}
