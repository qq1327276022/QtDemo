#ifndef WEATHERWIDGETSERVICE_H
#define WEATHERWIDGETSERVICE_H

#include <QObject>
#include <QThread>


class WeatherWidgetService : public QObject
{
    Q_OBJECT
public:
    explicit WeatherWidgetService(QObject *parent = nullptr);
    void startThread();
    void quitThread();
    static WeatherWidgetService *getWeatherWidgetServiceInstence();
    int getCityWeatherInfo(const QString &city);

private:
    WeatherWidgetService(const WeatherWidgetService&);
    WeatherWidgetService& operator=(const WeatherWidgetService&);

signals:

private  slots:
    void getCityWeatherInfo(int requestCount,const QString &city);

private:
    QThread *m_thread = nullptr;
    static WeatherWidgetService *m_service;
    QString m_uid;
    QString m_privateKey;
    int m_requestCount = 0;
};

#endif // WEATHERWIDGETSERVICE_H
