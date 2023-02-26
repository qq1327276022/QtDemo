#include "menulistviewproxymodel.h"
#include "utils.h"

MenuListviewProxymodel::MenuListviewProxymodel(QObject *parent)
    :QSortFilterProxyModel(parent)
{

}

MenuListviewProxymodel::~MenuListviewProxymodel()
{

}

bool MenuListviewProxymodel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    MenuData indexData  =  sourceModel()->index(source_row,0,source_parent).data(Qt::UserRole + 1).value<MenuData>();

    //若为一级标题固定显示，二级标题根据具体状态而定。
    if(indexData.m_isExpandable){
        return true;
    } else {
        return !indexData.m_isExpanded;
    }
}
