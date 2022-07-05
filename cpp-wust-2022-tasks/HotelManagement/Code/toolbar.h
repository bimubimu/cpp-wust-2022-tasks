#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QObject>
#include <QToolBar>
#include <QLabel>
#include "database/kdatabase.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif


class ToolBar : public QWidget
{
    Q_OBJECT
public:
    explicit ToolBar(const QString& username, QWidget *parent = nullptr);
    ~ToolBar();

    void initToolBar(const QString& username, QWidget *parent);
    QLabel* addUserAvatarInfo(const QString& username);
    QLabel* addUserNameInfo(const QString& username);
    QToolBar* getToolBar();

signals:
    void priceClicked();
    void roomClicked();
    void registClicked();
    void employeeClicked();

private:
    QToolBar* m_pToolBar;
    KDataBase * m_pDatabase;
};

#endif // TOOLBAR_H
