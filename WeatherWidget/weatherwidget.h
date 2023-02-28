#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include <QWidget>
#include <QUuid>

#include "weatherwidgetservice.h"
#include "weatherdatamanager.h"
#include "rightbasewidget.h"

class WeatherWidget : public RightBaseWidget
{
    Q_OBJECT
public:
    explicit WeatherWidget(QWidget *parent = nullptr);
    ~WeatherWidget();

private:
    void initUi();
    void initConnection();
    void getCityWeather(const QString &city);

signals:
private slots:
    void onGetWeatherInfoFinished(const CityWeather &cityWeather);

private:
    QList<QUuid> m_requestingID;
    WeatherDataManager *m_weatherDataManager;
};

#endif // WEATHERWIDGET_H
