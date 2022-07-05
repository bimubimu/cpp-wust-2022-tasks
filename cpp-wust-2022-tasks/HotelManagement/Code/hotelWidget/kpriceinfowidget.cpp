#include "kpriceinfowidget.h"
#include "ui_kpriceinfowidget.h"

KPriceInfoWidget::KPriceInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KPriceInfoWidget)
{
    ui->setupUi(this);
    m_priceInfoService = new KPriceInfo;

    //选择显示图片，默认为第5张
    ui->labelPicture->setPixmap(m_priceInfoService->getRoomPicture(5));
    ui->labelPicture->setScaledContents(true);

    //切换图片
    connect(ui->pushButtonOne, &QPushButton::clicked, [=](){ui->labelPicture->setPixmap(m_priceInfoService->getRoomPicture(1));});
    connect(ui->pushButtonTwo, &QPushButton::clicked, [=](){ui->labelPicture->setPixmap(m_priceInfoService->getRoomPicture(2));});
    connect(ui->pushButtonThree, &QPushButton::clicked, [=](){ui->labelPicture->setPixmap(m_priceInfoService->getRoomPicture(3));});
    connect(ui->pushButtonFour, &QPushButton::clicked, [=](){ui->labelPicture->setPixmap(m_priceInfoService->getRoomPicture(4));});
    connect(ui->pushButtonFive, &QPushButton::clicked, [=](){ui->labelPicture->setPixmap(m_priceInfoService->getRoomPicture(5));});

    initPriceInfoTableView();
}

KPriceInfoWidget::~KPriceInfoWidget()
{
    delete ui;
    delete m_priceInfoService;
}

void KPriceInfoWidget::initPriceInfoTableView()
{
    //设置对应的model
    ui->tableViewPriceInfo->setModel(m_priceInfoService->getTableModel());

    ui->tableViewPriceInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewPriceInfo->setAlternatingRowColors(true);
    ui->tableViewPriceInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableViewPriceInfo->horizontalHeader()->setMinimumHeight(40);
    ui->tableViewPriceInfo->horizontalHeader()->setFont(QFont("微软雅黑", 10));
    ui->tableViewPriceInfo->setFont(QFont("微软雅黑", 13));
    ui->tableViewPriceInfo->verticalHeader()->hide();
    ui->tableViewPriceInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewPriceInfo->setFocusPolicy(Qt::NoFocus);
}
