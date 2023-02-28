#ifndef RIGHTBASEWIDGET_H
#define RIGHTBASEWIDGET_H

#include <QWidget>

class RightBaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RightBaseWidget(QWidget *parent = nullptr);

signals:


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // RIGHTBASEWIDGET_H
