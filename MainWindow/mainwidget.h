#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QHBoxLayout>

#include "menulistview.h"


class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
private:
    void initUi();


signals:

private:
    MenuListview *m_leftMenu = nullptr;
    QStackedWidget *m_rightMainWidget = nullptr;
};

#endif // MAINWIDGET_H
