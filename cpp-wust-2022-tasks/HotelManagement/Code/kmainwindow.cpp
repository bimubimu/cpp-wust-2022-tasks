#include "kmainwindow.h"
#include "ui_kmainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QMessageBox>

KMainWindow::KMainWindow(const QString& username, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KMainWindow)
{
    ui->setupUi(this);

    //关闭时释放内存
    this->setAttribute(Qt::WA_DeleteOnClose);

    //记录登录用户信息
    m_username = username;

    //初始化工具栏
    initToolBar();

    m_priceInfoWidget = new KPriceInfoWidget;
    m_roomInfoWidget = new KRoomInfoWidget;
    m_registerWidget = new KRegisterWidget;
    m_employeeWidget = new KEmployeeWidget;

    //初始化stackWidget
    initStackWidget();

    //显示时间
    QTimer *timerCalendar;//用来显示当前日期的定时器
    timerCalendar = new QTimer(this);//new一个QTimer对象
    connect(timerCalendar,&QTimer::timeout,this,&KMainWindow::showTime);//连接槽函数
    timerCalendar->start(1000);//每一秒溢出一次进入槽函数

}

KMainWindow::~KMainWindow()
{
    delete ui;
    delete m_ptoolBar;
    delete m_priceInfoWidget;
    delete m_roomInfoWidget;
    delete m_registerWidget;
    delete m_employeeWidget;
}

void KMainWindow::initStackWidget()
{
    ui->stackedWidget->addWidget(m_priceInfoWidget);
    ui->stackedWidget->addWidget(m_roomInfoWidget);
    ui->stackedWidget->addWidget(m_registerWidget);
    ui->stackedWidget->addWidget(m_employeeWidget);

    connect(m_ptoolBar, &ToolBar::priceClicked, [=](){
        ui->stackedWidget->setCurrentWidget(m_priceInfoWidget);
    });

    connect(m_ptoolBar, &ToolBar::roomClicked, [=](){
        ui->stackedWidget->setCurrentWidget(m_roomInfoWidget);
        m_roomInfoWidget->initRoomInfo();   //切换界面时更新房间信息
    });

    connect(m_ptoolBar, &ToolBar::registClicked, [=](){
        ui->stackedWidget->setCurrentWidget(m_registerWidget);
    });

    connect(m_ptoolBar, &ToolBar::employeeClicked, [=](){
        if(m_username == "admin")
            ui->stackedWidget->setCurrentWidget(m_employeeWidget);
        else
            QMessageBox::information(this, "提示", "没有管理员权限");
    });
}

void KMainWindow::initToolBar()
{
    m_ptoolBar = new ToolBar(m_username, this);
    addToolBar(Qt::LeftToolBarArea, m_ptoolBar->getToolBar());
}

void KMainWindow::showTime()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss");
    ui->labelTime->setText(str);
    ui->labelTime->setFont(QFont("华文琥珀", 30));
    ui->labelTime->setAlignment(Qt::AlignCenter);
}
