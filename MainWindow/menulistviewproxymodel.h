#ifndef MENULISTVIEWPROXYMODEL_H
#define MENULISTVIEWPROXYMODEL_H

#include <QSortFilterProxyModel>

class MenuListviewProxymodel :public QSortFilterProxyModel
{
public:
    MenuListviewProxymodel(QObject *parent = nullptr);
    ~MenuListviewProxymodel();

    // QSortFilterProxyModel interface
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
};

#endif // MENULISTVIEWPROXYMODEL_H
