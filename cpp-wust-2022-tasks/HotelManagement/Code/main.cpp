#include "kmainwindow.h"
#include <QApplication>
#include "loginDialog/logindialog.h"

#if 0

//内存泄漏检测
#include <vld.h>

#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog * lgn = new LoginDialog;
    lgn->show();

    return a.exec();
}
