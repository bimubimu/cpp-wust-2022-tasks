#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //设置窗口名称
    this->setWindowTitle("计算器");

    //固定窗口大小
    this->setFixedSize( this->width (),this->height ());

    //限制输入长度
    ui-> lineEdit ->setMaxLength (15);

    //限制输入符号
    ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9.()+*/e-]+$")));

    //通过button输入
    connect(ui->m_button_1, SIGNAL(clicked()), this, SLOT(sendNumAndOper()));
    connect(ui->m_button_2, SIGNAL(clicked()), this, SLOT(sendNumAndOper()));
    connect(ui->m_button_3, SIGNAL(clicked()), this, SLOT(sendNumAndOper()));
    connect(ui->m_button_4, SIGNAL(clicked()), this, SLOT(sendNumAndOper()));
    connect(ui->m_button_5, SIGNAL(clicked()), this, SLOT(sendNumAndOper()));
    connect(ui->m_button_6, SIGNAL(clicked()), this, SLOT(sendNumAndOper()));
    connect(ui->m_button_7, SIGNAL(clicked()), this, SLOT(sendNumAndOper()));
    connect(ui->m_button_8, SIGNAL(clicked()), this, SLOT(sendNumAndOper()));
    connect(ui->m_button_9, SIGNAL(clicked()), this, SLOT(sendNumAndOper()));
    connect(ui->m_button_0, SIGNAL(clicked()), this, SLOT(sendNumAndOper()));
    connect(ui->m_button_dot, SIGNAL(clicked()), this, SLOT(sendNumAndOper()));
    connect(ui->m_button_add, SIGNAL(clicked()), this, SLOT(sendNumAndOper()));
    connect(ui->m_button_sub, SIGNAL(clicked()), this, SLOT(sendNumAndOper()));
    connect(ui->m_button_mul, SIGNAL(clicked()), this, SLOT(sendNumAndOper()));
    connect(ui->m_button_dev, SIGNAL(clicked()), this, SLOT(sendNumAndOper()));
    connect(ui->m_button_left_parenthes, SIGNAL(clicked()), this, SLOT(sendNumAndOper()));
    connect(ui->m_button_right_parenthes, SIGNAL(clicked()), this, SLOT(sendNumAndOper()));

    //运算
    connect(ui->m_button_calculate, SIGNAL(clicked()), this, SLOT(calculate()));
    //输入栏退格
    connect(ui->m_button_del, SIGNAL(clicked()), this, SLOT(textDelete()));
    //清空输入栏
    connect(ui->m_button_clear, SIGNAL(clicked()), ui->lineEdit, SLOT(clear()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::sendLineEdit(QString str)
{
    ui->lineEdit->insert(str);
}

void Dialog::throwErrorNeedExpression()
{
    QMessageBox::information(this,"提示","请输入表达式");
}

void Dialog::throwErrorExpressionWrong()
{
    QMessageBox::information(this,"提示","不合理的表达式");
}

void Dialog::throwErrorDivisorIsZero()
{
    QMessageBox::information(this,"提示","除数不能为0");
}

void Dialog::sendNumAndOper()
{
    //获取button文本信息
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString text = button->text();

    if(text == "0")
        sendLineEdit("0");
    if(text == "1")
        sendLineEdit("1");
    if(text == "2")
        sendLineEdit("2");
    if(text == "3")
        sendLineEdit("3");
    if(text == "4")
        sendLineEdit("4");
    if(text == "5")
        sendLineEdit("5");
    if(text == "6")
        sendLineEdit("6");
    if(text == "7")
        sendLineEdit("7");
    if(text == "8")
        sendLineEdit("8");
    if(text == "9")
        sendLineEdit("9");
    if(text == "+")
        sendLineEdit("+");
    if(text == "-")
        sendLineEdit("-");
    if(text == "*")
        sendLineEdit("*");
    if(text == "/")
        sendLineEdit("/");
    if(text == "(")
        sendLineEdit("(");
    if(text == ")")
        sendLineEdit(")");
    if(text == ".")
        sendLineEdit(".");

}

void Dialog::textDelete()
{
    ui->lineEdit->backspace();
}

void Dialog::calculate()
{
    //获取表达式字符串
    QString text = ui->lineEdit->text();
    if(text.isEmpty())
    {
        throwErrorNeedExpression();
        return;
    }

    Calculator calc;
    int ansInfo  = 0;   //0有结果  1表达式错误  2除数为0

    double ans = 0;
    ans = calc.calculate(text, ansInfo);

    //表达式不能计算，提示错误
    if(ansInfo == 1)
    {
        throwErrorExpressionWrong();
        return;
    }

    if(ansInfo == 2)
    {
        throwErrorDivisorIsZero();
        return;
    }

    ui->lineEdit->clear();
    ui->lineEdit->insert(QString::number(ans, 10, 6));
}




