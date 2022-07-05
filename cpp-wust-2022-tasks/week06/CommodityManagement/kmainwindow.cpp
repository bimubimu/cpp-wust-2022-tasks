#include "kmainwindow.h"
#include "ui_kmainwindow.h"

KMainWindow::KMainWindow(QString userId, QWidget *parent) :
    QMainWindow(parent),
    m_userId(userId),
    ui(new Ui::KMainWindow)
{
    ui->setupUi(this);

    m_orderId = 1;
    m_orderTotalPrice = 0;

    this->setAttribute(Qt::WA_DeleteOnClose);

    createSqlConn();

    //初始化输入限制
    initLimit();


    initTableView();

    initToolBar(userId);

    initComboBox();

    initOrders();

    //设置订单字体
    QFont font = QFont("Microsoft YaHei",13,2);
    ui->textEdit->setFont(font);

    //点击入库
    connect(ui->pushButtonStorage, &QPushButton::clicked, this, &KMainWindow::onPushButtonStorageClicked);

    //点击清仓
    connect(ui->pushButtonClear, &QPushButton::clicked, this, &KMainWindow::onPushButtonClearClicked);

    //预售订单选中类别
    void(QComboBox:: *typeSignal)(int) = &QComboBox::currentIndexChanged;
    connect(ui->comboBoxTypeSell, typeSignal, this, &KMainWindow::onComboBoxTypeSellCurrentIndexChanged);

    //预售订单选中物品
    void(QComboBox:: *nameSignal)(int) = &QComboBox::currentIndexChanged;
    connect(ui->comboBoxNameSell, nameSignal, this, &KMainWindow::onComboBoxNameSellCurrentIndexChanged);

    //选择出售数量
    void(QSpinBox:: *numberSignal)(int) = &QSpinBox::valueChanged;
    connect(ui->spinBoxSellNumber, numberSignal, this, &KMainWindow::onSpinBoxSellNumberValueChanged);

    //出售
    connect(ui->pushButtonSell, &QPushButton::clicked, this, &KMainWindow::onPushButtonSellClicked);

    //下单
    connect(ui->pushButtonOrder, &QPushButton::clicked, this, &KMainWindow::onPushButtonOrderClicked);
}


KMainWindow::~KMainWindow()
{
    m_db.close();
    delete ui;
}


void KMainWindow::createSqlConn()
{
    //连接数据库
    QString connectionName = "manegeConnection";
    m_db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    m_db.setDatabaseName("company.db");
    bool ok = m_db.open();

    if(!ok)
    {
        QMessageBox::warning(NULL, "数据库操作", "数据库打开失败",QMessageBox::Yes, QMessageBox::Yes);
        qDebug()<<m_db.lastError().text();
        return;
    }
}

void KMainWindow::initLimit()
{
    QRegExp regxId("[0-9]+$");
    QRegExp regxPrice("[1-9][0-9]+$");

    QValidator *validatorId = new QRegExpValidator(regxId, this);
    QValidator *validatorPrice = new QRegExpValidator(regxPrice, this);

    //限制输入类型
    ui->lineEditId->setValidator(validatorId);
    ui->lineEditPurchasePrice->setValidator(validatorPrice);
    ui->lineEditSellingPrice->setValidator(validatorPrice);

    //限制输入长度
    ui->lineEditId->setMaxLength(6);
    ui->lineEditName->setMaxLength(12);
    ui->lineEditPurchasePrice->setMaxLength(6);
    ui->lineEditSellingPrice->setMaxLength(6);
}

void KMainWindow::initTableView()
{
    m_model = new QSqlTableModel(this, m_db);

    //设置模型与具体的表相关联
    m_model->setTable("commodity");

    //设置提交方式为手动提交
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //选取表中所有的行数
    m_model->select();

    //重新设置显示表头的信息
    m_model->setHeaderData(0, Qt::Horizontal, "编号");
    m_model->setHeaderData(1, Qt::Horizontal, "商品名称");
    m_model->setHeaderData(2, Qt::Horizontal, "类别");
    m_model->setHeaderData(3, Qt::Horizontal, "进价(¥)");
    m_model->setHeaderData(4, Qt::Horizontal, "售价(¥)");
    m_model->setHeaderData(5, Qt::Horizontal, "库存");


    //设置view对应的model
    ui->tableView->setModel(m_model);

    //设置表格不可编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //设置单元格颜色交替
    ui->tableView->setAlternatingRowColors(true);

    // 列自适应空间大小
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //设置表头最小高度
    ui->tableView->horizontalHeader()->setMinimumHeight(40);

    //隐藏行头
    ui->tableView->verticalHeader()->hide();

    //设置整行选中
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    //设置表格不获取焦点
    ui->tableView->setFocusPolicy(Qt::NoFocus);

}


