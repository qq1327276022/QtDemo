#ifndef UTILS_H
#define UTILS_H
#include <QString>
#include <QMetaType>
#include <QDebug>

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
    static bool getWeatherServiceKey(QString &private_key,QString &uid);
    static QString getWeatherServiceSig(QString &url,QString &private_key);
};

#endif // UTILS_H
