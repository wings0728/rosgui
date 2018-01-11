#ifndef T3_AF_GETWEATHER_H
#define T3_AF_GETWEATHER_H

#include "t3_af_config.hpp"
#include <QDialog>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

namespace Ui {
class T3_AF_getWeather;
}

struct Today
{
    QString _city_;
    QString _temprature_;
    QString _windForce_;
    QString _windDirection_;
    QString _wet_;
    QString _sunset_;
    QString _sunrise_;
    QString _pm25_;
    QString _quality_;
};

class T3_AF_getWeather : public QDialog
{
    Q_OBJECT

public:
    explicit T3_AF_getWeather(QWidget *parent = 0);
    ~T3_AF_getWeather();

    void getWeather(QString result);

    Today _today;

signals:
    void getReady(Today today);

private slots:
    void replayFinished(QNetworkReply *reply);

private:
    Ui::T3_AF_getWeather *ui;
    QNetworkAccessManager *_manager;
    QString _url1;
};

#endif // T3_AF_GETWEATHER_H
