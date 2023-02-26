#ifndef MENULISTVIEWDELEGATE_H
#define MENULISTVIEWDELEGATE_H
#include <QStyledItemDelegate>
#include "utils.h"

class MenuListViewDelegate : public QStyledItemDelegate
{
public:
    MenuListViewDelegate(QObject *parent = nullptr);
    ~MenuListViewDelegate();

    // QAbstractItemDelegate interface
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paintBackground(QPainter *painter, const QStyleOptionViewItem &option, const QRect &backgroundRect, const QPalette::ColorGroup cg) const;
    void paintExpendIcon(QPainter *painter, const QStyleOptionViewItem &option, const MenuData &data,const QRect &Rect)const;
    void paintText(QPainter *painter, const QStyleOptionViewItem &option,const QString &content,const QRect &Rect)const;
    void getPaintPath(const QRect &bgRect, QPainterPath &path, const int xDifference, const int yDifference, const int radius) const;

};

#endif // MENULISTVIEWDELEGATE_H