void KMainWindow::initToolBar(QString userId)
{
    //新建工具栏
    QToolBar* toolBar = new QToolBar;
    toolBar->setMovable(false);
    addToolBar(Qt::LeftToolBarArea, toolBar);
    toolBar->setStyleSheet("background-color:rgb(60,60,60);");
    toolBar->setIconSize(QSize(60,60));

    //新建新品入库入库按钮
    QToolButton* btnWarehouse = new QToolButton;
    btnWarehouse->setIcon(QIcon(":/image/CommodityWarehousing.png"));
    btnWarehouse->setText("新品入库");
    btnWarehouse->setStyleSheet("QToolButton{font:20px;color:white;}");
    btnWarehouse->setFixedSize(100,100);
    btnWarehouse->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    //新建预售订单按钮
    QToolButton* btnPreSale = new QToolButton;
    btnPreSale->setIcon(QIcon(":/image/Presale.png"));
    btnPreSale->setText("预售订单");
    btnPreSale->setStyleSheet("QToolButton{font:20px;color:white;}");
    btnPreSale->setFixedSize(100,100);
    btnPreSale->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    //显示用户头像框 avatar
    QLabel* LabelAvatar = new QLabel;
    LabelAvatar->setFixedSize(100, 100);
    LabelAvatar->setAlignment(Qt::AlignCenter);

    QPixmap pixmapa(":/image/defaultAvatar.png");
    QPixmap pixmap(70, 70);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QPainterPath path;
    path.addEllipse(0, 0, 70, 70);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, 70, 70, pixmapa);
    LabelAvatar->setPixmap(pixmap);



    //通过userId获取用户姓名，在toolbar上显示
    QSqlQuery query(m_db);
    query.prepare("select name from employee where id = ?");
    query.bindValue(0, userId.toInt());
    query.exec();

    QString username;
    if(query.next())
        username = query.value(0).toString();

    QLabel * labelUser = new QLabel;
    labelUser->setFixedSize(100,30);
    labelUser->setText(username);
    labelUser->setAlignment(Qt::AlignCenter);
    labelUser->setStyleSheet("QLabel{font:25px;color:white;}");

    QLabel * labelBlank = new QLabel;
    labelBlank->setFixedSize(100,30);


    //工具栏添加信息和操作
    toolBar->addWidget(LabelAvatar);
    toolBar->addWidget(labelUser);
    toolBar->addWidget(labelBlank);
    toolBar->addWidget(btnWarehouse);
    //toolBar->addSeparator();
    toolBar->addWidget(btnPreSale);


    //设置信号槽
    connect(btnWarehouse,&QToolButton::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(0);

        //回到新品入库后对未处理的订单清空
        m_model->revertAll();
        ui->textEdit->clear();

        //将下单按钮关闭
        ui->pushButtonOrder->setEnabled(false);
    });

    connect(btnPreSale,&QToolButton::clicked, [=](){
        //转到预售订单时对预售订单内容初始化
        initComboBox();
        initOrders();
        ui->stackedWidget->setCurrentIndex(1);
    });

    //美化
    QPalette q;
    q.setColor(QPalette::ButtonText, Qt::white);
    btnWarehouse->setPalette(q);
    btnPreSale->setPalette(q);


}

void KMainWindow::initComboBox()
{
    ui->comboBoxNameSell->clear();
    int row = m_model->rowCount();

    for(int i = 0; i < row; i ++)
    {
        QString name = m_model->index(i, 1).data().toString();
        ui->comboBoxNameSell->addItem(name);
    }

    //默认 不显示物品，需手动选择
    ui->comboBoxNameSell->setCurrentIndex(-1);
}

