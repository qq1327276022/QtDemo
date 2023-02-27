#include "weatherwidgetservice.h"
#include "utils.h"

#include <QMutex>
#include <QMutexLocker>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QTimer>
#include <QDateTime>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextCodec>
QMutex Mutex;
WeatherWidgetService *WeatherWidgetService::m_service = nullptr;

WeatherWidgetService::WeatherWidgetService(QObject *parent) : QObject(parent)
{
    startThread();
    if(Utils::getWeatherServiceKey(m_privateKey,m_uid)){
        qDebug() << " get weather service info error!"<<endl;
    }
}

void WeatherWidgetService::startThread()
{
    if(nullptr == m_thread){
        m_thread = new QThread;
        this->moveToThread(m_thread);
        m_thread->start();
    }
}

void WeatherWidgetService::quitThread()
{
    if(nullptr == m_thread){
        return;
    }

    m_thread->requestInterruption();
    m_thread->quit();
    m_thread->wait();
    m_thread->deleteLater();
    m_thread = nullptr;
}

WeatherWidgetService *WeatherWidgetService::getWeatherWidgetServiceInstence()
{
    if(nullptr == m_service){
        QMutexLocker locker(&Mutex);
        if(nullptr == m_service){
            m_service = new WeatherWidgetService;
        }
    }

    return m_service;
}

int WeatherWidgetService::getCityWeatherInfo(const QString &city)
{
    QMetaObject::invokeMethod(this, "getCityWeatherInfo", Qt::QueuedConnection,
                              Q_ARG(int, ++m_requestCount), Q_ARG(QString, city));
    return m_requestCount;
}

void WeatherWidgetService::getCityWeatherInfo(int requestCount, const QString &city)
{
    QNetworkAccessManager manager;
    QNetworkRequest request;
    QEventLoop loop;
    QTimer timer;

//    心知天气 api调试通过
    QString time = QString::number(QDateTime::currentDateTime().toTime_t());
    QString ttl = "500";
    QString url = QString("ts=%1&ttl=%2&uid=%3").arg(time).arg(ttl).arg(m_uid);
    QString sig = Utils::getWeatherServiceSig(url,m_privateKey);
    url += QString("&sig=%1").arg(sig);

    url = QString("https://api.seniverse.com/v3/weather/now.json?%1&location=%2&language=zh-Hans&unit=c").arg(url).arg(city);
    request.setUrl(url);
    qInfo() << request.url();
    QNetworkReply *pReply = manager.get(request);
    connect(pReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    QTextCodec *code = QTextCodec::codecForName("UTF-8");

    if (pReply) {
        timer.setSingleShot(true);
        timer.start(5000);
        loop.exec();
        qDebug() << pReply->error();
        if (QNetworkReply::NoError == pReply->error()) {
            QByteArray replyData = pReply->readAll();
            qDebug()<< code->toUnicode(replyData) << endl;
            QJsonParseError error;
            QJsonDocument d = QJsonDocument::fromJson(replyData,&error);
            if(error.error != QJsonParseError::ParseError::NoError){
                qDebug() <<"parse error" <<endl;
            }

            if(d.object().contains("results")){
                qDebug() << d.object().value("results").isArray()<< endl;
                QJsonArray array = d.object().value("results").toArray();
                QJsonObject resultsObject = array.first().toObject();
                if(resultsObject.contains("now")){
                    QJsonObject nowObject = resultsObject.value("now").toObject();
                    if(nowObject.contains("text")){
                        qDebug() << nowObject.value("text").toString();
                    }
                }
            }

            pReply->close();
            pReply->deleteLater();
            pReply = nullptr;
        } else {
            pReply->close();
            pReply->deleteLater();
            pReply = nullptr;
        }
    }

}


