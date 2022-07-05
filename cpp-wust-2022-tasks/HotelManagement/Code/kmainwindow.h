#ifndef KMAINWINDOW_H
#define KMAINWINDOW_H

#include <QMainWindow>
#include "toolbar.h"
#include "hotelWidget/kpriceinfowidget.h"
#include "hotelWidget/kroominfowidget.h"
#include "hotelWidget/kregisterwidget.h"
#include "hotelWidget/kemployeewidget.h"

namespace Ui {
class KMainWindow;
}

class KMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit KMainWindow(const QString& username, QWidget *parent = 0);
    ~KMainWindow();

    void initStackWidget();
    void initToolBar();
    void showTime();

private:
    Ui::KMainWindow *ui;
    ToolBar * m_ptoolBar;

    KPriceInfoWidget * m_priceInfoWidget;
    KRoomInfoWidget * m_roomInfoWidget;
    KRegisterWidget * m_registerWidget;
    KEmployeeWidget * m_employeeWidget;

    QString m_username;
};

#endif // KMAINWINDOW_H
