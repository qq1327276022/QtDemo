#ifndef WEATHERDATATYPE_H
#define WEATHERDATATYPE_H
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextCodec>
#include <QDebug>

struct CityWeather{
    QString city_id; //城市id -1時表示异常
    QString city_name;
    QString city_weather;
    QString city_temperature;
    QString lastUpdateDate;
    CityWeather(){
        city_id = "";
        city_name = "";
        city_weather = "";
        city_temperature = "";
    }

    CityWeather(const QByteArray &data){
        QJsonParseError error;
        QJsonDocument d = QJsonDocument::fromJson(data,&error);
        if(error.error != QJsonParseError::ParseError::NoError){
            qDebug() <<"parse error" <<endl;
            city_id = "-1";
            return;
        }

        if(d.object().contains("results")){
            qDebug() << d.object().value("results").isArray()<< endl;
            QJsonArray array = d.object().value("results").toArray();
            QJsonObject resultsObject = array.first().toObject();
            if(resultsObject.contains("location")){
                QJsonObject locationObject = resultsObject.value("location").toObject();
                if(locationObject.contains("id")){
                   city_id = locationObject.value("id").toString();
                }
                if(locationObject.contains("name")){
                   city_name = locationObject.value("name").toString();
                }
            }
            if(resultsObject.contains("now")){
                QJsonObject nowObject = resultsObject.value("now").toObject();
                if(nowObject.contains("text")){
                    city_weather = nowObject.value("text").toString();
                }
                if(nowObject.contains("temperature")){
                    city_temperature = nowObject.value("temperature").toString();
                }
                if(nowObject.contains("last_update")){
                    lastUpdateDate = nowObject.value("last_update").toString();
                }
            }
        }
    }
};

#endif // WEATHERDATATYPE_H
