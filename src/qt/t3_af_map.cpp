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
    //
    ui->_exitPushBtn_->setText("");
    ui->_exitPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_exitPushBtn_->setStyleSheet("border-image:url(:/Pictures/map_back.png)");
    ui->_dateTimeLabel_->setText("");
    ui->_dateTimeLabel_->setStyleSheet("color:rgb(7, 221, 225)");
    ui->_showConnectStatus_->setText("未连接");
    ui->_modePushBtn_->setText("自动模式");
    ui->_modePushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_modePushBtn_->setCheckable(true);
    ui->_clear->setFocusPolicy(Qt::NoFocus);
    //size
    ui->_modePushBtn_->setGeometry(this->width()*0.75,
                                     this->height()*0.0889,
                                     this->width()*0.0675,
                                     this->height()*0.0400);
    ui->_clear->setGeometry(this->width()*0.8625,
                            this->height()*0.8111,
                            this->width()*0.1000,
                            this->height()*0.0578);
    ui->_dateTimeLabel_->setGeometry(this->width()*0.6500,
                                     this->height()*0.9333,
                                     this->width()*0.1620,
                                     this->height()*0.034);
    ui->_exitPushBtn_->setGeometry(this->width()*0.9313,
                                   this->height()*0.0178,
                                   this->width()*0.0375,
                                   this->height()*0.0600);
    ui->_showConnectStatus_->setGeometry(this->width()*0.6125,
                                         this->height()*0.0889,
                                         this->width()*0.0675,
                                         this->height()*0.0400);
    ui->_videoLabel_->setGeometry(this->width()*0.6250,
                                  this->height()*0.1600,
                                  this->width()*0.3250,
                                  this->width()*0.2438);
    _forwardPusbBtn_->setGeometry(this->width()*0.715,
                                  this->height()*0.6,
                                  this->width()*0.07,
                                  this->height()*0.05);
    _backwordPushBtn_->setGeometry(this->width()*0.715,
                                   this->height()*0.8,
                                   this->width()*0.07,
                                   this->height()*0.05);
    _leftTurnPushBtn_->setGeometry(this->width()*0.625,
                                   this->height()*0.7,
                                   this->width()*0.07,
                                   this->height()*0.05);
    _rightTurnPushBtn_->setGeometry(this->width()*0.805,
                                     this->height()*0.7,
                                     this->width()*0.07,
                                     this->height()*0.05);
    _stopPushBtn_->setGeometry(this->width()*0.715,
                               this->height()*0.7,
                               this->width()*0.07,
                               this->height()*0.05);

    _forwardPusbBtn_->show();
    _backwordPushBtn_->show();
    _leftTurnPushBtn_->show();
    _rightTurnPushBtn_->show();
    _stopPushBtn_->show();
    //font
    QFont showConnectStatusFont_;
    showConnectStatusFont_.setPointSize(ui->_showConnectStatus_->height() * kLabelFontScal);
    QFont modePushBtnFont_;
    modePushBtnFont_.setPointSize(ui->_modePushBtn_->height() * kBtnFontScal);
    QFont clearFont_;
    clearFont_.setPointSize(ui->_clear->height() * kBtnFontScal);
    QFont dateTimaLabelFont_;
    dateTimaLabelFont_.setPointSize(ui->_dateTimeLabel_->height() * kLabelFontScal * 0.75);
    ui->_showConnectStatus_->setFont(showConnectStatusFont_);
    ui->_modePushBtn_->setFont(modePushBtnFont_);
    ui->_clear->setFont(clearFont_);
    ui->_dateTimeLabel_->setFont(dateTimaLabelFont_);
    //
    _qnode = rosgui::QNode::getInstance();
    _mapStartX = this->width()*0.0313;
    _mapStartY = this->height()*0.0800;
    QImage realMap_;
    realMap_.load(":/Pictures/map_realMap.pgm");
    _realWidth = realMap_.width();
    _realHeight = realMap_.height();
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
    _mode = _qnode->getOprationMode();
    if(_mode = rosgui::QNode::Manual)
    {
        ui->_modePushBtn_->setText("手动模式");
    }
    else
    {
        ui->_modePushBtn_->setText("自动模式");
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
    //链接ui部件与功能
    connect(timer_, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    connect(ui->_exitPushBtn_, &QPushButton::clicked, this, &T3_AF_map::exitToMainWindow);
    connect(_qnode, &rosgui::QNode::poseUpdated, this, &T3_AF_map::getPoint);
    connect(_qnode, &rosgui::QNode::globalPlanGet, this, &T3_AF_map::routeUpdate);
    connect(ui->_clear, &QPushButton::clicked, this, &T3_AF_map::pathClear);
    //connect(ui->_update, &QPushButton::clicked, this, &T3_AF_map::getPoint);
    connect(ui->_modePushBtn_, SIGNAL(clicked(bool)), this, SLOT(autoMode()));
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
     }

     _frameLineData = _netWork->_frameLineData_;
     connect(_decoder,&Decoder::newFrame,this,&T3_AF_map::printVideo);
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

    //日志
    T3LOG("7+ 导航界面构造");
}

