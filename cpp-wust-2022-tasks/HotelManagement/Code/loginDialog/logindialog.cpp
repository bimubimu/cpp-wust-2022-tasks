#include "logindialog.h"
#include "ui_logindialog.h"

#include <QMessageBox>
#include <QAction>

LoginDialog::LoginDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    m_pLoginService = new LoginService;

    //关闭时释放内存
    this->setAttribute(Qt::WA_DeleteOnClose);

    //正则表达式限制用户输入
    initInputLimit();

    //初始化登录界面
    initDialog();
}

LoginDialog::~LoginDialog()
{
    delete ui;
    delete m_pLoginService;
}

void LoginDialog::initInputLimit()
{
    //只能输入字母数字和下划线，最大长度为16
    QRegExp regx("^[0-9a-zA-Z_]{1,16}$");

    QValidator *validator = new QRegExpValidator(regx, this);

    ui->lineEditUsername->setValidator(validator);
    ui->lineEditPassword->setValidator(validator);
}

void LoginDialog::initDialog()
{
    QAction * pActUsername = new QAction(this);
    pActUsername->setIcon(QIcon(":/image/username.png"));
    ui->lineEditUsername->addAction(pActUsername,QLineEdit::LeadingPosition);
    QAction * pActPassword = new QAction(this);
    pActPassword->setIcon(QIcon(":/image/password.png"));
    ui->lineEditPassword->addAction(pActPassword, QLineEdit::LeadingPosition);
}

void LoginDialog::on_pushButtonLogin_clicked()
{
    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();

    //用户名密码为空
    if(username == "" || password == "")
    {
        QMessageBox::information(this, "提示", "用户名或密码不能为空");
        return;
    }

    //检查登录信息
    bool ok = m_pLoginService->checkUserInfo(username, password);

    if(ok)
    {
        KMainWindow * mainWindow = new KMainWindow(username);
        mainWindow->show();

        this->close();
    }
    else
    {
        QMessageBox::information(this, "提示", "用户名或密码有误!");
    }
}
