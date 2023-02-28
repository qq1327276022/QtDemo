#include "utils.h"

#include <QSettings>
#include <QFile>
#include <QTextCodec>
#include <QCryptographicHash>
#include <QDateTime>
#include <QMessageAuthenticationCode>
#include <QUrl>

Utils::Utils()
{

}

bool Utils::getWeatherServiceKey(QString &private_key, QString &uid)
{
    QFile file(":/Settings/networkSettings.ini");
    if (!file.exists()) {
        qWarning() << " get weather service info error!" << endl;
        return false;
    }

    QSettings *setting = new QSettings(":/Settings/networkSettings.ini", QSettings::IniFormat);
    setting->beginGroup("Weather Service");
    //将Qsetting的编码格式改为utf8格式，否则会出现乱码
    setting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    QStringList allKeys = setting->allKeys();
    if(!allKeys.contains("key") || !allKeys.contains("uid")){
        return false;
    }

    private_key = setting->value("key").toString();
    uid = setting->value("uid").toString();
    return true;
}

QString Utils::getWeatherServiceSig(QString &url, QString &private_key)
{
   QString str = QMessageAuthenticationCode::hash(url.toLatin1(),private_key.toLatin1(),QCryptographicHash::Sha1).toBase64();
   return  QUrl::toPercentEncoding(str);
}
