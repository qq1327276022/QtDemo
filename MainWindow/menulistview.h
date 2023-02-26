#ifndef MENULISTVIEW_H
#define MENULISTVIEW_H
#include <QListView>
#include <QStandardItemModel>
#include <QMouseEvent>

#include "menulistviewdelegate.h"
#include "menulistviewproxymodel.h"
#include "utils.h"

class MenuListview : public QListView
{
public:
    MenuListview(QWidget *parent = nullptr);
    ~MenuListview();
    bool insertData(const QMap<QString,QStringList> &dataMap);


private:
    void initListView();
    bool changeSecondLevelMenuExpandStatus(int firstMenuDataIndex,int secondLevelMenuCount);

private:
    MenuListViewDelegate *m_listviewDelegate = nullptr;
    MenuListviewProxymodel *m_listviewProxyModel = nullptr;
    QStandardItemModel *m_standardItemModel = nullptr;


    //记录一级菜单标题 以及该一级菜单对应二级菜单数目
    QMap<QString ,int> m_firstTitleInMenuCountMap;

    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // MENULISTVIEW_H
