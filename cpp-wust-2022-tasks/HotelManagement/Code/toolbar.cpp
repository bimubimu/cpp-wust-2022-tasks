#include "toolbar.h"

#include <QToolButton>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QPainter>
#include <QHBoxLayout>

ToolBar::ToolBar(const QString& username, QWidget *parent) : QWidget(parent)
{
    QString connectionName = "toolBarConn";
    m_pDatabase = new KDataBase(connectionName);

    initToolBar(username, parent);
}

ToolBar::~ToolBar()
{
    delete m_pToolBar;
    delete m_pDatabase;
}

void ToolBar::initToolBar(const QString& username, QWidget *parent)
{
    //创建工具栏
    m_pToolBar = new QToolBar;

    m_pToolBar->setObjectName("toolbar");
    m_pToolBar->setAllowedAreas(Qt::LeftToolBarArea);
    m_pToolBar->setOrientation(Qt::Vertical);
    m_pToolBar->setMovable(false);

    //创建工具按钮
    QToolButton * price = new QToolButton;
    price->setObjectName("price");
    price->setToolTip("当日价格信息");

    QToolButton * room = new QToolButton;
    room->setObjectName("room");
    room->setToolTip("客房信息查询");

    QToolButton * regist = new QToolButton;
    regist->setObjectName("regist");
    regist->setToolTip("客房信息登记");

    QToolButton * employee = new QToolButton;
    employee->setObjectName("employee");
    employee->setToolTip("员工信息录入");

    //添加选中时画面显示
    QHBoxLayout * layoutPrice = new QHBoxLayout(price);
    QLabel * labelPrice = new QLabel;
    QLabel * labelPriceEmpty = new QLabel;
    labelPrice->setFixedSize(4, 80);
    layoutPrice->addWidget(labelPrice);
    layoutPrice->addWidget(labelPriceEmpty);
    layoutPrice->setMargin(0);
    labelPrice->setStyleSheet("background-color: rgb(51,51,51);");

    QHBoxLayout * layoutRoom = new QHBoxLayout(room);
    QLabel * labelRoom = new QLabel;
    QLabel * labelRoomEmpty = new QLabel;
    labelRoom->setFixedSize(4, 80);
    layoutRoom->addWidget(labelRoom);
    layoutRoom->addWidget(labelRoomEmpty);
    layoutRoom->setMargin(0);
    labelRoom->setStyleSheet("background-color: rgb(51,51,51);");

    QHBoxLayout * layoutRegist = new QHBoxLayout(regist);
    QLabel * labelRegist = new QLabel;
    QLabel * labelRegistEmpty = new QLabel;
    labelRegist->setFixedSize(4, 80);
    layoutRegist->addWidget(labelRegist);
    layoutRegist->addWidget(labelRegistEmpty);
    layoutRegist->setMargin(0);
    labelRegist->setStyleSheet("background-color: rgb(51,51,51);");

    QHBoxLayout * layoutEmployee = new QHBoxLayout(employee);
    QLabel * labelEmployee = new QLabel;
    QLabel * labelEmployeeEmpty = new QLabel;
    labelEmployee->setFixedSize(4, 80);
    layoutEmployee->addWidget(labelEmployee);
    layoutEmployee->addWidget(labelEmployeeEmpty);
    layoutEmployee->setMargin(0);
    labelEmployee->setStyleSheet("background-color: rgb(51,51,51);");



    //添加到工具栏
    m_pToolBar->addWidget(addUserAvatarInfo(username));  //添加用户头像到工具栏
    m_pToolBar->addWidget(addUserNameInfo(username));   //添加用户名到工具栏

    QLabel * labelEmpty = new QLabel;
    labelEmpty->setFixedSize(80, 30);
    m_pToolBar->addWidget(labelEmpty);

    m_pToolBar->addSeparator();
    m_pToolBar->addWidget(price);
    m_pToolBar->addWidget(room);
    m_pToolBar->addWidget(regist);
    m_pToolBar->addWidget(employee);

    m_pToolBar->setStyleSheet("#toolbar{"
                              "background-color:rgb(51,51,51);}"
                              "QToolBar QToolButton{"
                              "color:white;"
                              "font-size:20px;"
                              "min-width:80px;"
                              "min-height:80px}"
                              );

    parent->setStyleSheet("#price{"
                          "border-image:url(:/toolBar/image/priceInformation.png);}"
                          "#price:hover{"
                          "border-image:url(:/toolBar/image/priceInformation_press.png);}"
                          "#room{"
                          "border-image: url(:/toolBar/image/roomQuery.png);}"
                          "#room:hover{"
                          "border-image:url(:/toolBar/image/roomQuery_press.png);}"
                          "#regist{"
                          "border-image: url(:/toolBar/image/register.png);}"
                          "#regist:hover{"
                          "border-image:url(:/toolBar/image/register_press.png);}"
                          "#employee{"
                          "border-image: url(:/toolBar/image/employee.png);}"
                          "#employee:hover{"
                          "border-image: url(:/toolBar/image/employee_press.png);}");

    connect(price, &QToolButton::clicked, [=](){
        emit priceClicked();
        labelPrice->setStyleSheet("background-color: white;");
        labelRoom->setStyleSheet("background-color: rgb(51, 51, 51);");
        labelRegist->setStyleSheet("background-color: rgb(51, 51, 51);");
        labelEmployee->setStyleSheet("background-color: rgb(51, 51, 51);");

        parent->setStyleSheet(
                    "#price{"
                    "border-image: url(:/toolBar/image/priceInformation_press.png);}"
                    "#room{"
                    "border-image: url(:/toolBar/image/roomQuery.png);}"
                    "#room:hover{"
                    "border-image:url(:/toolBar/image/roomQuery_press.png);}"
                    "#regist{"
                    "border-image: url(:/toolBar/image/register.png);}"
                    "#regist:hover{"
                    "border-image:url(:/toolBar/image/register_press.png);}"
                    "#employee{"
                    "border-image: url(:/toolBar/image/employee.png);}"
                    "#employee:hover{"
                    "border-image:url(:/toolBar/image/employee_press.png);}");
    });

    connect(room, &QToolButton::clicked, [=](){
        emit roomClicked();
        labelPrice->setStyleSheet("background-color: rgb(51, 51, 51);");
        labelRoom->setStyleSheet("background-color: white;");
        labelRegist->setStyleSheet("background-color: rgb(51, 51, 51);");
        labelEmployee->setStyleSheet("background-color: rgb(51, 51, 51);");

        parent->setStyleSheet(
                    "#price{"
                    "border-image: url(:/toolBar/image/priceInformation.png);}"
                    "#price:hover{"
                    "border-image:url(:/toolBar/image/priceInformation_press.png);}"
                    "#room{"
                    "border-image: url(:/toolBar/image/roomQuery_press.png);}"
                    "#regist{"
                    "border-image: url(:/toolBar/image/register.png);}"
                    "#regist:hover{"
                    "border-image:url(:/toolBar/image/register_press.png);}"
                    "#employee{"
                    "border-image: url(:/toolBar/image/employee.png);}"
                    "#employee:hover{"
                    "border-image:url(:/toolBar/image/employee_press.png);}");
    });

    connect(regist, &QToolButton::clicked, [=](){
        emit registClicked();
        labelPrice->setStyleSheet("background-color: rgb(51, 51, 51);");
        labelRoom->setStyleSheet("background-color: rgb(51, 51, 51);");
        labelRegist->setStyleSheet("background-color: white;");
        labelEmployee->setStyleSheet("background-color: rgb(51, 51, 51);");

        parent->setStyleSheet(
                    "#price{"
                    "border-image: url(:/toolBar/image/priceInformation.png);}"
                    "#price:hover{"
                    "border-image:url(:/toolBar/image/priceInformation_press.png);}"
                    "#room{"
                    "border-image: url(:/toolBar/image/roomQuery.png);}"
                    "#room:hover{"
                    "border-image:url(:/toolBar/image/roomQuery_press.png);}"
                    "#regist{"
                    "border-image: url(:/toolBar/image/register_press.png);}"
                    "#employee{"
                    "border-image: url(:/toolBar/image/employee.png);}"
                    "#employee:hover{"
                    "border-image:url(:/toolBar/image/employee_press.png);}");
    });

    connect(employee, &QToolButton::clicked, [=](){
        emit employeeClicked();
        labelPrice->setStyleSheet("background-color: rgb(51, 51, 51);");
        labelRoom->setStyleSheet("background-color: rgb(51, 51, 51);");
        labelRegist->setStyleSheet("background-color: rgb(51, 51, 51);");
        labelEmployee->setStyleSheet("background-color: white;");

        parent->setStyleSheet(
                    "#price{"
                    "border-image: url(:/toolBar/image/priceInformation.png);}"
                    "#price:hover{"
                    "border-image:url(:/toolBar/image/priceInformation_press.png);}"
                    "#room{"
                    "border-image: url(:/toolBar/image/roomQuery.png);}"
                    "#room:hover{"
                    "border-image:url(:/toolBar/image/roomQuery_press.png);}"
                    "#regist{"
                    "border-image: url(:/toolBar/image/register.png);}"
                    "#regist:hover{"
                    "border-image:url(:/toolBar/image/register_press.png);}"
                    "#employee{"
                    "border-image: url(:/toolBar/image/employee_press.png);}");
    });
}

