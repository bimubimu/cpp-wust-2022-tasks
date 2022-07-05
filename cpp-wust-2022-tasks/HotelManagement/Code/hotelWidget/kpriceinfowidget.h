#ifndef KPRICEINFOWIDGET_H
#define KPRICEINFOWIDGET_H

#include <QWidget>
#include "hotelService/kpriceinfo.h"

namespace Ui {
class KPriceInfoWidget;
}

class KPriceInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit KPriceInfoWidget(QWidget *parent = 0);
    ~KPriceInfoWidget();

    void initPriceInfoTableView();

private:
    Ui::KPriceInfoWidget *ui;
    KPriceInfo * m_priceInfoService;
};

#endif // KPRICEINFOWIDGET_H