void T3_AF_map::manualCmd()
{
    if(kForwardName == QObject::sender()->objectName())
    {
        _qnode->setManualCmd(rosgui::QNode::Forward);
    }
    else if(kBackwardName == QObject::sender()->objectName())
    {
        _qnode->setManualCmd(rosgui::QNode::Backward);
    }
    else if(kLeftTurnName == QObject::sender()->objectName())
    {
        _qnode->setManualCmd(rosgui::QNode::LeftTurn);
    }
    else if(kRighTurnName == QObject::sender()->objectName())
    {
        _qnode->setManualCmd(rosgui::QNode::RightTurn);
    }
    else
    {
        _qnode->setManualCmd(rosgui::QNode::Stop);
    }
}

//test
void T3_AF_map::autoMode()
{
    if(_mode = rosgui::QNode::Manual)
    {
        if(ui->_modePushBtn_->isChecked())
        {
            ui->_modePushBtn_->setText("自动模式");
            _qnode->setOperationMode(rosgui::QNode::Auto);
        }
        else
        {
            ui->_modePushBtn_->setText("手动模式");
            _qnode->setOperationMode(rosgui::QNode::Manual);
        }
    }
    else
    {
        if(ui->_modePushBtn_->isChecked())
        {
            ui->_modePushBtn_->setText("手动模式");
            _qnode->setOperationMode(rosgui::QNode::Manual);
        }
        else
        {
            ui->_modePushBtn_->setText("自动模式");
            _qnode->setOperationMode(rosgui::QNode::Auto);
        }
    }
    //_qnode->operationMode(mode);
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
    //path fin
    paint_.setPen(QPen(Qt::green, 2));
    if((_startX > 0) & (_startY > 0) & (_moveX > 0) & (_moveY) > 0)
    {
        paint_.drawLine(_startX, _startY, _moveX, _moveY);
        paint_.drawLine(_moveX, _moveY, _arrow_[0], _arrow_[1]);
        paint_.drawLine(_moveX, _moveY, _arrow_[2], _arrow_[3]);
    }
}

void T3_AF_map::pathClear()
{
    _pathX.clear();
    _pathY.clear();
    _route.clear();
    update();
}

//mouseMoveEvent
void T3_AF_map::mouseMoveEvent(QMouseEvent *m)
{
    _moveX = m->x();
    _moveY = m->y();
    //_arrow_[0]~ax,[1]~ay,[2]~bx,[3]~by
    float cArrow = 8.0;
    float a = atan2(_startY - _moveY, _moveX - _startX);
    float alfaArrow = kPi/6;
    _arrow_[0] = _moveX - cArrow * cos(a - alfaArrow);
    _arrow_[1] = _moveY + cArrow * sin(a - alfaArrow);
    _arrow_[2] = _moveX - cArrow * sin(kPi/2 - a - alfaArrow);
    _arrow_[3] = _moveY + cArrow * cos(kPi/2 - a - alfaArrow);
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
    _startX = 0;
    _startY = 0;
    _moveX = 0;
    _moveY = 0;
    update();

}

void T3_AF_map::getTarget()
{
    if((_moveX > 0) & (_moveY > 0))
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

    for(int idx = 0; idx < kDelay; idx++){}

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
    ui->_showConnectStatus_->setText("连接");
    update();
}

void T3_AF_map::routeUpdate()
{
    _qnode->getGlobalPlan(_route);
    for(int idx = 0; idx < _route.size(); idx++)
    {
      _route[idx].first = (_route[idx].first - _originX) * _scale + _mapStartX;
      _route[idx].second = _mapStartY + _mapHeight - (_route[idx].second - _originY)* _scale;
      qDebug() << "route[" << idx << "]" << _route[idx].first << _route[idx].second;
    }

    update();
}

void T3_AF_map::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

void T3_AF_map::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        break;
    default:
        QDialog::keyPressEvent(event);
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

//界面析构函数
T3_AF_map::~T3_AF_map()
{
    delete ui;
    delete _forwardPusbBtn_;
    delete _backwordPushBtn_;
    delete _leftTurnPushBtn_;
    delete _rightTurnPushBtn_;
    delete _stopPushBtn_;
    //日志
    T3LOG("7- 导航界面析构");
}