QLabel *ToolBar::addUserAvatarInfo(const QString &username)
{
    QSqlQuery query(m_pDatabase->getDatabase());

    QString sql = "select avatar from users where username = ?";
    query.prepare(sql);
    query.bindValue(0, username);

    bool ok = query.exec();

    if(!ok)
    {
        qDebug()<<"[ToolBar::addUserAvatarInfo]: "<<query.lastError().text();
    }

    query.first();
    QByteArray outByteArray = query.value(0).toByteArray();
    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData(outByteArray);

    //调整图片为圆图
    QPixmap pixmap(80, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QPainterPath path;
    path.addEllipse(8, 8, 65, 65);
    painter.setClipPath(path);
    painter.drawPixmap(8, 8, 65, 65, outPixmap);

    QLabel * label = new QLabel;
    label->setFixedSize(80, 80);
    label->setPixmap(pixmap);

    return label;
}

QLabel* ToolBar::addUserNameInfo(const QString &username)
{
    QLabel * labelName = new QLabel;
    QSqlQuery query(m_pDatabase->getDatabase());
    QString sql = "select name from users where username = ?";

    query.prepare(sql);
    query.bindValue(0, username);
    bool ok = query.exec();

    if(!ok)
    {
        qDebug()<<"[ToolBar::addUserNameInfo]: "<<query.lastError().text();
        labelName->setText("");
        return labelName;
    }

    query.first();
    labelName->setText(query.value(0).toString());

    //设置label格式
    labelName->setFixedSize(80, 30);
    labelName->setAlignment(Qt::AlignCenter);
    labelName->setFont(QFont("幼圆", 12, QFont::Bold));
    labelName->setStyleSheet("color:white");

    return labelName;
}


QToolBar* ToolBar::getToolBar()
{
    return m_pToolBar;
}
