#ifndef KTABLEVIEW_H
#define KTABLEVIEW_H

#include <QObject>
#include <QMouseEvent>
#include <QTableView>

class KTableView : public QTableView
{
public:
    KTableView(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent* ev);
};

#endif // KTABLEVIEW_H
