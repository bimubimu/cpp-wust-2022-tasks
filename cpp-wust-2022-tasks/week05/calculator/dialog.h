#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include <QStack>
#include <QDebug>
#include <QMessageBox>
#include "calculator.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void sendLineEdit(QString);
    void throwErrorNeedExpression();
    void throwErrorExpressionWrong();
    void throwErrorDivisorIsZero();

public slots:
    void sendNumAndOper();
    void textDelete();
    void calculate();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
