#include "menulistviewdelegate.h"

#include <QPainter>
#include <QDebug>
#include <QFontMetrics>

MenuListViewDelegate::MenuListViewDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{

}

MenuListViewDelegate::~MenuListViewDelegate()
{

}

void MenuListViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    painter->setRenderHints(QPainter::HighQualityAntialiasing | QPainter::SmoothPixmapTransform | QPainter::Antialiasing);

    MenuData data = index.data(Qt::UserRole +1).value<MenuData>();
    QRect rect = option.rect;

    paintBackground(painter,option,rect,QPalette::Active);
    paintExpendIcon(painter,option,data,rect);
    paintText(painter,option,data.m_title,rect);

    painter->restore();
}

QSize MenuListViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    return QSize(120,50);
}

void MenuListViewDelegate::paintBackground(QPainter *painter, const QStyleOptionViewItem &option, const QRect &backgroundRect, const QPalette::ColorGroup cg) const
{
    QPainterPath pathFirst;
    const int radius = 8;
    if(option.state & QStyle::State_Selected){
        getPaintPath(backgroundRect, pathFirst, 0, 0, radius);
        painter->fillPath(pathFirst,QBrush(option.palette.color(cg,QPalette::ColorRole::Highlight)));
    }
}

void MenuListViewDelegate::paintExpendIcon(QPainter *painter, const QStyleOptionViewItem &option, const MenuData &data, const QRect &Rect) const
{
    if(!data.m_isExpandable){
        return;
    }

    QPoint topleft = Rect.topLeft();
    QRect icRect  = QRect(topleft.x()+5 , topleft.y()+10,25,25);
    if(data.m_isExpanded){
        if(option.state & QStyle::State_Selected){
            painter->drawPixmap(icRect ,QPixmap(":/icon/dark_up.png"));
        } else {
            painter->drawPixmap(icRect ,QPixmap(":/icon/up.png"));
        }
    } else {
        if(option.state & QStyle::State_Selected){
            painter->drawPixmap(icRect ,QPixmap(":/icon/dark_down.png"));
        } else {
            painter->drawPixmap(icRect ,QPixmap(":/icon/down.png"));
        }
    }
}

void MenuListViewDelegate::paintText(QPainter *painter, const QStyleOptionViewItem &option, const QString &content, const QRect &Rect) const
{
    QPoint topleft = Rect.topLeft();
    int textRectWidth = Rect.width() - 40;
    QRect textRect  = QRect(topleft.x()+40 , topleft.y()+10,textRectWidth,Rect.height() - 10);

    QTextOption textOption;
    textOption.setAlignment(Qt::AlignLeft);

    QFont font = painter->font();
    QFontMetrics fontMetrics(font);
    QString str = fontMetrics.elidedText(content,Qt::TextElideMode::ElideRight,textRectWidth);

    if(option.state & QStyle::State_Selected){
        painter->setPen(Qt::white);
        painter->drawText(textRect,str,textOption);
    } else {
        painter->setPen(Qt::black);
        painter->drawText(textRect,str,textOption);
    }
}

void MenuListViewDelegate::getPaintPath(const QRect &bgRect, QPainterPath &path, const int xDifference, const int yDifference, const int radius) const
{
    QPoint path_bottomRight(bgRect.bottomRight().x() - xDifference, bgRect.bottomRight().y() - yDifference);
    QPoint path_topRight(bgRect.topRight().x() - xDifference, bgRect.topRight().y() + yDifference);
    QPoint path_topLeft(bgRect.topLeft().x() + xDifference, bgRect.topLeft().y() + yDifference);
    QPoint path_bottomLeft(bgRect.bottomLeft().x() + xDifference, bgRect.bottomLeft().y() - yDifference);
    path.moveTo(path_bottomRight - QPoint(0, 10));
    path.lineTo(path_topRight + QPoint(0, 10));
    path.arcTo(QRect(QPoint(path_topRight - QPoint(radius * 2, 0)), QSize(radius * 2, radius * 2)), 0, 90);
    path.lineTo(path_topLeft + QPoint(10, 0));
    path.arcTo(QRect(QPoint(path_topLeft), QSize(radius * 2, radius * 2)), 90, 90);
    path.lineTo(path_bottomLeft - QPoint(0, 10));
    path.arcTo(QRect(QPoint(path_bottomLeft - QPoint(0, radius * 2)), QSize(radius * 2, radius * 2)), 180, 90);
    path.lineTo(path_bottomRight - QPoint(10, 0));
    path.arcTo(QRect(QPoint(path_bottomRight - QPoint(radius * 2, radius * 2)), QSize(radius * 2, radius * 2)), 270, 90);
}
