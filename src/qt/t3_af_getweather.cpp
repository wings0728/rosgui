#include "../../include/rosgui/qt/t3_af_getweather.hpp"
#include "ui_t3_af_getweather.h"

#include <QByteArray>
#include <QXmlStreamReader>

//界面构造函数
T3_AF_getWeather::T3_AF_getWeather(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::T3_AF_getWeather)
{
    //界面布局初始化
    ui->setupUi(this);
    //连接网络和信号收发
    _manager = new QNetworkAccessManager;
    _url1 = "http://wthrcdn.etouch.cn/WeatherApi?citykey=101280601";
    _manager->get(QNetworkRequest(QUrl(_url1)));
    connect(_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replayFinished(QNetworkReply*)));
    //日志
    T3LOG("++ 天气预报获取");
}

//获取reply的信息
void T3_AF_getWeather::replayFinished(QNetworkReply *reply)
{
    QByteArray byte_ = reply->readAll();
    QString result_;
    result_ = byte_;
    getWeather(result_);

}

//xml解读
void T3_AF_getWeather::getWeather(QString result)
{
    QXmlStreamReader getWeather_(result);
    while(!getWeather_.atEnd())
    {
        if(getWeather_.hasError())
        {
            T3LOG("ERROR!");
            return;
        }
        else if(getWeather_.isStartElement())
        {
            if("city" == getWeather_.name())
            {
                _today._city_= getWeather_.readElementText();
            }
            else if("wendu" == getWeather_.name())
            {
                _today._temprature_ = getWeather_.readElementText();
            }
            else if("fengli" == getWeather_.name())
            {
                _today._windForce_ = getWeather_.readElementText();
            }
            else if("shidu" == getWeather_.name())
            {
                _today._wet_ = getWeather_.readElementText();
            }
            else if("fengxiang" == getWeather_.name())
            {
                _today._windDirection_ = getWeather_.readElementText();
            }
            else if("sunrise_1" == getWeather_.name())
            {
                _today._sunrise_ = getWeather_.readElementText();
            }
            else if("sunset_1" == getWeather_.name())
            {
                _today._sunset_ = getWeather_.readElementText();
            }
            else if("pm25" == getWeather_.name())
            {
                _today._pm25_ = getWeather_.readElementText();
            }
            else if("quality" == getWeather_.name())
            {
                _today._quality_ = getWeather_.readElementText();
                emit getReady(_today);
                //输出当日天气
                qDebug() << _today._city_
                         << _today._pm25_
                         << _today._quality_
                         << _today._sunrise_
                         << _today._sunset_
                         << _today._temprature_+"C"
                         << _today._wet_
                         << _today._windDirection_
                         << _today._windForce_;
                getWeather_.clear();
                return;
            }
            else
            {
                getWeather_.readNext();

            }

        }
        else
            getWeather_.readNext();
    }
    getWeather_.clear();
}

//界面析构函数
T3_AF_getWeather::~T3_AF_getWeather()
{
    delete ui;
    T3LOG("-- 天气预报结束");
}
