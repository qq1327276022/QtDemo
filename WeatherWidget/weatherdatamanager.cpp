#include "weatherdatamanager.h"
#include <QMutex>

static QMutex Mutex;
WeatherDataManager *WeatherDataManager::m_dataManager = nullptr;

WeatherDataManager *WeatherDataManager::getWeatherDataManagerInstence()
{
    if(nullptr == m_dataManager){
        QMutexLocker locker(&Mutex);
        if(nullptr == m_dataManager){
            m_dataManager = new WeatherDataManager;
        }
    }

    return m_dataManager;
}

void WeatherDataManager::initConnection()
{
    qRegisterMetaType<CityWeather>("CityWeather");
    connect(m_weatherService,&WeatherWidgetService::getCityWeatherInfoFinished,
            this,&WeatherDataManager::onGetWeatherInfoFinished);
}


WeatherDataManager::WeatherDataManager(QObject *parent) : QObject(parent)
{
    m_weatherService = WeatherWidgetService::getWeatherWidgetServiceInstence();
    initConnection();
}

void WeatherDataManager::setCurrentCityWeather(const QByteArray &replyData)
{
    m_currentCityWeather = CityWeather(replyData);
}

CityWeather WeatherDataManager::currentCityWeather() const
{
    return m_currentCityWeather;
}

void WeatherDataManager::getCityWeather(const QString &city)
{
    QUuid id = QUuid::createUuid();
    m_requestingIDList.append(id);
    m_weatherService->getCityWeatherInfo(id,city);
}

void WeatherDataManager::onGetWeatherInfoFinished(QUuid id, const QByteArray &replyData)
{
    if(!m_requestingIDList.contains(id))
        return;

    m_currentCityWeather = CityWeather(replyData);
    emit getCityWeatherFinished(m_currentCityWeather);
}
