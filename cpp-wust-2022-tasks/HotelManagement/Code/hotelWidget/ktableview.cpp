#include "ktableview.h"

KTableView::KTableView(QWidget *parent)
{

}

void KTableView::mousePressEvent(QMouseEvent* ev)
{
    QModelIndex idx = indexAt(ev->pos());
    if (!idx.isValid())
        this->setCurrentIndex(QModelIndex(idx));
    QTableView::mousePressEvent(ev);
}
