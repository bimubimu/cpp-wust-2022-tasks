
#include "klogindialog.h"
#include "ui_klogindialog.h"

KLoginDialog::KLoginDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KLoginDialog)
{
    ui->setupUi(this);
    initLineEdit();
    initLimit();

    this->setAttribute(Qt::WA_DeleteOnClose);
    m_lgnService = new KLoginService;

    connect(ui->pushButtonLogin, &QPushButton::clicked, this, &KLoginDialog::onPushButtonLoginClicked);
    connect(ui->pushButtonExit, &QPushButton::clicked, this, &KLoginDialog::close);
}

KLoginDialog::~KLoginDialog()
{
    delete m_lgnService;
    delete ui;
}

void KLoginDialog::initLineEdit()
{
    QAction* userAction = new QAction(this);
    userAction->setIcon(QIcon(":/image/username.png"));
    ui->lineEditUserId->addAction(userAction, QLineEdit::LeadingPosition);

    QAction* passwdAction = new QAction(this);
    passwdAction->setIcon(QIcon(":/image/password.png"));
    ui->lineEditPassword->addAction(passwdAction, QLineEdit::LeadingPosition);
}

void KLoginDialog::initLimit()
{
    //显示输入长度12
    ui->lineEditUserId->setMaxLength(12);
    ui->lineEditPassword->setMaxLength(12);

    //限制用户名只能为数字 密码为数字或字母
    QRegExp regxId("[0-9]+$");
    QRegExp regxPwd("[A-Za-z0-9]+$");

    QValidator *validatorId = new QRegExpValidator(regxId, this);
    QValidator *validatorPwd = new QRegExpValidator(regxPwd, this);

    ui->lineEditUserId->setValidator(validatorId);
    ui->lineEditPassword->setValidator(validatorPwd);

}

void KLoginDialog::onPushButtonLoginClicked()
{
    QString userId = ui->lineEditUserId->text();
    QString password = ui->lineEditPassword->text();

    if(userId.isEmpty() || password.isEmpty())
    {
        QMessageBox::information(this, "提示", "用户名或密码不能为空");
        return;
    }

    if(m_lgnService->checkUserInfo(userId, password))
    {
       KMainWindow* pwin = new KMainWindow(userId);
       pwin->show();
       this->close();
    }
    else
        QMessageBox::information(this, "提示", "用户名或密码有误");
}
