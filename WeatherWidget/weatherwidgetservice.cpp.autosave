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
#include <QTextCodec>
#include "weatherDataType.h"

static QMutex Mutex;
WeatherWidgetService *WeatherWidgetService::m_service = nullptr;

WeatherWidgetService::WeatherWidgetService(QObject *parent) : QObject(parent)
{
    startThread();
    if(!Utils::getWeatherServiceKey(m_privateKey,m_uid)){
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

void WeatherWidgetService::getCityWeatherInfo(const QUuid &id, const QString &city)
{
    QMetaObject::invokeMethod(this, "onGetCityWeatherInfo", Qt::QueuedConnection,
                              Q_ARG(QUuid, id), Q_ARG(QString, city));
}

void WeatherWidgetService::onGetCityWeatherInfo(QUuid id, const QString &city)
{
    qDebug() << __func__ << QThread::currentThreadId() << "start" << endl;
    QNetworkAccessManager manager;
    QNetworkRequest request;
    QEventLoop loop;
    QTimer timer;

//    心知天气 api调试通过
    QString time = QString::number(QDateTime::currentDateTime().toTime_t());
    QString ttl = "500";
    QString para = QString("ts=%1&ttl=%2&uid=%3").arg(time).arg(ttl).arg(m_uid);
    QString s = Utils::getWeatherServiceSig(para,m_privateKey);
    QString paraSig = para + QString("&sig=%1").arg(s);

    QUrl url = QString("https://api.seniverse.com/v3/weather/now.json?%1&location=%2&language=zh-Hans&unit=c")
            .arg(paraSig).arg(city);
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
            emit getCityWeatherInfoFinished(id,replyData);
            pReply->close();
            pReply->deleteLater();
            pReply = nullptr;
        } else {
            pReply->close();
            pReply->deleteLater();
            pReply = nullptr;
        }
    }
    qDebug() << __func__ << QThread::currentThreadId() << "end" << endl;
}


