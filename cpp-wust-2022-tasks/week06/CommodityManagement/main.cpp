#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "kmainwindow.h"
#include "klogindialog.h"
#include <QApplication>
#include <QDebug>
#include <QSqlDatabase>

//内存泄漏检测
//#include <vld.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    KLoginDialog* lgn = new KLoginDialog;
    lgn->show();


    return a.exec();
}
