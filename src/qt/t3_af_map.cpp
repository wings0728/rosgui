#include "../../include/rosgui/qt/t3_af_map.hpp"
#include "ui_t3_af_map.h"


//界面构造函数
T3_AF_map::T3_AF_map(T3Dialog *mainWindow, QWidget *parent) :
    T3Dialog(parent),
    _mainWindow(mainWindow),
    ui(new Ui::T3_AF_map),
    _pos_(6, -2.0),
    _arrow_(6, 0.0),
    _robotPose(4, 0.0),
    _mapOrigin(3, 0.0)
{
    i=0;
    _father = new T3Dialog;
    //界面布局初始化
    ui->setupUi(this);
    this->setGeometry(0, 0, _father->_width_, _father->_height_);
//    this->move(0, 0);
//    this->resize(_father->_width_, _father->_height_);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    this->showFullScreen();
    //
    _forwardPusbBtn_ = new QPushButton(this);
    _backwordPushBtn_ = new QPushButton(this);
    _leftTurnPushBtn_ = new QPushButton(this);
    _rightTurnPushBtn_ = new QPushButton(this);
    _stopPushBtn_ = new QPushButton(this);
    _backToOrigin_ = new QPushButton(this);
    _lineSLabel_ = new QLabel(this);
    _angleSLabel_ = new QLabel(this);
    _forwardPusbBtn_->setObjectName(kForwardName);
    _backwordPushBtn_->setObjectName(kBackwardName);
    _leftTurnPushBtn_->setObjectName(kLeftTurnName);
    _rightTurnPushBtn_->setObjectName(kRighTurnName);
    _stopPushBtn_->setObjectName(kStopName);
    _forwardPusbBtn_->setFocusPolicy(Qt::NoFocus);
    _backwordPushBtn_->setFocusPolicy(Qt::NoFocus);
    _leftTurnPushBtn_->setFocusPolicy(Qt::NoFocus);
    _rightTurnPushBtn_->setFocusPolicy(Qt::NoFocus);
    _stopPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_stopPushBtn_->setFocusPolicy(Qt::NoFocus);
    _backToOrigin_->setFocusPolicy(Qt::NoFocus);
    _backToOrigin_->setText("回到原点");
    _backToOrigin_->setStyleSheet("border-image:url(:/Pictures/clearPath.png)");
    ui->_stopPushBtn_->setStyleSheet("QPushButton{border-image:url(:/Pictures/mainWindow_stop.png);}"
                                     "QPushButton:pressed{border-image:url(:/Pictures/mainWindow_stop2.png);}");
    _lineSLabel_->setText("");
    _angleSLabel_->setText("");
    _lineSLabel_->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    _angleSLabel_->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->_exitPushBtn_->setText("");
    ui->_exitPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_exitPushBtn_->setStyleSheet("border-image:url(:/Pictures/map_back.png)");
    ui->_dateTimeLabel_->setText("");
    ui->_dateTimeLabel_->setStyleSheet("color:rgb(7, 221, 225)");
    ui->_showConnectStatus_->setText("未连接        ");
    ui->_showConnectStatus_->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->_showConnectStatus_->setStyleSheet("border-image:url(:/Pictures/off.png)");
    ui->_modePushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_modePushBtn_->setCheckable(true);
    ui->_clear->setFocusPolicy(Qt::NoFocus);
    //size
    ui->_modePushBtn_->setGeometry(this->width()*0.8075,
                                     this->height()*0.2067,
                                     this->width()*0.1225,
                                     this->height()*0.0800);
    ui->_clear->setGeometry(this->width()*0.5050,
                            this->height()*0.4956,
                            this->width()*0.1125,
                            this->height()*0.0667);
    _backToOrigin_->setGeometry(this->width()*0.5050,
                                this->height()*0.5750,
                                this->width()*0.1125,
                                this->height()*0.0667);
    ui->_dateTimeLabel_->setGeometry(this->width()*0.6450,
                                     this->height()*0.9333,
                                     this->width()*0.1620,
                                     this->height()*0.034);
    ui->_battery_->setGeometry(this->width()*0.636,
                               this->height()*0.93,
                               this->width()*0.0438,
                               this->height()*0.034);
    ui->_battIMG_->setGeometry(this->width()*0.5100,
                               this->height()*0.9403,
                               this->width()*0.1188,
                               this->height()*0.027);
    ui->_battGIF_->setGeometry(this->width()*0.5100,
                               this->height()*0.9403,
                               this->width()*0.1188,
                               this->height()*0.027);
    ui->_exitPushBtn_->setGeometry(this->width()*0.9313,
                                   this->height()*0.0178,
                                   this->width()*0.0375,
                                   this->height()*0.0600);
    ui->_showConnectStatus_->setGeometry(this->width()*0.8075,
                                         this->height()*0.1067,
                                         this->width()*0.1225,
                                         this->height()*0.0800);
    ui->_videoLabel_->setGeometry(this->width()*0.5050,
                                  this->height()*0.0822,
                                  this->width()*0.2763,
                                  this->height()*0.3689);
    ui->_videoSquareLabel_->setGeometry(this->width()*0.5050,
                                        this->height()*0.0822,
                                        this->width()*0.2763,
                                        this->height()*0.3689);
    ui->_stopPushBtn_->setGeometry(this->width()*0.5125,
                                   this->height()*0.7000,
                                   this->width()*0.1750,
                                   this->height()*0.2000);
    _forwardPusbBtn_->setGeometry(this->width()*0.7750,
                                  this->height()*0.4222,
                                  this->width()*0.1275,
                                  this->height()*0.1333);
    _backwordPushBtn_->setGeometry(this->width()*0.7750,
                                   this->height()*0.7956,
                                   this->width()*0.1275,
                                   this->height()*0.1333);
    _leftTurnPushBtn_->setGeometry(this->width()*0.6963,
                                   this->height()*0.5622,
                                   this->width()*0.0750,
                                   this->height()*0.2267);
    _rightTurnPushBtn_->setGeometry(this->width()*0.9063,
                                     this->height()*0.5622,
                                     this->width()*0.0750,
                                     this->height()*0.2267);
    _stopPushBtn_->setGeometry(this->width()*0.7750,
                               this->height()*0.5622,
                               this->width()*0.1275,
                               this->height()*0.2267);
    _lineSLabel_->setGeometry(this->width()*0.875,
                               this->height()*0.38,
                               this->width()*0.1,
                               this->height()*0.0444);
    _angleSLabel_->setGeometry(this->width()*0.875,
                               this->height()*0.4244,
                               this->width()*0.1,
                               this->height()*0.0444);
    QMovie *battLow_ = new QMovie(":/Pictures/batt_4.gif");
    battLow_->setScaledSize(QSize(ui->_battGIF_->width(), ui->_battGIF_->height()));
    battLow_->setSpeed(130);
    ui->_battGIF_->setMovie(battLow_);
    battLow_->start();

    _forwardPusbBtn_->setCheckable(true);
    _forwardPusbBtn_->show();
    _backwordPushBtn_->show();
    _leftTurnPushBtn_->show();
    _rightTurnPushBtn_->show();
    _stopPushBtn_->show();
    _backToOrigin_->show();
    _lineSLabel_->show();
    _angleSLabel_->show();
    //font
    QFont showConnectStatusFont_;
    showConnectStatusFont_.setPointSize(ui->_showConnectStatus_->height() * kBtnFontScal * 0.6);
    QFont modePushBtnFont_;
    modePushBtnFont_.setPointSize(ui->_modePushBtn_->height() * kBtnFontScal * 0.6);
    QFont clearFont_;
    clearFont_.setPointSize(ui->_clear->height() * kBtnFontScal * 0.72);
    QFont backToOriginFont_;
    backToOriginFont_.setPointSize(_backToOrigin_->height() * kBtnFontScal * 0.72);
    QFont dateTimaLabelFont_;
    dateTimaLabelFont_.setPointSize(ui->_dateTimeLabel_->height() * kLabelFontScal * 0.75);
    ui->_showConnectStatus_->setFont(showConnectStatusFont_);
    ui->_modePushBtn_->setFont(modePushBtnFont_);
    ui->_clear->setFont(clearFont_);
    ui->_dateTimeLabel_->setFont(dateTimaLabelFont_);
    _backToOrigin_->setFont(backToOriginFont_);
    QFont lineSLabelFont_;
    QFont angleSLabelFont_;
    lineSLabelFont_.setPointSize(_lineSLabel_->height() * kLabelFontScal * 0.6);
    angleSLabelFont_.setPointSize(_angleSLabel_->height() * kLabelFontScal * 0.6);
    _lineSLabel_->setFont(lineSLabelFont_);
    _angleSLabel_->setFont(angleSLabelFont_);
    QFont battFont_;
    battFont_.setPointSize(ui->_battery_->height() * kLabelFontScal * 0.75);
    ui->_battery_->setFont(battFont_);
    //
    _qnode = rosgui::QNode::getInstance();
    _mapStartX = this->width()*0.0313;
    _mapStartY = this->height()*0.0800;
    QImage realMap_;
    realMap_.load(":/Pictures/map_realMap.pgm");
    _realWidth = realMap_.width()/20;
    _realHeight = realMap_.height()/20;
    if(_realWidth >= _realHeight)
    {
        _mapWidth = this->width()*0.45;
        _scale = _mapWidth / _realWidth;
        _mapHeight = _scale * _realHeight;
    }
    else
    {
        _mapHeight = this->height()*0.8;
        _scale = _mapHeight / _realHeight;
        _mapWidth = _scale * _realWidth;
    }
    _startX = 0;
    _startY = 0;
    _moveX = 0;
    _moveY = 0;
    _originX = 0.0;
    _originY = 0.0;
    _lineS = 0.0;
    _angleS = 0.0;
    _lineSText = "";
    _angleSText = "";
    _battInt = 0;
    _battQString = "";
    _mode = _qnode->getOprationMode();
    if(_mode == rosgui::QNode::Manual)
    {
        ui->_modePushBtn_->setText("           手动模式");
        ui->_modePushBtn_->setStyleSheet("border-image:url(:/Pictures/off.png)");
        buttonStatus(true);
    }
    else
    {
        ui->_modePushBtn_->setText("自动模式           ");
        ui->_modePushBtn_->setStyleSheet("border-image:url(:/Pictures/on.png);color:black");
        buttonStatus(false);
    }
    //界面浮现动画
//    QPropertyAnimation *animation_ = new QPropertyAnimation(this, "windowOpacity");
//    animation_->setDuration(150);
//    animation_->setStartValue(0);
//    animation_->setEndValue(1);
//    animation_->start();
    //定时器
    QTimer *timer_ = new QTimer(this);
    timer_->start(100);
    _connect = new QTimer(this);
    _connect->start(5000);
    //链接ui部件与功能
    connect(timer_, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    connect(_connect, SIGNAL(timeout()), this, SLOT(ifConnected()));
    connect(ui->_exitPushBtn_, &QPushButton::clicked, this, &T3_AF_map::exitToMainWindow);
    connect(_qnode, &rosgui::QNode::poseUpdated, this, &T3_AF_map::getPoint);
    connect(_qnode, &rosgui::QNode::globalPlanGet, this, &T3_AF_map::routeUpdate);
    connect(ui->_clear, &QPushButton::clicked, this, &T3_AF_map::pathClear);
    //connect(ui->_update, &QPushButton::clicked, this, &T3_AF_map::getPoint);
    connect(ui->_modePushBtn_, SIGNAL(clicked(bool)), this, SLOT(autoMode()));
    connect(ui->_stopPushBtn_, &QPushButton::clicked, this, &T3_AF_map::stopRobot);
    //视频展示
     _netWork = T3_Face_Network::getT3FaceNetwork();
     _decoder = _netWork->_decoder_;

     if(_netWork->_isNetworkConnected_)
     {
       _netWork->getVideo();
     }else
     {
            //T3_AF_warning *warning = new T3_AF_warning(this,"网络未连接");
            //warning->show();
        ui->_videoLabel_->setText("网络未连接，请检查网络");
     }

     _frameLineData = _netWork->_frameLineData_;
     connect(_decoder,&Decoder::newFrame,this,&T3_AF_map::printVideo);
     connect(_netWork,&T3_Face_Network::networkDisconnect,this,&T3_AF_map::networkDisconnected);
     //数据库连接
     _database = QSqlDatabase::addDatabase(kDatabaseEngine);
     _database.setDatabaseName(kDatabaseName);
     _database.setHostName(kServerURL);
     _database.setUserName(kDatabaseUserName);
     _database.setPassword(kDatabasePassword);
     _database.open();

    connect(_stopPushBtn_, &QPushButton::clicked, this, &T3_AF_map::manualCmd);
    connect(_forwardPusbBtn_, &QPushButton::clicked, this, &T3_AF_map::manualCmd);
    connect(_backwordPushBtn_, &QPushButton::clicked, this, &T3_AF_map::manualCmd);
    connect(_leftTurnPushBtn_, &QPushButton::clicked, this, &T3_AF_map::manualCmd);
    connect(_rightTurnPushBtn_, &QPushButton::clicked, this, &T3_AF_map::manualCmd);
    connect(_backToOrigin_, &QPushButton::clicked, this, &T3_AF_map::backToOrigin);
    //日志
    T3LOG("7+ 导航界面构造");
}


void T3_AF_map::battery()
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

void T3_AF_map::backToOrigin()
{
    _qnode->goalUpdate(0.0, 0.0, 0.0);
}

void T3_AF_map::manualCmd()
{
    if(kForwardName == QObject::sender()->objectName())
    {
        _qnode->setManualCmd(rosgui::QNode::Forward);
//        qDebug() << "manualCmd - W";
    }
    else if(kBackwardName == QObject::sender()->objectName())
    {
        _qnode->setManualCmd(rosgui::QNode::Backward);
//        qDebug() << "manualCmd - B";
    }
    else if(kLeftTurnName == QObject::sender()->objectName())
    {
        _qnode->setManualCmd(rosgui::QNode::LeftTurn);
//        qDebug() << "manualCmd - L";
    }
    else if(kRighTurnName == QObject::sender()->objectName())
    {
        _qnode->setManualCmd(rosgui::QNode::RightTurn);
//        qDebug() << "manualCmd - R";
    }
    else
    {
        _qnode->setManualCmd(rosgui::QNode::Stop);
//        qDebug() << "manualCmd - S";
    }
}

void T3_AF_map::buttonStatus(bool status)
{
    _forwardPusbBtn_->setEnabled(status);
    _backwordPushBtn_->setEnabled(status);
    _leftTurnPushBtn_->setEnabled(status);
    _rightTurnPushBtn_->setEnabled(status);
    _stopPushBtn_->setEnabled(status);
    if(status == true)
    {
        _forwardPusbBtn_->setStyleSheet("QPushButton{border-image:url(:/Pictures/forward_true.png);}"
                                        "QPushButton:pressed{border-image:url(:/Pictures/forward_false.png);}");
        _backwordPushBtn_->setStyleSheet("QPushButton{border-image:url(:/Pictures/backward_true.png);}"
                                         "QPushButton:pressed{border-image:url(:/Pictures/backward_false.png);}");
        _leftTurnPushBtn_->setStyleSheet("QPushButton{border-image:url(:/Pictures/leftTurn_true.png);}"
                                         "QPushButton:pressed{border-image:url(:/Pictures/leftTurn_false.png);}");
        _rightTurnPushBtn_->setStyleSheet("QPushButton{border-image:url(:/Pictures/rightTurn_true.png);}"
                                          "QPushButton:pressed{border-image:url(:/Pictures/rightTurn_false.png);}");
        _stopPushBtn_->setStyleSheet("QPushButton{border-image:url(:/Pictures/stop_true.png);}"
                                     "QPushButton:pressed{border-image:url(:/Pictures/stop_false.png);}");
    }
    else
    {
        _forwardPusbBtn_->setStyleSheet("border-image:url(:/Pictures/forward_false.png)");
        _backwordPushBtn_->setStyleSheet("border-image:url(:/Pictures/backward_false.png)");
        _leftTurnPushBtn_->setStyleSheet("border-image:url(:/Pictures/leftTurn_false.png)");
        _rightTurnPushBtn_->setStyleSheet("border-image:url(:/Pictures/rightTurn_false.png)");
        _stopPushBtn_->setStyleSheet("border-image:url(:/Pictures/stop_false.png)");
    }
}

//test
void T3_AF_map::autoMode()
{
    _mode = _qnode->getOprationMode();
    if(_mode == rosgui::QNode::Manual)
    {
        ui->_modePushBtn_->setText("自动模式           ");
        ui->_modePushBtn_->setStyleSheet("border-image:url(:/Pictures/on.png);color:black");
        _qnode->setOperationMode(rosgui::QNode::Auto);
        buttonStatus(false);
    }
    else
    {
        ui->_modePushBtn_->setText("           手动模式");
        ui->_modePushBtn_->setStyleSheet("border-image:url(:/Pictures/off.png)");
        _qnode->setOperationMode(rosgui::QNode::Manual);
        buttonStatus(true);
    }
}

void T3_AF_map::stopRobot()
{
    _qnode->setOperationMode(rosgui::QNode::Manual);
    ui->_modePushBtn_->setText("           手动模式");
    ui->_modePushBtn_->setStyleSheet("border-image:url(:/Pictures/off.png)");
    _qnode->setOperationMode(rosgui::QNode::Manual);
    buttonStatus(true);
    _qnode->setManualCmd(rosgui::QNode::Stop);
}

//显示时间
void T3_AF_map::timeUpdate()
{
    QDateTime dateTime_ = QDateTime::currentDateTime();
    QString dateTimeStr_ = dateTime_.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->_dateTimeLabel_->setText(dateTimeStr_);
}

//界面背景绘制
void T3_AF_map::paintEvent(QPaintEvent *)
{
    QPainter paint_(this);
    paint_.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/Pictures/map_background.png"));
    paint_.drawPixmap(_mapStartX, _mapStartY, _mapWidth, _mapHeight, QPixmap(":/Pictures/map_realMap.pgm"));
    paint_.setRenderHint(QPainter::Antialiasing, true);
    paint_.setPen(QPen(Qt::red, 4));
    paint_.drawLine(_pos_[0], _pos_[1], _pos_[2], _pos_[3]);
    paint_.drawLine(_pos_[2], _pos_[3], _pos_[4], _pos_[5]);
    paint_.drawLine(_pos_[4], _pos_[5], _pos_[0], _pos_[1]);
    //route
    paint_.setPen(QPen(Qt::green, 3));
    if(_route.size() > 1)
    {
            for(int i = 0; i<_route.size()-1; i++)
        {
            paint_.drawLine(_route.at(i).first, _route.at(i).second, _route.at(i+1).first, _route.at(i+1).second);

        }
    }
    //path
    paint_.setPen(QPen(Qt::gray, 5));
    if(_pathX.size() > 1)
    {
            for(int i = 0; i<_pathX.size()-1; i++)
        {
            paint_.drawLine(_pathX.at(i), _pathY.at(i), _pathX.at(i+1), _pathY.at(i+1));
        }
    }
    //arrow
    paint_.setPen(QPen(Qt::green, 2));
    if((_startX > _mapStartX) & (_startY > _mapStartY) & (_moveX > 0) & (_moveY) > 0 & (_startX < (_mapStartX + _mapWidth)) & (_startY < (_mapStartY + _mapHeight)))
    {
//        paint_.drawLine(_startX, _startY, _moveX, _moveY);
//        paint_.drawLine(_startX, _startY, _arrow_[0], _arrow_[1]);
//        paint_.drawLine(_startX, _startY, _arrow_[2], _arrow_[3]);
        paint_.drawLine(_arrow_[0], _arrow_[1], _arrow_[2], _arrow_[3]);
        paint_.drawLine(_arrow_[2], _arrow_[3], _arrow_[4], _arrow_[5]);
        paint_.drawLine(_arrow_[4], _arrow_[5], _arrow_[0], _arrow_[1]);
    }
    showSpeed();
    battery();
}

void T3_AF_map::showSpeed()
{
    _qnode->getRobotSpeed(&_lineS, &_angleS);
    _lineSText = "线速度： " + QString::number(_lineS, 10, 2) + " m/s";
    _angleSText = "角速度： " + QString::number(_angleS, 10, 2) + " m/s";
    _lineSLabel_->setText(_lineSText);
    _angleSLabel_->setText(_angleSText);
    update();
}



void T3_AF_map::pathClear()
{
    _pathX.clear();
    _pathY.clear();
    _route.clear();
        _startX = 0;
        _startY = 0;
        _moveX = 0;
        _moveY = 0;
    update();
}

//mouseMoveEvent
void T3_AF_map::mouseMoveEvent(QMouseEvent *m)
{
    _moveX = m->x();
    _moveY = m->y();
    //_arrow_[0]~ax,[1]~ay,[2]~bx,[3]~by
//    float cArrow = 8.0;
//    float a = atan2(_startY - _moveY, _moveX - _startX);
//    float alfaArrow = kPi/6;
//    _arrow_[0] = _startX - cArrow * cos(a - alfaArrow);
//    _arrow_[1] = _startY + cArrow * sin(a - alfaArrow);
//    _arrow_[2] = _startX - cArrow * sin(kPi/2 - a - alfaArrow);
//    _arrow_[3] = _startY + cArrow * cos(kPi/2 - a - alfaArrow);
    float cShort = 3.0;
    float cLong = 10.0;
    float angle = atan2(_startY - _moveY, _moveX - _startX);
    //pose[0]~ax,[1]~ay,[2]~bx,[3]~by,[4]~cx,[5]~cy
    _arrow_[0] = _startX - cShort*sin(angle);
    _arrow_[1] = _startY - cShort*cos(angle);
    _arrow_[2] = _startX + cLong*cos(angle);
    _arrow_[3] = _startY - cLong*sin(angle);
    _arrow_[4] = _startX + cShort*sin(angle);
    _arrow_[5] = _startY + cShort*cos(angle);
    update();
}

//mousePressEvent
void T3_AF_map::mousePressEvent(QMouseEvent *p)
{
    _startX = p->x();
    _startY = p->y();
    update();
}

void T3_AF_map::mouseReleaseEvent(QMouseEvent *)
{
    getTarget();
//    _startX = 0;
//    _startY = 0;
//    _moveX = 0;
//    _moveY = 0;
    update();

}

void T3_AF_map::getTarget()
{
    if((_startX > _mapStartX) & (_startY > _mapStartY) & (_moveX > 0) & (_moveY) > 0 & (_startX < (_mapStartX + _mapWidth)) & (_startY < (_mapStartY + _mapHeight)))
    {
        float x = (_startX - _mapStartX)/_scale + _originX;
        float y = (_mapStartY + _mapHeight - _startY)/_scale + _originY;
        float a = atan2(_startY - _moveY, _moveX - _startX);
        _qnode->goalUpdate(x, y, a);
    }
}

//退出
void T3_AF_map::exitToMainWindow()
{
    if(_netWork->_isNetworkConnected_)
    {
      _netWork->closeVideo();
    }
    _mainWindow->show();

    this->close();
    delete this;
}

//getPoint
void T3_AF_map::getPoint()
{
    //test
//    _qnode->_robotPose[0] = ui->_x->text().toFloat();
//    _qnode->_robotPose[1] = ui->_y->text().toFloat();
//    _qnode->_robotPose[2] = ui->_a->text().toFloat();
//    _qnode->_robotPose[3] = 0;
    //test fin.
  _robotPose = _qnode->getRobotPose();
  _mapOrigin = _qnode->getMapOrigin();

//    qDebug() << "robotpose[0]:" << _robotPose[0] << "\n"
//             << "robotpose[1]:" << _robotPose[1] << "\n"
//             << "robotpose[2]:" << _robotPose[2] << "\n"
//             << "robotpose[3]:" << _robotPose[3];
    //---------jason code
    float x = _robotPose[0];
    float y = _robotPose[1];
    float z = _robotPose[2];
    float w = _robotPose[3];
    //temp...
    _originX = _mapOrigin[0];
    _originY = _mapOrigin[1];
    //---------jason end
    float px = _mapStartX + (x - _originX) * _scale;
    float py = _mapStartY + _mapHeight - (y - _originY)*_scale;
    _pathX.append(px);
    _pathY.append(py);
    float angle = atan2(2 * w * z, 1 - 2 * z * z);
    //test
//    angle = z;
    //test fin.
    float cShort = 3.0;
    float cLong = 10.0;
    //pose[0]~ax,[1]~ay,[2]~bx,[3]~by,[4]~cx,[5]~cy
    _pos_[0] = px - cShort*sin(angle);
    _pos_[1] = py - cShort*cos(angle);
    _pos_[2] = px + cLong*cos(angle);
    _pos_[3] = py - cLong*sin(angle);
    _pos_[4] = px + cShort*sin(angle);
    _pos_[5] = py + cShort*cos(angle);
//    qDebug() <<"angle:" << angle <<"\n"
//             <<"ax:" << _pos_[0] <<"\n"
//             <<"ay:" << _pos_[1] <<"\n"
//             <<"bx:" << _pos_[2] <<"\n"
//             <<"by:" << _pos_[3] <<"\n"
//             <<"cx:" << _pos_[4] <<"\n"
//             <<"cy:" << _pos_[5] <<"\n" <<"\n";
    _connect->stop();
    _connect->start(5000);
    ui->_showConnectStatus_->setText("        已连接");
    ui->_showConnectStatus_->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->_showConnectStatus_->setStyleSheet("border-image:url(:/Pictures/on.png);color:black");
    update();
}

void T3_AF_map::routeUpdate()
{
    _qnode->getGlobalPlan(_route);
    for(int idx = 0; idx < _route.size(); idx++)
    {
      _route[idx].first = (_route[idx].first - _originX) * _scale + _mapStartX;
      _route[idx].second = _mapStartY + _mapHeight - (_route[idx].second - _originY)* _scale;
    }
    update();
}

void T3_AF_map::closeEvent(QCloseEvent *event)
{
    event->ignore();
}


//press
void T3_AF_map::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        break;
    case Qt::Key_W:
        if(_forwardPusbBtn_->isEnabled())
        {
            _forwardPusbBtn_->setStyleSheet("border-image:url(:/Pictures/forward_false.png)");
        }
        break;
    case Qt::Key_X:
        if(_backwordPushBtn_->isEnabled())
        {
            _backwordPushBtn_->setStyleSheet("border-image:url(:/Pictures/backward_false.png)");
        }
        break;
    case Qt::Key_A:
        if(_leftTurnPushBtn_->isEnabled())
        {
            _leftTurnPushBtn_->setStyleSheet("border-image:url(:/Pictures/leftTurn_false.png)");
        }
        break;
    case Qt::Key_S:
        if(_stopPushBtn_->isEnabled())
        {
            _stopPushBtn_->setStyleSheet("border-image:url(:/Pictures/stop_false.png)");
        }
        break;
    case Qt::Key_D:
        if(_rightTurnPushBtn_->isEnabled())
        {
            _rightTurnPushBtn_->setStyleSheet("border-image:url(:/Pictures/rightTurn_false.png)");
        }
        break;
    case Qt::Key_Up:
        if(_forwardPusbBtn_->isEnabled())
        {
            _forwardPusbBtn_->setStyleSheet("border-image:url(:/Pictures/forward_false.png)");
        }
        break;
    case Qt::Key_Down:
        if(_backwordPushBtn_->isEnabled())
        {
            _backwordPushBtn_->setStyleSheet("border-image:url(:/Pictures/backward_false.png)");
        }
        break;
    case Qt::Key_Left:
        if(_leftTurnPushBtn_->isEnabled())
        {
            _leftTurnPushBtn_->setStyleSheet("border-image:url(:/Pictures/leftTurn_false.png)");
        }
        break;
    case Qt::Key_Space:
        if(_stopPushBtn_->isEnabled())
        {
            _stopPushBtn_->setStyleSheet("border-image:url(:/Pictures/stop_false.png)");
        }
        break;
    case Qt::Key_Right:
        if(_rightTurnPushBtn_->isEnabled())
        {
            _rightTurnPushBtn_->setStyleSheet("border-image:url(:/Pictures/rightTurn_false.png)");
        }
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}

