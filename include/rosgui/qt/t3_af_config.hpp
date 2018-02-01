#ifndef T3_AF_CONFIG_H
#define T3_AF_CONFIG_H

//常用库
#include <QPropertyAnimation>
#include <QPainter>
#include <QTimer>
#include <QDateTime>
#include <QMovie>
#include "t3_af_getweather.hpp"
#include <QCloseEvent>
#include <QKeyEvent>
#include <QSqlDatabase>
#include <QSqlQuery>

//T3LOG
#include <QDebug>
#include <string.h>
#include <stdio.h>

#define T3LOG(format, ...); qDebug(format , ##__VA_ARGS__);

//k
#define kMapScal 9.0
#define kPi 3.141592653
#define kDelay 1000
#define kLabelFontScal 0.6
#define kBtnFontScal 0.4
#define kForwardName "F"
#define kBackwardName "B"
#define kLeftTurnName "L"
#define kRighTurnName "R"
#define kStopName "S"

//ros
#define kLowPowerLimit 20

#endif // T3_AF_CONFIG_H
