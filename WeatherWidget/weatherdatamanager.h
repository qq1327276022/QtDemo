#ifndef WEATHERDATAMANAGER_H
#define WEATHERDATAMANAGER_H
#include "weatherDataType.h"
#include "weatherwidgetservice.h"
#include <QObject>


class WeatherDataManager : public QObject
{
    Q_OBJECT
public:
    explicit WeatherDataManager(QObject *parent = nullptr);
    void setCurrentCityWeather(const QByteArray &replyData);
    CityWeather currentCityWeather() const;
    void getCityWeather(const QString &city);
    static WeatherDataManager *getWeatherDataManagerInstence();

private:
    WeatherDataManager(const WeatherDataManager&);
    WeatherDataManager& operator=(const WeatherDataManager&);
    void initConnection();

signals:
    void getCityWeatherFinished(const CityWeather &cityWeather);


private slots:
    void onGetWeatherInfoFinished(QUuid id, const QByteArray &replyData);

private:
    CityWeather m_currentCityWeather;
    QList<QUuid> m_requestingIDList;
    WeatherWidgetService *m_weatherService;
    static WeatherDataManager *m_dataManager;
};

#endif // WEATHERDATAMANAGER_H
