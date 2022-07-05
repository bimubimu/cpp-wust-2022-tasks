#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QString>
#include <QStack>
#include <QDebug>

class Calculator
{
public:
    Calculator() {}

    //获取运算符优先级
    static int getPriority(QChar ch);
    //检查数字的合法性
    bool checkNumber(QString number);
    //中缀表达式转后缀表达式
    void parseSuffixExpression(QString& text, QString& suffixExpression);
    //计算后缀表达式
    double countSuffix(QString& suffixExpression, int& flag);
    //计算字符串表达式
    double calculate(QString& text, int& usefulAns);

};
#endif // CALCULATOR_H

