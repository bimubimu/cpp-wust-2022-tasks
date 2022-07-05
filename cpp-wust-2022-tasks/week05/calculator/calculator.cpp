#include "calculator.h"

int Calculator::getPriority(QChar ch)
{
    if(ch == '+' || ch == '-')
        return 1;
    if(ch == '*' || ch == '/')
        return 2;
    return -1;
}

bool Calculator::checkNumber(QString number)
{
    int i = 0;
    if(number[i] == '-')    i ++;

    if(number[i] == '0')    i ++;
    else
    {
        if(number[i] < '0' || number[i] > '9')  return false;
        for(; number[i] >= '0' && number[i] <= '9'; i ++);
    }

    if(number[i] == '.')
    {
        i ++;
        if(number[i] < '0' || number[i] > '9')  return false;
        for(; number[i] >= '0' && number[i] <= '9'; i ++);
    }

    if(number[i] != ' ')
        return false;

    return true;
}

void Calculator::parseSuffixExpression(QString &text, QString &suffixExpression)
{
    QStack<QChar> operStack;
    operStack.push_back('#');
    suffixExpression.push_back('#');
    int preSign = 1;    //1.运算符 2.数字 3.(  4.)

    for(int i = 0; i < text.size(); i ++)
    {
        //第一位只能为数字(包含负数)或左括号
        if(i == 0)
            if(text[0] == ')' || text[0] == '+' || text[0] == '*' || text[0] == '/')
            {
                suffixExpression.clear();
                return;
            }


        if(text[i] == '(')
        {
            //左括号前不能为数字或右括号
            if(preSign == 2 || preSign == 4)
            {
                suffixExpression.clear();
                return;
            }
            operStack.push_back('(');
            preSign = 3;
        }

        else if(text[i] == ')')
        {
            //右括号前不能为运算符或左括号
            if(preSign == 1 || preSign == 3)
            {
                suffixExpression.clear();
                return;
            }

            while(operStack.top() != '(')
            {
                //没有匹配的括号
                if(operStack.top() == '#')
                {
                    suffixExpression.clear();
                    return;
                }

                suffixExpression.push_back(operStack.top());
                suffixExpression.push_back(' ');
                operStack.pop();
            }
            operStack.pop();
            preSign = 4;
        }

        //  '('和' '后的'-'看做数字的一部分
        else if((text[i] >= '0' && text[i] <= '9' )|| text[i] == '.'
                || (text[i] == '-' && i != 0 && text[i - 1] == '(')
                || (text[i] == '-' && i == 0))
        {

            QString number;
            number.push_back(text[i]);
            suffixExpression.push_back(text[i]);
            i++;

            //数字前不能为右括号
            if(preSign == 4)
            {
                suffixExpression.clear();
                return;
            }

            while(i < text.size() && ((text[i] >= '0' && text[i] <= '9') || text[i] == '.'))
            {
                number.push_back(text[i]);
                suffixExpression.push_back(text[i]);
                i ++;

            }
            i --;
            suffixExpression.push_back(' ');
            number.push_back(' ');

            //检查数字是否合法
            if(!checkNumber(number))
            {
                suffixExpression.clear();
                return;
            }

            preSign = 2;
        }


        else if(text[i] == '+' || text[i] == '-' || text[i] == '*' || text[i] == '/')
        {
            //运算符前不能为运算符或左括号
            if(preSign == 1 || preSign == 3)
            {
                suffixExpression.clear();
                return;
            }
            while(Calculator::getPriority(operStack.top()) >= Calculator::getPriority(text[i]))
            {
                suffixExpression.push_back(operStack.top());
                suffixExpression.push_back(' ');
                operStack.pop();
            }
            operStack.push_back(text[i]);
            preSign = 1;
        }


    }

    //不能以（或运算符结尾
    if(preSign == 3 || preSign == 1)
    {
        suffixExpression.clear();
        return;
    }

    while(operStack.top() != '#')
    {
        //运算符不匹配
        if(operStack.top() == '(')
        {
            suffixExpression.clear();
            return;
        }
        suffixExpression.push_back(operStack.top());
        suffixExpression.push_back(' ');
        operStack.pop();
    }

    qDebug()<<suffixExpression;
}

double Calculator::countSuffix(QString &suffixExpression, int& flag)
{

    double newElem;  //新入栈元素
    QStack<double> elemStack;

    for(int i = 1; i < suffixExpression.size(); i ++)
    {
        if(suffixExpression[i] == ' ')
            continue;

        else if(suffixExpression[i] == '+')
        {
            newElem = elemStack.top();
            elemStack.pop();
            newElem = elemStack.top() + newElem;
            elemStack.pop();
        }

        else if(suffixExpression[i] == '-' && suffixExpression[i + 1] == ' ')
        {
            newElem = elemStack.top();
            elemStack.pop();
            newElem = elemStack.top() - newElem;
            elemStack.pop();
        }

        else if(suffixExpression[i] == '*')
        {
            newElem = elemStack.top();
            elemStack.pop();
            newElem = elemStack.top() * newElem;
            elemStack.pop();
        }

        else if(suffixExpression[i] == '/')
        {
            newElem = elemStack.top();
            //除数为0
            if(newElem == 0)
            {
                flag = 1;
                return 0;
            }
            elemStack.pop();
            newElem = elemStack.top() / newElem;
            elemStack.pop();
        }

        else
        {
            QString number;
            while(suffixExpression[i] != ' ')
            {
                number.push_back(suffixExpression[i]);
                i++;
            }

            newElem = number.toDouble();

        }

        elemStack.push_back(newElem);
    }
    return elemStack.top();
}


double Calculator::calculate(QString &text, int& ansInfo)
{
    QString suffixExpression;
    int flag = 0;   //记录后缀表达式运算过程中的信息  0正常  1除数为0

    //中缀表达式转后缀表达式
    parseSuffixExpression(text, suffixExpression);

    if(suffixExpression.isEmpty())
    {
        ansInfo = 1;
        return 0;
    }

    double ans = countSuffix(suffixExpression, flag);
    if(flag == 1)
    {
        ansInfo = 2;
        return 0;
    }

    return ans;

}
