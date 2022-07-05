#ifndef KLOGINDIALOG_H
#define KLOGINDIALOG_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QMainWindow>
#include <QAction>
#include <QMessageBox>
#include "kloginservice.h"
#include "kmainwindow.h"

namespace Ui {
class KLoginDialog;
}

class KLoginDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit KLoginDialog(QWidget *parent = 0);
    ~KLoginDialog();

    void initLineEdit();
    //初始化输入限制
    void initLimit();

public slots:
    void onPushButtonLoginClicked();

private:
    Ui::KLoginDialog *ui;
    KLoginService* m_lgnService;
};

#endif // KLOGINDIALOG_H