void KMainWindow::initOrders()
{
    ui->lineEditPrice->setText("");
    ui->lineEditNumber->setText("");
    ui->lineEditTotalPrice->setText("");
    ui->spinBoxSellNumber->setValue(1);
}

void KMainWindow::onPushButtonStorageClicked()
{
    //信息不完整
    if(ui->lineEditId->text().isEmpty() ||
            ui->lineEditName->text().isEmpty() ||
            ui->lineEditPurchasePrice->text().isEmpty() ||
            ui->lineEditSellingPrice->text().isEmpty())
        return;

    //获取入库信息
    QString id = ui->lineEditId->text();
    QString name = ui->lineEditName->text();
    QString type = ui->comboBoxType->currentText();
    double purchasePrice = ui->lineEditPurchasePrice->text().toDouble();
    double sellingPrice = ui->lineEditSellingPrice->text().toDouble();
    int number = ui->spinBoxNumber->text().toInt();

    for(int i = 0; i < m_model->rowCount(); i ++)
    {
        //获取一行信息
        QSqlRecord record = m_model->record(i);

        //同id情况
        if(record.value("id") == id)
        {

            if(record.value("name") == name && record.value("type") == type &&
                    record.value("purchase_price") == purchasePrice && record.value("selling_price") == sellingPrice)
            {
                //更改商品库存数量
                record.setValue("number", ui->spinBoxNumber->text().toInt() + record.value("number").toInt());

                //重新设置对应的model
                m_model->setRecord(i, record);
                //重新写到数据库中
                m_model->submitAll();
                return;
            }

            //不同商品使用相同id
            else
                return;
        }

        //同名情况
        if(record.value("name") == name)
        {

            if(record.value("id") == id && record.value("type") == type &&
                    record.value("purchase_price") == purchasePrice && record.value("selling_price") == sellingPrice)
            {
                //更改商品库存数量
                record.setValue("number", ui->spinBoxNumber->text().toInt() + record.value("number").toInt());

                //重新设置对应的model
                m_model->setRecord(i, record);
                //重新写到数据库中
                m_model->submitAll();
                return;
            }

            //不同id同名不合法
            else
                return;
        }

    }

    if(purchasePrice >= sellingPrice)
    {
        QMessageBox::information(this, "提示", "该状态不盈利，谨慎考虑！");
        return;
    }

    //插入一行
    int line = m_model->rowCount();
    m_model->insertRow(line);

    //(line, 0)单元格插入数据
    m_model->setData(m_model->index(line, 0), id);
    m_model->setData(m_model->index(line, 1), name);
    m_model->setData(m_model->index(line, 2), type);
    m_model->setData(m_model->index(line, 3), purchasePrice);
    m_model->setData(m_model->index(line, 4), sellingPrice);
    m_model->setData(m_model->index(line, 5), number);

    //提交并更新数据库
    m_model->submitAll();
}

void KMainWindow::onPushButtonClearClicked()
{
    int curRow = ui->tableView->currentIndex().row();

    m_model->removeRow(curRow);

    m_model->submitAll();

}

void KMainWindow::onComboBoxTypeSellCurrentIndexChanged()
{
    //获取类型
    QString type = ui->comboBoxTypeSell->currentText();

    if(type == "全选")
    {
        initComboBox();
        initOrders();
        return;
    }

    //清空comboBox商品名称
    ui->comboBoxNameSell->clear();

    for(int i = 0; i < m_model->rowCount(); i ++)
    {
        //获取一行信息
        QSqlRecord record = m_model->record(i);

        if(record.value("type") == type)
        {
            QString name = m_model->index(i, 1).data().toString();
            ui->comboBoxNameSell->addItem(name);
        }
    }

    //默认不显示
    ui->comboBoxNameSell->setCurrentIndex(-1);
    initOrders();
}

