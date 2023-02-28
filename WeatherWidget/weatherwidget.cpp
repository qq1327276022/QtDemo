#include "weatherwidget.h"

#include <QPushButton>
#include <QDebug>
#include <QPainter>

WeatherWidget::WeatherWidget(QWidget *parent) : RightBaseWidget(parent)
{

    m_weatherDataManager = WeatherDataManager::getWeatherDataManagerInstence();
    initConnection();
    getCityWeather("南京");
}

WeatherWidget::~WeatherWidget()
{
    WeatherWidgetService::getWeatherWidgetServiceInstence()->quitThread();
}

void WeatherWidget::initUi()
{

}

void WeatherWidget::initConnection()
{
    connect(m_weatherDataManager,&WeatherDataManager::getCityWeatherFinished,
            this,&WeatherWidget::onGetWeatherInfoFinished);
}

void WeatherWidget::getCityWeather(const QString &city)
{
    m_weatherDataManager->getCityWeather(city);
}

void WeatherWidget::onGetWeatherInfoFinished(const CityWeather &cityWeather)
{
    qDebug() << __func__ << cityWeather.city_id << cityWeather.city_name << cityWeather.city_weather << endl;
}