void T3_AF_map::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_W:
        if(_forwardPusbBtn_->isEnabled() && (!event->isAutoRepeat()))
        {
            _forwardPusbBtn_->clicked();
            _forwardPusbBtn_->setStyleSheet("QPushButton{border-image:url(:/Pictures/forward_true.png);}"
                                            "QPushButton:pressed{border-image:url(:/Pictures/forward_false.png);}");
            qDebug() << "W";
        }
        break;
    case Qt::Key_X:
        if(_backwordPushBtn_->isEnabled() && (!event->isAutoRepeat()))
        {
            _backwordPushBtn_->clicked();
            _backwordPushBtn_->setStyleSheet("QPushButton{border-image:url(:/Pictures/backward_true.png);}"
                                            "QPushButton:pressed{border-image:url(:/Pictures/backward_false.png);}");
            qDebug() << "B";
        }
        break;
    case Qt::Key_A:
        if(_leftTurnPushBtn_->isEnabled() && (!event->isAutoRepeat()))
        {
            _leftTurnPushBtn_->clicked();
            _leftTurnPushBtn_->setStyleSheet("QPushButton{border-image:url(:/Pictures/leftTurn_true.png);}"
                                            "QPushButton:pressed{border-image:url(:/Pictures/leftTurn_false.png);}");
            qDebug() << "L";
        }
        break;
    case Qt::Key_S:
        if(_stopPushBtn_->isEnabled() && (!event->isAutoRepeat()))
        {
            _stopPushBtn_->clicked();
            _stopPushBtn_->setStyleSheet("QPushButton{border-image:url(:/Pictures/stop_true.png);}"
                                            "QPushButton:pressed{border-image:url(:/Pictures/stop_false.png);}");
            qDebug() << "S";
        }
        break;
    case Qt::Key_D:
        if(_rightTurnPushBtn_->isEnabled() && (!event->isAutoRepeat()))
        {
            _rightTurnPushBtn_->clicked();
            _rightTurnPushBtn_->setStyleSheet("QPushButton{border-image:url(:/Pictures/rightTurn_true.png);}"
                                            "QPushButton:pressed{border-image:url(:/Pictures/rightTurn_false.png);}");
            qDebug() << "R";
        }
        break;
    case Qt::Key_Up:
        if(_forwardPusbBtn_->isEnabled() && (!event->isAutoRepeat()))
        {
            _forwardPusbBtn_->clicked();
            _forwardPusbBtn_->setStyleSheet("QPushButton{border-image:url(:/Pictures/forward_true.png);}"
                                            "QPushButton:pressed{border-image:url(:/Pictures/forward_false.png);}");
            qDebug() << "W";
        }
        break;
    case Qt::Key_Down:
        if(_backwordPushBtn_->isEnabled() && (!event->isAutoRepeat()))
        {
            _backwordPushBtn_->clicked();
            _backwordPushBtn_->setStyleSheet("QPushButton{border-image:url(:/Pictures/backward_true.png);}"
                                            "QPushButton:pressed{border-image:url(:/Pictures/backward_false.png);}");
            qDebug() << "B";
        }
        break;
    case Qt::Key_Left:
        if(_leftTurnPushBtn_->isEnabled() && (!event->isAutoRepeat()))
        {
            _leftTurnPushBtn_->clicked();
            _leftTurnPushBtn_->setStyleSheet("QPushButton{border-image:url(:/Pictures/leftTurn_true.png);}"
                                            "QPushButton:pressed{border-image:url(:/Pictures/leftTurn_false.png);}");
            qDebug() << "L";
        }
        break;
    case Qt::Key_Space:
        if(_stopPushBtn_->isEnabled() && (!event->isAutoRepeat()))
        {
            _stopPushBtn_->clicked();
            _stopPushBtn_->setStyleSheet("QPushButton{border-image:url(:/Pictures/stop_true.png);}"
                                            "QPushButton:pressed{border-image:url(:/Pictures/stop_false.png);}");
            qDebug() << "S";
        }
        break;
    case Qt::Key_Right:
        if(_rightTurnPushBtn_->isEnabled() && (!event->isAutoRepeat()))
        {
            _rightTurnPushBtn_->clicked();
            _rightTurnPushBtn_->setStyleSheet("QPushButton{border-image:url(:/Pictures/rightTurn_true.png);}"
                                            "QPushButton:pressed{border-image:url(:/Pictures/rightTurn_false.png);}");
            qDebug() << "R";
        }
        break;
    default:
        QDialog::keyReleaseEvent(event);
    }
}



