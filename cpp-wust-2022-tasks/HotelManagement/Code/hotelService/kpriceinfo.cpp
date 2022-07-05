#include "kpriceinfo.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

KPriceInfo::KPriceInfo(QObject *parent) : QObject(parent)
{
    QString connectionName = "priceInfoConn";
    m_pDatabase = new KDataBase(connectionName);

    initSqlModel();
}

KPriceInfo::~KPriceInfo()
{
    delete m_model;
    delete m_pDatabase;
}

void KPriceInfo::initSqlModel()
{
    m_model = new QSqlTableModel(this, m_pDatabase->getDatabase());

    m_model->setTable("roomPrice");

    //设置手动提交
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //查询数据库
    m_model->select();

    m_model->removeColumn(5);
    m_model->setHeaderData(0, Qt::Horizontal, "id");
    m_model->setHeaderData(1, Qt::Horizontal, "房型");
    m_model->setHeaderData(2, Qt::Horizontal, "今日价");
    m_model->setHeaderData(3, Qt::Horizontal, "门市价");
    m_model->setHeaderData(4, Qt::Horizontal, "会员价");
}

QSqlTableModel *KPriceInfo::getTableModel()
{
    return m_model;
}

QPixmap KPriceInfo::getRoomPicture(int id)
{
    QSqlQuery query(m_pDatabase->getDatabase());

    QString sql = "select roomPixmap from roomPrice where id = ?";
    query.prepare(sql);
    query.bindValue(0, id);

    bool ok = query.exec();

    if(!ok)
    {
        qDebug()<<"[KPriceInfo::getRoomPicture]: "<<query.lastError().text();
    }

    query.first();
    QByteArray outByteArray = query.value(0).toByteArray();
    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData(outByteArray);

    return outPixmap;
}
