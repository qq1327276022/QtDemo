#include "menulistview.h"
#include <QDebug>
#include <QPalette>

MenuListview::MenuListview(QWidget *parent)
    :QListView(parent)
{
    qRegisterMetaType<MenuData>("MenuData");
    initListView();
}

MenuListview::~MenuListview()
{

}


/*************************************************************************
 <Function>      MenuListview::insertData
 <Description>   插入菜单项数据
 <Author>        鶸 1327276022@qq.com
 <Input>
    <param1>     const QMap<QString, QStringList> &dataMap
                 Description: key   一级菜单标题
                              value 该一级菜单对应的二级菜单标题
 <Return>        bool            Description:是否插入成功
 <Note>          目前只支持两层菜单
*************************************************************************/
bool MenuListview::insertData(const QMap<QString, QStringList> &dataMap)
{
    QMap<QString, QStringList>::const_iterator iterator = dataMap.begin();

    while (iterator != dataMap.end()) {
        QString firstTitle = iterator.key();
        QStringList secondTitlelist = iterator.value();

        int rows = m_standardItemModel->rowCount();

        if(!m_standardItemModel->insertRows(rows,secondTitlelist.count() +1 )){
            qDebug() << "insertRows error !" << endl;
            return false;
        }

        setModelIndexData(rows++,MenuData(firstTitle,true,true));

        foreach(QString secondTitle, secondTitlelist){
            setModelIndexData(rows++,MenuData(secondTitle,false,true));
        }

        m_firstTitleInMenuCountMap.insert(firstTitle,secondTitlelist.count());
        iterator++;
    }

    return true;
}

void MenuListview::initListView()
{
    QPalette basePal =  this->palette();
    basePal.setColor (QPalette::Base, Qt::transparent);
    this->setPalette(basePal);
    this->setFrameShape(QFrame::NoFrame);

    m_listviewDelegate = new MenuListViewDelegate;
    setItemDelegate(m_listviewDelegate);

    m_standardItemModel = new QStandardItemModel;
    m_standardItemModel->setColumnCount(1);

    m_listviewProxyModel = new MenuListviewProxymodel;
    m_listviewProxyModel->setSourceModel(m_standardItemModel);

    setModel(m_listviewProxyModel);
    setEditTriggers(EditTrigger::NoEditTriggers);
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setAutoScroll(false);
}

bool MenuListview::changeSecondLevelMenuExpandStatus(int firstMenuDataIndex, int secondLevelMenuCount)
{
    MenuData indexData;
    for(int index = firstMenuDataIndex;index <= firstMenuDataIndex + secondLevelMenuCount;index++){
        if(!getModelIndexData(index,indexData)){
            return false;
        }

        indexData.m_isExpanded = !indexData.m_isExpanded;

        if(!setModelIndexData(index,indexData)){
            return false;
        };
    }

    return true;
}

bool MenuListview::getModelIndexData(int index, MenuData &data)
{
    if(index < 0 || index >= m_standardItemModel->rowCount()){
        return false;
    }

    QModelIndex modelIndex = m_standardItemModel->index(index,0);
    data = modelIndex.data(Qt::UserRole + 1).value<MenuData>();
    return true;
}

bool MenuListview::getModelIndexData(const QModelIndex &index, MenuData &data)
{
    data = index.data(Qt::UserRole + 1).value<MenuData>();
    return true;
}

bool MenuListview::setModelIndexData(int index, const MenuData &data)
{
    QModelIndex modelIndex = m_standardItemModel->index(index,0);
    return  m_standardItemModel->setData(modelIndex,QVariant::fromValue(data),Qt::UserRole + 1);
}

bool MenuListview::setModelIndexData(const QModelIndex &index, const MenuData &data)
{
    return  m_standardItemModel->setData(index,QVariant::fromValue(data),Qt::UserRole + 1);
}



void MenuListview::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint releasePoint = event->pos();
    QModelIndex releaseIndex = this->indexAt(releasePoint);
    int row = releaseIndex.row();
    qDebug() << m_standardItemModel->rowCount() << "====" << row <<endl;
    if(row != -1){
        MenuData releaseIndexData = releaseIndex.data(Qt::UserRole + 1).value<MenuData>();

        //判断鼠标松开前所在行 若为一级标题则将其对应的所有二级标题状态取反 ，若为二级标题则无操作
        //判断是否为一级标题
        if(releaseIndexData.m_isExpandable){
            int secondMenuCount = m_firstTitleInMenuCountMap.value(releaseIndexData.m_title);
            for(int i = 0 ; i < m_standardItemModel->rowCount() ; i++){
//                 modelIndex = m_standardItemModel->index(i,0);
                 MenuData indexData;
                 if(!getModelIndexData(i,indexData)){
                     break;
                 }

                 if(!indexData.m_isExpandable){
                     continue;
                 }

                 if(indexData.m_title == releaseIndexData.m_title){
                    changeSecondLevelMenuExpandStatus(i,secondMenuCount);
                    break;
                 }
            }
        }
    }

    QListView::mouseReleaseEvent(event);
}

void MenuListview::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous)

    MenuData data;
    getModelIndexData(current,data);
//    emit currentPageChanged(data.m_title);

    QListView::currentChanged(current,previous);
}