void T3_AF_map::printVideo(QImage faceImage)
{
  //faceImage = faceImage.mirrored(true,false);
  QPainter paint(&faceImage);
  QPen pen(Qt::yellow,2);
  paint.setPen(pen);
  paint.setFont(QFont(QString::fromLocal8Bit("宋体"),20,-1,false));
  //qDebug() << _frameLineData->personNum;
 for(int i = 0; i<_frameLineData->personNum; i++)
 {

     paint.drawLine(QPoint(_frameLineData->rightList[i],_frameLineData->topList[i]),QPoint(_frameLineData->leftList[i],_frameLineData->topList[i]));
     paint.drawLine(QPoint(_frameLineData->rightList[i],_frameLineData->bottomList[i]),QPoint(_frameLineData->leftList[i],_frameLineData->bottomList[i]));
     paint.drawLine(QPoint(_frameLineData->rightList[i],_frameLineData->topList[i]),QPoint(_frameLineData->rightList[i],_frameLineData->bottomList[i]));
     paint.drawLine(QPoint(_frameLineData->leftList[i],_frameLineData->topList[i]),QPoint(_frameLineData->leftList[i],_frameLineData->bottomList[i]));
     if(-1 != _frameLineData->idList[i])
     {
         QSqlQuery query_(_database);
         query_.prepare("select name from T3Face where id = ?");
         query_.bindValue(0, _frameLineData->idList[i]);

         query_.exec();
         query_.next();
         QString name_ = query_.value(0).toString();
         paint.drawText(QPointF(_frameLineData->dot2List[i]-1,_frameLineData->dot1List[i]),name_);
     }

 }

  paint.end();
  ui->_videoLabel_->setPixmap(QPixmap::fromImage(faceImage));
}


void T3_AF_map::ifConnected()
{
    ui->_showConnectStatus_->setText("未连接        ");
    ui->_showConnectStatus_->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->_showConnectStatus_->setStyleSheet("border-image:url(:/Pictures/off.png)");
}

void T3_AF_map::sleepBtn(int delayTime)
{
    QTime dead_ = QTime::currentTime().addMSecs(delayTime);
    while(QTime::currentTime() < dead_)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void T3_AF_map::networkDisconnected()
{
  ui->_videoLabel_->clear();
  ui->_videoLabel_->setText("网络连接断开，请检查网络");
}

//界面析构函数
T3_AF_map::~T3_AF_map()
{
    delete ui;
    delete _forwardPusbBtn_;
    delete _backwordPushBtn_;
    delete _leftTurnPushBtn_;
    delete _rightTurnPushBtn_;
    delete _stopPushBtn_;
    delete _backToOrigin_;
    delete _lineSLabel_;
    delete _angleSLabel_;
    //日志
    T3LOG("7- 导航界面析构");
}
