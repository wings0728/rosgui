#include "../../include/rosgui/qt/t3_af_maponly.hpp"
#include "ui_t3_af_maponly.h"

T3_AF_mapOnly::T3_AF_mapOnly(T3_AF_map *map, QWidget *parent) :
    T3Dialog(parent),
    _pos_(6, -3.0),
    _arrow_(6, 0.0),
    _robotPose(4, 0.0),
    _mapOrigin(3, 0.0),
    _map(map),
    ui(new Ui::T3_AF_mapOnly)
{
    //father
    _father = new T3Dialog;
    //basic settings
    ui->setupUi(this);
    this->setGeometry(0, 0, _father->_width_, _father->_height_);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->showFullScreen();
    //ui
    ui->_dateTimeLabel_->setText("");
    ui->_dateTimeLabel_->setStyleSheet("color:rgb(7, 221, 225)");
    ui->_dateTimeLabel_->setGeometry(this->width()*0.6450,
                                     this->height()*0.9333,
                                     this->width()*0.1620,
                                     this->height()*0.034);
    ui->_battGIF_->setGeometry(this->width()*0.5100,
                               this->height()*0.9403,
                               this->width()*0.1188,
                               this->height()*0.027);
    ui->_battery_->setGeometry(this->width()*0.636,
                               this->height()*0.93,
                               this->width()*0.0438,
                               this->height()*0.034);
    ui->_battIMG_->setGeometry(this->width()*0.5100,
                               this->height()*0.9403,
                               this->width()*0.1188,
                               this->height()*0.027);
    QFont dateTimaLabelFont_;
    dateTimaLabelFont_.setPointSize(ui->_dateTimeLabel_->height() * kLabelFontScal * 0.75);
    ui->_dateTimeLabel_->setFont(dateTimaLabelFont_);
    QFont battFont_;
    battFont_.setPointSize(ui->_battery_->height() * kLabelFontScal * 0.75);
    ui->_battery_->setFont(battFont_);
    //date/time update timer
    QTimer *timer_ = new QTimer(this);
    timer_->start(100);
    //low batt GIF
    QMovie *battLow_ = new QMovie(":/Pictures/batt_4.gif");
    battLow_->setScaledSize(QSize(ui->_battGIF_->width(), ui->_battGIF_->height()));
    battLow_->setSpeed(130);
    ui->_battGIF_->setMovie(battLow_);
    battLow_->start();
    _qnode = rosgui::QNode::getInstance();
    //func
    connect(timer_, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    connect(_map, SIGNAL(offline()), this, SLOT(exitUI()));
    connect(_qnode, &rosgui::QNode::poseUpdated, this, &T3_AF_mapOnly::posUpdate);
    routeUpdate();
    connect(_qnode, &rosgui::QNode::globalPlanGet, this, &T3_AF_mapOnly::routeUpdate);
    //initialization
    _battInt = 0;
    _battQString = "";
    _mapIMG.load(":/Pictures/map_realMap.pgm");
    _mapWidthReal = ((float)(_mapIMG.width()))/20.0;
    _mapHeightReal = ((float)(_mapIMG.height()))/20.0;
    _Hcenter = this->width() * 0.5;
    _Vcenter = this->height() * 0.5;
    getMapGeometry();
    arrowUpdate();
    _originX = 0.0;
    _originY = 0.0;
    //LOG
    T3LOG("** mapOnly created");
    clearPath();
}

void T3_AF_mapOnly::exitUI()
{
    _map->show();
    this->hide();
    delete this;
}

void T3_AF_mapOnly::clearPath()
{
    if(true == _map->ifClear)
    {
        _pos_[0] = -3.0;
        _pos_[1] = -3.0;
        _pos_[2] = -3.0;
        _pos_[3] = -3.0;
        _pos_[4] = -3.0;
        _pos_[5] = -3.0;
        _arrow_[0] = 0.0;
        _arrow_[1] = 0.0;
        _arrow_[2] = 0.0;
        _arrow_[3] = 0.0;
        _arrow_[4] = 0.0;
        _arrow_[5] = 0.0;
        _pathX.clear();
        _pathY.clear();
        _route.clear();
        _map->ifClear = false;
    }
}

///
/// \brief T3_AF_mapOnly::getMapGeometry --> get map x/y/width/height
///
void T3_AF_mapOnly::getMapGeometry()
{
    if(((this->width()) * 0.9 / _mapWidthReal) >= ((this->height() * 0.84) / _mapHeightReal))
    {
        _mapHeight = this->height() * 0.84;
        _scale = _mapHeight / _mapHeightReal;
        _mapWidth = _scale * _mapWidthReal;
        _mapX = _Hcenter - (_mapWidth / 2);
        _mapY = _Vcenter - (_mapHeight / 2);
    }
    else
    {
        _mapWidth = this->width() * 0.9;
        _scale = _mapWidth / _mapWidthReal;
        _mapHeight = _scale * _mapHeightReal;
        _mapX = _Vcenter - (_mapWidth / 2);
        _mapY = _Hcenter - (_mapHeight / 2);
    }
}

///
/// \brief T3_AF_mapOnly::battery --> show batt status
///
void T3_AF_mapOnly::battery()
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

///
/// \brief T3_AF_mapOnly::timeUpdate --> show time/date info
///
void T3_AF_mapOnly::timeUpdate()
{
    QDateTime dateTime_ = QDateTime::currentDateTime();
    QString dateTimeStr_ = dateTime_.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->_dateTimeLabel_->setText(dateTimeStr_);
}

void T3_AF_mapOnly::paintEvent(QPaintEvent *)
{
    QPainter paint_(this);
    paint_.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/Pictures/map_background.png"));
    paint_.drawPixmap(_mapX, _mapY, _mapWidth, _mapHeight, QPixmap(":/Pictures/map_realMap.pgm"));
    paint_.setRenderHint(QPainter::Antialiasing, true);
    //current position
    paint_.setPen(QPen(Qt::red, 6));
    paint_.drawLine(_pos_[0], _pos_[1], _pos_[2], _pos_[3]);
    paint_.drawLine(_pos_[2], _pos_[3], _pos_[4], _pos_[5]);
    paint_.drawLine(_pos_[4], _pos_[5], _pos_[0], _pos_[1]);
    //path
    paint_.setPen(QPen(Qt::gray, 6));
    if(_pathX.size() > 1)
    {
            for(int i = 0; i<_pathX.size()-1; i++)
        {
            paint_.drawLine(_pathX.at(i), _pathY.at(i), _pathX.at(i+1), _pathY.at(i+1));
        }
    }
    //arrow
    paint_.setPen(QPen(Qt::white, 2));
    if((_arrow_[0] > 0) && (_arrow_[1] > 0) && (_arrow_[2] > 0) && (_arrow_[3] > 0) && (_arrow_[4] > 0) && (_arrow_[5] > 0))
    {
        paint_.drawLine(_arrow_[0], _arrow_[1], _arrow_[2], _arrow_[3]);
        paint_.drawLine(_arrow_[2], _arrow_[3], _arrow_[4], _arrow_[5]);
        paint_.drawLine(_arrow_[4], _arrow_[5], _arrow_[0], _arrow_[1]);
    }

    //route
    paint_.setPen(QPen(Qt::white, 4));
    if(_route.size() > 1)
    {
            for(int i = 0; i<_route.size()-1; i++)
        {
            paint_.drawLine(_route.at(i).first, _route.at(i).second, _route.at(i+1).first, _route.at(i+1).second);

        }
    }
    //batt
    battery();
}

//weiceshi
void T3_AF_mapOnly::posUpdate()
{
    _robotPose = _qnode->getRobotPose();
    _mapOrigin = _qnode->getMapOrigin();
    float x = _robotPose[0];
    float y = _robotPose[1];
    float z = _robotPose[2];
    float w = _robotPose[3];
    _originX = _mapOrigin[0];
    _originY = _mapOrigin[1];
    float px = _mapX + (x - _originX) * _scale;
    float py = _mapY + _mapHeight - (y - _originY) * _scale;
    _pathX.append(px);
    _pathY.append(py);
    float angle = atan2(2 * w * z, 1 - 2 * z * z);
    float cShort = 4.5;
    float cLong = 15.0;
    _pos_[0] = px - cShort*sin(angle);
    _pos_[1] = py - cShort*cos(angle);
    _pos_[2] = px + cLong*cos(angle);
    _pos_[3] = py - cLong*sin(angle);
    _pos_[4] = px + cShort*sin(angle);
    _pos_[5] = py + cShort*cos(angle);
    update();
}

//weiceshi
void T3_AF_mapOnly::arrowUpdate()
{
    if((_map->x > 0.001) && (_map->y > 0.001))
    {
        float ax = _mapX + (_map->x - _originX) * _scale;
        float ay = _mapY + _mapHeight - (_map->y - _originY) * _scale;
        float aShort = 4.5;
        float aLong = 15.0;
        _arrow_[0] = ax - aShort*sin(_map->a);
        _arrow_[1] = ay - aShort*cos(_map->a);
        _arrow_[2] = ax + aLong*cos(_map->a);
        _arrow_[3] = ay - aLong*sin(_map->a);
        _arrow_[4] = ax + aShort*sin(_map->a);
        _arrow_[5] = ay + aShort*cos(_map->a);
        update();
    }
}

//weiceshi
void T3_AF_mapOnly::routeUpdate()
{
    _qnode->getGlobalPlan(_route);
    for(int idx = 0; idx < _route.size(); idx++)
    {
      _route[idx].first = (_route[idx].first - _originX) * _scale + _mapX;
      _route[idx].second = _mapY + _mapHeight - (_route[idx].second - _originY)* _scale;
    }
    update();
}

void T3_AF_mapOnly::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        exit();
        break;
    default:
        QDialog::keyReleaseEvent(event);
    }
}

