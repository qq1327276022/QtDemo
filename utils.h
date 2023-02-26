#ifndef UTILS_H
#define UTILS_H
#include <QString>
#include <QMetaType>

struct MenuData{
    QString m_title;
    bool m_isExpandable;
    bool m_isExpanded;

    MenuData(){
        m_title = QString();
        m_isExpandable = false;
        m_isExpanded = false;
    }
    MenuData(const QString &title,bool isExpandable,bool isExpanded){
        m_title = title;
        m_isExpandable = isExpandable;
        m_isExpanded = isExpanded;
    }
};

Q_DECLARE_METATYPE(MenuData);

class Utils
{
public:
    Utils();
};

#endif // UTILS_H