void KMainWindow::onComboBoxNameSellCurrentIndexChanged()
{
    //获取商品名称
    QString name = ui->comboBoxNameSell->currentText();

    double sellingPrice;
    int number;

    for(int i = 0; i < m_model->rowCount(); i ++)
    {
        //获取一行信息
        QSqlRecord record = m_model->record(i);

        if(record.value("name") == name)
        {
            sellingPrice = record.value("selling_price").toDouble();
            number = record.value("number").toInt();
            break;
        }

    }

    //出售数量更新为1
    ui->spinBoxSellNumber->setValue(1);

    ui->lineEditPrice->setText(QString::number(sellingPrice));
    ui->lineEditNumber->setText(QString::number(number));
    ui->lineEditTotalPrice->setText(QString::number(sellingPrice));
}

void KMainWindow::onSpinBoxSellNumberValueChanged()
{
    if(ui->comboBoxNameSell->currentIndex() == -1)
    {
        ui->spinBoxSellNumber->setValue(1);
        return;
    }

    //获取出售量和库存量
    int sellNumber = ui->spinBoxSellNumber->value();
    int totalNumber = ui->lineEditNumber->text().toInt();

    if(sellNumber > totalNumber)
    {
        //为spinBox设置上限
        ui->spinBoxSellNumber->setValue(totalNumber);

        //计算出总价
        double price = ui->lineEditPrice->text().toDouble();
        double totalPrice = price * totalNumber;

        //设置总价
        ui->lineEditTotalPrice->setText(QString::number(totalPrice));
        return;
    }

    //计算出总价
    double price = ui->lineEditPrice->text().toDouble();
    double totalPrice = price * sellNumber;

    //设置总价
    ui->lineEditTotalPrice->setText(QString::number(totalPrice));
}


void KMainWindow::onPushButtonSellClicked()
{
    //未选中商品时不进行操作
    if(ui->comboBoxNameSell->currentText().isEmpty())
        return;

    QDateTime currentDateTime =QDateTime::currentDateTime();
    QString currentTime = currentDateTime.toString("hh:mm:ss");

    QString name = ui->comboBoxNameSell->currentText();
    QString number = ui->spinBoxSellNumber->text();
    QString price = ui->lineEditPrice->text();
    QString totalPrice = ui->lineEditTotalPrice->text();

    //库存量为0时不做操作
    if(ui->lineEditNumber->text().toInt() == 0)
    {
        qDebug()<<1;
        return;
    }

    //打印信息
    ui->textEdit->append("----------------------------------------------------------------------");
    ui->textEdit->append(currentTime + "\t售出：" + name);
    ui->textEdit->append("                数量：" + number + "    单价：" + price + "    总价：" + totalPrice + "\n");

    //更新记录
    for(int i = 0; i < m_model->rowCount(); i ++)
    {
        //获取一行信息
        QSqlRecord record = m_model->record(i);

        //如果改行信息使我们需要的
        if(record.value("name") == name)
        {
            //计算订单总价
            m_orderTotalPrice += totalPrice.toDouble();

            //计算剩余量
            int residualNumber = ui->lineEditNumber->text().toInt() - number.toInt();

            //将总量重置为剩余量
            ui->lineEditNumber->setText(QString::number(residualNumber));

            //更新出售量
            onSpinBoxSellNumberValueChanged();

            //更新对应的记录
            record.setValue("number", residualNumber);

            //重新设置对应model
            m_model->setRecord(i, record);

            break;
        }
    }

    //出售后将下单按钮激活
    ui->pushButtonOrder->setEnabled(true);
}


void KMainWindow::onPushButtonOrderClicked()
{
    ui->textEdit->append("**********************************************************************");

    QDateTime currentDateTime =QDateTime::currentDateTime();
    QString currentTime = currentDateTime.toString("yyyy.MM.dd hh:mm:ss ddd");

    ui->textEdit->append("日期：" + currentTime);
    ui->textEdit->append("订单号：" + QString::number(m_orderId));
    ui->textEdit->append("应付款总额：" + QString::number(m_orderTotalPrice) + "￥");
    ui->textEdit->append("下单成功！");

    //订单号加1
    m_orderId ++;
    //订单总价清空
    m_orderTotalPrice = 0;

    //提交修改 完成下单
    m_model->submitAll();

    //完成下单后将下单按钮关闭
    ui->pushButtonOrder->setEnabled(false);
}