void T3_AF_mapOnly::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_W:
        if((rosgui::QNode::Manual == _qnode->getOprationMode()) && (!event->isAutoRepeat()))
        {_qnode->setManualCmd(rosgui::QNode::Forward);}
        break;
    case Qt::Key_S:
        if((rosgui::QNode::Manual == _qnode->getOprationMode()) && (!event->isAutoRepeat()))
        {_qnode->setManualCmd(rosgui::QNode::Stop);}
        break;
    case Qt::Key_X:
        if((rosgui::QNode::Manual == _qnode->getOprationMode()) && (!event->isAutoRepeat()))
        {_qnode->setManualCmd(rosgui::QNode::Backward);}
        break;
    case Qt::Key_A:
        if((rosgui::QNode::Manual == _qnode->getOprationMode()) && (!event->isAutoRepeat()))
        {
            _qnode->setManualCmd(rosgui::QNode::LeftTurn);
        }
        break;
    case Qt::Key_D:
        if((rosgui::QNode::Manual == _qnode->getOprationMode()) && (!event->isAutoRepeat()))
        {_qnode->setManualCmd(rosgui::QNode::RightTurn);}
        break;
    case Qt::Key_Up:
        if((rosgui::QNode::Manual == _qnode->getOprationMode()) && (!event->isAutoRepeat()))
        {_qnode->setManualCmd(rosgui::QNode::Forward);}
        break;
    case Qt::Key_Space:
        if((rosgui::QNode::Manual == _qnode->getOprationMode()) && (!event->isAutoRepeat()))
        {_qnode->setManualCmd(rosgui::QNode::Stop);}
        break;
    case Qt::Key_Down:
        if((rosgui::QNode::Manual == _qnode->getOprationMode()) && (!event->isAutoRepeat()))
        {_qnode->setManualCmd(rosgui::QNode::Backward);}
        break;
    case Qt::Key_Left:
        if((rosgui::QNode::Manual == _qnode->getOprationMode()) && (!event->isAutoRepeat()))
        {_qnode->setManualCmd(rosgui::QNode::LeftTurn);}
        break;
    case Qt::Key_Right:
        if((rosgui::QNode::Manual == _qnode->getOprationMode()) && (!event->isAutoRepeat()))
        {_qnode->setManualCmd(rosgui::QNode::RightTurn);}
        break;
    default:
        QDialog::keyReleaseEvent(event);
    }
}

void T3_AF_mapOnly::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

void T3_AF_mapOnly::exit()
{
    _map->show();
    this->hide();
    delete this;
}

T3_AF_mapOnly::~T3_AF_mapOnly()
{
    delete ui;
    //log
    T3LOG("** mapOnly deleted");
}
