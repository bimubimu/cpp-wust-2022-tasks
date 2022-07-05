#ifndef KREGISTERWIDGET_H
#define KREGISTERWIDGET_H

#include <QWidget>
#include "hotelService/kregister.h"

namespace Ui {
class KRegisterWidget;
}

class KRegisterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit KRegisterWidget(QWidget *parent = 0);
    ~KRegisterWidget();

    void initTime();
    void initCalendar();
    void initInputLimitCheckOut();
    void initInputLimitQuery();
    void initTableView();

private slots:
    void on_pushButtonRegister_clicked();
    void on_pushButtonClean_clicked();
    void on_pushButtonCheckOut_clicked();
    void on_pushButtonRoomNumber_clicked();
    void on_pushButtonName_clicked();
    void on_pushButtonIdCard_clicked();
    void on_tabWidget_currentChanged(int index);

private:
    Ui::KRegisterWidget *ui;

    KRegister * m_pRegisterService;
};

#endif // KREGISTERWIDGET_H
