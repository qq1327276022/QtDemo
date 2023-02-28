#ifndef WEATHERWIDGETSERVICE_H
#define WEATHERWIDGETSERVICE_H

#include <QObject>
#include <QThread>
#include <QUuid>

class WeatherWidgetService : public QObject
{
    Q_OBJECT
public:
    explicit WeatherWidgetService(QObject *parent = nullptr);
    void startThread();
    void quitThread();
    static WeatherWidgetService *getWeatherWidgetServiceInstence();
    void getCityWeatherInfo(const QUuid &id, const QString &city);

private:
    WeatherWidgetService(const WeatherWidgetService&);
    WeatherWidgetService& operator=(const WeatherWidgetService&);

signals:
    void getCityWeatherInfoFinished(QUuid id,const QByteArray &replyData);

private  slots:
    void onGetCityWeatherInfo(QUuid id,const QString &city);

private:
    QThread *m_thread = nullptr;
    static WeatherWidgetService *m_service;
    QString m_uid;
    QString m_privateKey;
    int m_requestCount = 0;
};

#endif // WEATHERWIDGETSERVICE_H
