#include "../../include/rosgui/qt/t3_af_mainwindow.hpp"
#include "ui_t3_af_mainwindow.h"

//界面构造函数
T3_AF_mainWindow::T3_AF_mainWindow(T3Dialog *welcome, QWidget *parent) :
    T3Dialog(parent),
    ui(new Ui::T3_AF_mainWindow),
    _welcome(welcome)
{
    _father = new T3Dialog;
    //界面布局初始化
    ui->setupUi(this);
    this->move(0, 0);
    this->resize(_father->_width_, _father->_height_);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    this->showFullScreen();
    _weather = new T3_AF_getWeather;
    ui->_dateLabel_->setText("");
    ui->_dateLabel_->setStyleSheet("color:white");
    ui->_timeLabel_->setText("");
    ui->_timeLabel_->setStyleSheet("color:white");
    ui->_exitPushBtn_->setText("");
    ui->_exitPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_exitPushBtn_->setStyleSheet("border-image:url(:/Pictures/mainWindow_back.png)");
    ui->_facePushBtn_->setText("");
    ui->_facePushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_facePushBtn_->setStyleSheet("border-image:url(:/Pictures/mainWindow_face.png)");
    ui->_mapBackgroundLabel_->setText("");
    ui->_mapBackgroundLabel_->setStyleSheet("border-image:url(:/Pictures/mainWindow_mapBackground.png)");
    ui->_robotInfoPushBtn_->setText("");
    ui->_robotInfoPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_robotInfoPushBtn_->setStyleSheet("border-image:url(:/Pictures/mainWindow_robotInfo.png)");
    ui->_textLabel_->setText("");
    ui->_textLabel_->setStyleSheet("border-image:url(:/Pictures/mainWindow_text.png)");
    ui->_tempraturePushBtn_->setText("");
    ui->_tempraturePushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_tempraturePushBtn_->setStyleSheet("background:transparent;border-width:0;border-style:outset;color:white");
    ui->_tempratureLabel_->setText("");
    ui->_sunriseTitleLabel_->setText("日出");
    ui->_sunriseTitleLabel_->setStyleSheet("color:white");
    ui->_sunriseLabel_->setText("");
    ui->_sunriseLabel_->setStyleSheet("color:white");
    ui->_sunsetTitleLabel_->setText("日落");
    ui->_sunsetTitleLabel_->setStyleSheet("color:white");
    ui->_sunsetLabel_->setText("");
    ui->_sunsetLabel_->setStyleSheet("color:white");
    ui->_windDirectionLabel_->setText("");
    ui->_windDirectionLabel_->setStyleSheet("color:white");
    ui->_windForceLabel_->setText("");
    ui->_windForceLabel_->setStyleSheet("color:white");
    ui->_wetTitleLabel_->setText("湿度");
    ui->_wetTitleLabel_->setStyleSheet("color:white");
    ui->_wetLabel_->setText("");
    ui->_wetLabel_->setStyleSheet("color:white");
    ui->_pm25TitleLabel_->setText("PM2.5");
    ui->_pm25TitleLabel_->setStyleSheet("color:white");
    ui->_pm25Label_->setText("");
    ui->_pm25Label_->setStyleSheet("color:white");
    ui->_qualityLabel_->setText("");
    ui->_qualityLabel_->setStyleSheet("color:white");
    ui->_qualityTitleLabel_->setText("空气质量");
    ui->_qualityTitleLabel_->setStyleSheet("color:white");
    ui->_mapPushBtn_->setText("");
    ui->_mapPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_mapPushBtn_->setStyleSheet("border-image:url(:/Pictures/mainWindow_map.png)");
    //size
    ui->_dateLabel_->setGeometry(this->width()*0.0688,
                                 this->height()*0.0667,
                                 this->width()*0.1625,
                                 this->height()*0.0667);
    ui->_exitPushBtn_->setGeometry(this->width()*0.9313,
                                   this->height()*0.0178,
                                   this->width()*0.0375,
                                   this->height()*0.0600);
    ui->_facePushBtn_->setGeometry(this->width()*0.0375,
                                   this->height()*0.3111,
                                   this->width()*0.2000,
                                   this->height()*0.4222);
    ui->_mapBackgroundLabel_->setGeometry(this->width()*0.2625,
                                          this->height()*0.2111,
                                          this->width()*0.4875,
                                          this->height()*0.6667);
    ui->_mapPushBtn_->setGeometry(this->width()*0.3000,
                                  this->height()*0.2778,
                                  this->width()*0.4125,
                                  this->height()*0.5111);
    ui->_pm25Label_->setGeometry(this->width()*0.6688,
                                 this->height()*0.0778,
                                 this->width()*0.0625,
                                 this->height()*0.0333);
    ui->_pm25TitleLabel_->setGeometry(this->width()*0.6000,
                                      this->height()*0.0778,
                                      this->width()*0.0688,
                                      this->height()*0.0333);
    ui->_qualityLabel_->setGeometry(this->width()*0.6688,
                                    this->height()*0.1111,
                                    this->width()*0.0625,
                                    this->height()*0.0333);
    ui->_qualityTitleLabel_->setGeometry(this->width()*0.6000,
                                         this->height()*0.1111,
                                         this->width()*0.0688,
                                         this->height()*0.0333);
    ui->_robotInfoPushBtn_->setGeometry(this->width()*0.7688,
                                          this->height()*0.2556,
                                          this->width()*0.1875,
                                          this->height()*0.6000);
    ui->_sunriseLabel_->setGeometry(this->width()*0.3375,
                                    this->height()*0.0778,
                                    this->width()*0.0514,
                                    this->height()*0.0333);
    ui->_sunriseTitleLabel_->setGeometry(this->width()*0.2688,
                                         this->height()*0.0778,
                                         this->width()*0.0688,
                                         this->height()*0.0333);
    ui->_sunsetLabel_->setGeometry(this->width()*0.3375,
                                   this->height()*0.1111,
                                   this->width()*0.0625,
                                   this->height()*0.0333);
    ui->_sunsetTitleLabel_->setGeometry(this->width()*0.2688,
                                        this->height()*0.1111,
                                        this->width()*0.0688,
                                        this->height()*0.0333);
    ui->_tempratureLabel_->setGeometry(this->width()*0.4125,
                                       this->height()*0.0333,
                                       this->width()*0.1750,
                                       this->height()*0.1111);
    ui->_tempraturePushBtn_->setGeometry(this->width()*0.4125,
                                         this->height()*0.0333,
                                         this->width()*0.1750,
                                         this->height()*0.1111);
    ui->_textLabel_->setGeometry(this->width()*0.0375,
                                 this->height()*0.8000,
                                 this->width()*0.2000,
                                 this->height()*0.0889);
    ui->_timeLabel_->setGeometry(this->width()*0.0688,
                                 this->height()*0.1111,
                                 this->width()*0.1625,
                                 this->height()*0.1778);
    ui->_wetLabel_->setGeometry(this->width()*0.6688,
                                this->height()*0.0444,
                                this->width()*0.0625,
                                this->height()*0.0333);
    ui->_wetTitleLabel_->setGeometry(this->width()*0.6000,
                                     this->height()*0.0444,
                                     this->width()*0.0688,
                                     this->height()*0.0333);
    ui->_windDirectionLabel_->setGeometry(this->width()*0.2688,
                                          this->height()*0.0444,
                                          this->width()*0.0688,
                                          this->height()*0.0333);
    ui->_windForceLabel_->setGeometry(this->width()*0.3375,
                                      this->height()*0.0444,
                                      this->width()*0.0625,
                                      this->height()*0.0333);



    //界面浮现动画
//    QPropertyAnimation *animation_ = new QPropertyAnimation(this, "windowOpacity");
//    animation_->setDuration(300);
//    animation_->setStartValue(0);
//    animation_->setEndValue(1);
//    animation_->start();
    //定时器
    QTimer *timer_ = new QTimer(this);
    timer_->start(100);
    //链接ui部件与功能
    connect(timer_, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    connect(ui->_exitPushBtn_, &QPushButton::clicked, this, &T3_AF_mainWindow::exitToWelcome);
    connect(ui->_facePushBtn_, &QPushButton::clicked, this, &T3_AF_mainWindow::toFace);
    //connect(ui->_tempraturePushBtn_, &QPushButton::clicked, this, &T3_AF_mainWindow::toWeatherForecast);
    connect(ui->_mapPushBtn_, &QPushButton::clicked, this, &T3_AF_mainWindow::toMap);
    //connect(ui->_robotInfoPushBtn_, &QPushButton::clicked, this, &T3_AF_mainWindow::toRobotInfo);
    connect(_weather, &T3_AF_getWeather::getReady, this, &T3_AF_mainWindow::weatherUpdate);
    //日志
    T3LOG("3+ 主界面构造");
}

//显示时间
void T3_AF_mainWindow::timeUpdate()
{
    QDateTime dateTime_ = QDateTime::currentDateTime();
    QString dataStr_ = dateTime_.toString("yyyy-MM-dd dddd");
    QString timeStr_ = dateTime_.toString("hh:mm");
    ui->_dateLabel_->setText(dataStr_);
    ui->_timeLabel_->setText(timeStr_);
}

//更新天气
void T3_AF_mainWindow::weatherUpdate(Today today)
{
    QString temprature_ = today._temprature_ + "℃";
    //ui->_tempraturePushBtn_->setText(temprature_);
    ui->_tempratureLabel_->setText(temprature_);
    ui->_wetLabel_->setText(today._wet_);
    ui->_windDirectionLabel_->setText(today._windDirection_);
    ui->_windForceLabel_->setText(today._windForce_);
    ui->_sunriseLabel_->setText(today._sunrise_);
    ui->_sunsetLabel_->setText(today._sunset_);
    ui->_pm25Label_->setText(today._pm25_);
    ui->_qualityLabel_->setText(today._quality_);
}

//界面背景绘制
void T3_AF_mainWindow::paintEvent(QPaintEvent *)
{
    QPainter paint_(this);
    paint_.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/Pictures/mainWindow_background.png"));
}

//退出
void T3_AF_mainWindow::exitToWelcome()
{
    T3_AF_confirmExit *confirmExit_ = new T3_AF_confirmExit(_welcome, this);
    confirmExit_->show();
}

//进入face
void T3_AF_mainWindow::toFace()
{
    T3_AF_face *face_ = new T3_AF_face(this);
    face_->show();
    this->hide();
}

//进入weatherForecast
void T3_AF_mainWindow::toWeatherForecast()
{
    T3_AF_weatherForecast *weatherForecast_ = new T3_AF_weatherForecast(this);
    weatherForecast_->show();
    this->hide();
}

//进入map
void T3_AF_mainWindow::toMap()
{
    T3_AF_map *map_ = new T3_AF_map(this);
    map_->show();
    this->hide();
}

//进入robotInfo
void T3_AF_mainWindow::toRobotInfo()
{
    T3_AF_robotInfo *robotInfo_ = new T3_AF_robotInfo(this);
    robotInfo_->show();
    this->hide();
}

//
void T3_AF_mainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

void T3_AF_mainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}

//界面析构函数
T3_AF_mainWindow::~T3_AF_mainWindow()
{
    delete ui;
    delete _weather;
    //日志
    T3LOG("3- 主界面析构");
}
