#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QMainWindow>
#include "loginService/loginservice.h"
#include "kmainwindow.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

    void initInputLimit();
    void initDialog();

public slots:
    void on_pushButtonLogin_clicked();

private:
    Ui::LoginDialog *ui;

    LoginService * m_pLoginService;
};

#endif // LOGINDIALOG_H
