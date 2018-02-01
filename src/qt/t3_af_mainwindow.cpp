#include "../../include/rosgui/qt/t3_af_mainwindow.hpp"
#include "ui_t3_af_mainwindow.h"

//界面构造函数
T3_AF_mainWindow::T3_AF_mainWindow(T3Dialog *welcome, QWidget *parent) :
    T3Dialog(parent),
    ui(new Ui::T3_AF_mainWindow),
    _welcome(welcome)
{
    _father = new T3Dialog;
    _map = new T3_AF_map(this);
    _map->hide();
    //界面布局初始化
    ui->setupUi(this);
    this->setGeometry(0, 0, _father->_width_, _father->_height_);
//    this->move(0, 0);
//    this->resize(_father->_width_, _father->_height_);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    this->showFullScreen();
    _weather = new T3_AF_getWeather;
    _stopPushBtn_ = new QPushButton(this);
    _stopPushBtn_->setFocusPolicy(Qt::NoFocus);
    _battQString = "";
    _stopPushBtn_->setStyleSheet("QPushButton{border-image:url(:/Pictures/mainWindow_stop.png);}"
                                 "QPushButton:pressed{border-image:url(:/Pictures/mainWindow_stop2.png);}");
    _stopPushBtn_->show();
    _stopPushBtn_->setText("");
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
    ui->_battery_->setText(_battQString);
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
    ui->_robotInfoPushBtn_->setGeometry(this->width()*0.7375,
                                          this->height()*0.0889,
                                          this->width()*0.2000,
                                          this->height()*0.6222);
    ui->_sunriseLabel_->setGeometry(this->width()*0.3375,
                                    this->height()*0.0778,
                                    this->width()*0.0625,
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
    _stopPushBtn_->setGeometry(this->width()*0.7500,
                               this->height()*0.7333,
                               this->width()*0.1875,
                               this->height()*0.2000);
    ui->_battery_->setGeometry(this->width()*0.5993,
                               this->height()*0.91,
                               this->width()*0.0875,
                               this->height()*0.06);
    ui->_battIMG_->setGeometry(this->width()*0.3430,
                               this->height()*0.91,
                               this->width()*0.2375,
                               this->height()*0.06);
    ui->_battGIF_->setGeometry(this->width()*0.3430,
                               this->height()*0.91,
                               this->width()*0.2375,
                               this->height()*0.06);

    QMovie *battLow_ = new QMovie(":/Pictures/batt_4.gif");
    battLow_->setScaledSize(QSize(ui->_battGIF_->width(), ui->_battGIF_->height()));
    battLow_->setSpeed(130);
    ui->_battGIF_->setMovie(battLow_);
    battLow_->start();
    //font
    QFont dateLabelFont_;
    dateLabelFont_.setPointSize(ui->_dateLabel_->height() * kLabelFontScal*0.55);
    QFont timeLabelFont_;
    timeLabelFont_.setPointSize(ui->_timeLabel_->height() * kLabelFontScal*0.8);
    QFont windDirectionLabelFont_;
    windDirectionLabelFont_.setPointSize(ui->_windDirectionLabel_->height() * kLabelFontScal);
    QFont windForceLabelFont_;
    windForceLabelFont_.setPointSize(ui->_windForceLabel_->height() * kLabelFontScal);
    QFont sunriseTitleLabelFont_;
    sunriseTitleLabelFont_.setPointSize(ui->_sunriseTitleLabel_->height() * kLabelFontScal);
    QFont sunriseLabelFont_;
    sunriseLabelFont_.setPointSize(ui->_sunriseLabel_->height() * kLabelFontScal);
    QFont sunsetTitleLabelFont_;
    sunsetTitleLabelFont_.setPointSize(ui->_sunsetTitleLabel_->height() * kLabelFontScal);
    QFont sunsetLabelFont_;
    sunsetLabelFont_.setPointSize(ui->_sunsetLabel_->height() * kLabelFontScal);
    QFont tempratureLabelFont_;
    tempratureLabelFont_.setPointSize(ui->_tempratureLabel_->height() * kLabelFontScal);
    QFont wetTitleLabelFont_;
    wetTitleLabelFont_.setPointSize(ui->_wetTitleLabel_->height() * kLabelFontScal);
    QFont wetLabelFont_;
    wetLabelFont_.setPointSize(ui->_wetLabel_->height() * kLabelFontScal);
    QFont pm25TitleLabelFont_;
    pm25TitleLabelFont_.setPointSize(ui->_pm25TitleLabel_->height() * kLabelFontScal);
    QFont pm25LabelFont_;
    pm25LabelFont_.setPointSize(ui->_pm25Label_->height() * kLabelFontScal);
    QFont qualityTitleLabelFont_;
    qualityTitleLabelFont_.setPointSize(ui->_qualityTitleLabel_->height() * kLabelFontScal);
    QFont qualityLabelFont_;
    qualityLabelFont_.setPointSize(ui->_qualityLabel_->height() * kLabelFontScal);
    ui->_dateLabel_->setFont(dateLabelFont_);
    ui->_timeLabel_->setFont(timeLabelFont_);
    ui->_windDirectionLabel_->setFont(windDirectionLabelFont_);
    ui->_windForceLabel_->setFont(windForceLabelFont_);
    ui->_sunriseTitleLabel_->setFont(sunriseTitleLabelFont_);
    ui->_sunriseLabel_->setFont(sunriseLabelFont_);
    ui->_sunsetTitleLabel_->setFont(sunsetTitleLabelFont_);
    ui->_sunsetLabel_->setFont(sunsetLabelFont_);
    ui->_tempratureLabel_->setFont(tempratureLabelFont_);
    ui->_wetTitleLabel_->setFont(wetTitleLabelFont_);
    ui->_wetLabel_->setFont(wetLabelFont_);
    ui->_pm25TitleLabel_->setFont(pm25TitleLabelFont_);
    ui->_pm25Label_->setFont(pm25LabelFont_);
    ui->_qualityTitleLabel_->setFont(qualityTitleLabelFont_);
    ui->_qualityLabel_->setFont(qualityLabelFont_);
    QFont battFont_;
    battFont_.setPointSize(ui->_battery_->height() * kLabelFontScal);
    ui->_battery_->setFont(battFont_);
    //界面浮现动画
//    QPropertyAnimation *animation_ = new QPropertyAnimation(this, "windowOpacity");
//    animation_->setDuration(150);
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
    connect(_stopPushBtn_, &QPushButton::clicked, this, &T3_AF_mainWindow::stopRobot);
    //connect(_qnode, SIGNAL(lowPower()), this, SLOT(lowBatt()));
    //
    _qnode = rosgui::QNode::getInstance();
    //日志
    T3LOG("3+ 主界面构造");

}

//void T3_AF_mainWindow::lowBatt()
//{
//    emit lowBattSignal();
//    if(rosgui::QNode::Auto == _qnode->getOprationMode())
//    {
//        _qnode->goalUpdate(0.0, 0.0, 0.0);
//    }
//    else
//    {
//        _qnode->setManualCmd(rosgui::QNode::Stop);
//        _qnode->setOperationMode(rosgui::QNode::Auto);
//        _qnode->goalUpdate(0.0, 0.0, 0.0);
//    }
//}

//显示时间
void T3_AF_mainWindow::timeUpdate()
{
    QDateTime dateTime_ = QDateTime::currentDateTime();
    QString dataStr_ = dateTime_.toString("yyyy-MM-dd dddd");
    QString timeStr_ = dateTime_.toString("hh:mm");
    ui->_dateLabel_->setText(dataStr_);
    ui->_timeLabel_->setText(timeStr_);
}

void T3_AF_mainWindow::battery()
{
    _battInt = _qnode->getBatt();
    _battQString = QString::number(_battInt) + "%";
    ui->_battery_->setText(_battQString);
    if(_battInt <= 30)
    {
        ui->_battIMG_->setStyleSheet("");
    }
    else if(_battInt > 30 && _battInt <= 60)
    {
        ui->_battIMG_->setStyleSheet("border-image:url(:/Pictures/batt_3.png)");
    }
    else if(_battInt > 60 && _battInt <= 90)
    {
        ui->_battIMG_->setStyleSheet("border-image:url(:/Pictures/batt_2.png)");
    }
    else if(_battInt > 90)
    {
        ui->_battIMG_->setStyleSheet("border-image:url(:/Pictures/batt_1.png)");
    }
    update();
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
    battery();
//    qDebug() << "refreshed";
}

//退出
void T3_AF_mainWindow::exitToWelcome()
{
    T3_AF_confirmExit *confirmExit_ = new T3_AF_confirmExit(_welcome, this);
    confirmExit_->show();
}

//stop
void T3_AF_mainWindow::stopRobot()
{
    _qnode->setOperationMode(rosgui::QNode::Manual);
    _qnode->setManualCmd(rosgui::QNode::Stop);
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
    _map->show();
    emit updateMode();
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
    delete _stopPushBtn_;
    delete _map;
    //日志
    T3LOG("3- 主界面析构");
}
