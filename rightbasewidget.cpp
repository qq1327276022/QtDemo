#include "rightbasewidget.h"
#include <QPainter>

RightBaseWidget::RightBaseWidget(QWidget *parent) : QWidget(parent)
{

}

void RightBaseWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QColor backgroundColor(Qt::black);
    backgroundColor.setAlphaF(0.1);
    painter.fillRect(rect(),backgroundColor);
    QWidget::paintEvent(event);
}
