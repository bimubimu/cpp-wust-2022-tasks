#include "kroominfowidget.h"
#include "ui_kroominfowidget.h"

KRoomInfoWidget::KRoomInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KRoomInfoWidget)
{
    ui->setupUi(this);
    m_roomInfoService = new KRoomInfo;

    initRoomInfo();
}

KRoomInfoWidget::~KRoomInfoWidget()
{
    delete ui;
    delete m_roomInfoService;
}

void KRoomInfoWidget::initRoomInfo()
{
    //更新所有房间状态
    for(int i = 0; i < 24; i ++)
    {
        QString id = "";
        QString roomType = "";
        QString roomStatus = "";

        m_roomInfoService->getRoomInfo(i, id, roomType, roomStatus);

        getRoomLabel(i)->setText(id + "\n" + roomType+ "\n" + roomStatus);
        getRoomLabel(i)->setFont(QFont("幼圆", 14));

        if(roomStatus == "空房")
            getRoomLabel(i)->setStyleSheet("background-color:rgb(14, 255, 14);");
        if(roomStatus == "入住")
            getRoomLabel(i)->setStyleSheet("background-color:rgb(255, 67, 30);");
    }
}

QLabel *KRoomInfoWidget::getRoomLabel(int index)
{
    switch(index)
    {
    case 0:return ui->label;
    case 1:return ui->label_2;
    case 2:return ui->label_3;
    case 3:return ui->label_4;
    case 4:return ui->label_5;
    case 5:return ui->label_6;
    case 6:return ui->label_7;
    case 7:return ui->label_8;
    case 8:return ui->label_9;
    case 9:return ui->label_10;
    case 10:return ui->label_11;
    case 11:return ui->label_12;
    case 12:return ui->label_13;
    case 13:return ui->label_14;
    case 14:return ui->label_15;
    case 15:return ui->label_16;
    case 16:return ui->label_17;
    case 17:return ui->label_18;
    case 18:return ui->label_19;
    case 19:return ui->label_20;
    case 20:return ui->label_21;
    case 21:return ui->label_22;
    case 22:return ui->label_23;
    case 23:return ui->label_24;
    default:return nullptr;
    };
}
