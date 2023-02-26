#include "mainwindow.h"
#include "menulistview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    MenuListview m_listview;

    QMap<QString ,QStringList> list;
    list.insert("1",QStringList() <<"2" << "3");
    list.insert("6",QStringList() <<"0" << "3");
    list.insert("7",QStringList() <<"00000000000000000000000000000000000" << "5");
    m_listview.insertData(list);
    m_listview.show();
    return a.exec();
}
