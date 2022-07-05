#ifndef KROOMINFOWIDGET_H
#define KROOMINFOWIDGET_H

#include <QWidget>
#include <QLabel>
#include "hotelService/kroominfo.h"

namespace Ui {
class KRoomInfoWidget;
}

class KRoomInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit KRoomInfoWidget(QWidget *parent = 0);
    ~KRoomInfoWidget();

    void initRoomInfo();
    QLabel *getRoomLabel(int index);

private:
    Ui::KRoomInfoWidget *ui;
    KRoomInfo * m_roomInfoService;
};

#endif // KROOMINFOWIDGET_H
