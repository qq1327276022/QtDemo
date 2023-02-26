#include "mainwidget.h"
#include <QPalette>
#include <QPushButton>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    initUi();
}

MainWidget::~MainWidget()
{

}

void MainWidget::initUi()
{
    m_leftMenu = new MenuListview(this);
    m_leftMenu->setMaximumWidth(150);
    m_rightMainWidget = new QStackedWidget;

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setContentsMargins(5,5,5,5);
    mainLayout->addWidget(m_leftMenu);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(m_rightMainWidget);

    this->setLayout(mainLayout);

    QMap<QString ,QStringList> list;
    list.insert("1",QStringList() <<"2" << "3");
    list.insert("6",QStringList() <<"0" << "3");
    list.insert("7",QStringList() <<"00000000000000000000000000000000000" << "5");
    m_leftMenu->insertData(list);
}

