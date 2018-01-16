#include "../../include/rosgui/qt/t3_af_map.hpp"
#include "ui_t3_af_map.h"


//界面构造函数
T3_AF_map::T3_AF_map(QDialog *mainWindow, QWidget *parent) :
    QDialog(parent),
    _mainWindow(mainWindow),
    ui(new Ui::T3_AF_map),
    _pos_(6, 0.0)
{
    //界面布局初始化
    ui->setupUi(this);
    this->move(0, 0);
    this->resize(800, 450);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    ui->_exitPushBtn_->setText("");
    ui->_exitPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_exitPushBtn_->setStyleSheet("border-image:url(:/Pictures/map_back.png)");
    ui->_dateTimeLabel_->setText("");
    ui->_dateTimeLabel_->setStyleSheet("color:rgb(7, 221, 225)");
    _qnode = rosgui::QNode::getInstance();
    _mapStartX = 25.0;
    _mapStartY = 35.0;
    _mapWidth = 360.0;
    _mapHeight = 360.0;
    _scale = kMapScal;
    //界面浮现动画
    QPropertyAnimation *animation_ = new QPropertyAnimation(this, "windowOpacity");
    animation_->setDuration(300);
    animation_->setStartValue(0);
    animation_->setEndValue(1);
    animation_->start();
    //定时器
    QTimer *timer_ = new QTimer(this);
    timer_->start(200);
    //链接ui部件与功能
    connect(timer_, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    connect(ui->_exitPushBtn_, &QPushButton::clicked, this, &T3_AF_map::exitToMainWindow);
    connect(_qnode, &rosgui::QNode::poseUpdated, this, &T3_AF_map::getPoint);
    //connect(ui->_testPushBtn_, &QPushButton::clicked, this, &T3_AF_map::getPoint);
    //日志
    T3LOG("7+ 导航界面构造");

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
    paint_.setPen(QPen(Qt::blue, 4));
    paint_.drawLine(_pos_[0], _pos_[1], _pos_[2], _pos_[3]);
    paint_.drawLine(_pos_[2], _pos_[3], _pos_[4], _pos_[5]);
    paint_.drawLine(_pos_[4], _pos_[5], _pos_[0], _pos_[1]);
}

//退出
void T3_AF_map::exitToMainWindow()
{
    _mainWindow->show();
    this->close();
    delete this;
}

//getPoint
void T3_AF_map::getPoint()
{
    qDebug() << "robotpose[0]:" << _qnode->_robotPose[0] << "\n"
             << "robotpose[1]:" << _qnode->_robotPose[1] << "\n"
             << "robotpose[2]:" << _qnode->_robotPose[2] << "\n"
             << "robotpose[3]:" << _qnode->_robotPose[3];
    //---------jason code
    float z = _qnode->_robotPose[2];
    float w = _qnode->_robotPose[3];
    //---------jason end
    float angle = atan2(2 * w * z, 1 - 2 * z * z);
    float a = 3.0;
    float b = 10.0;
    //pose[0]~ax,[1]~ay,[2]~bx,[3]~by,[4]~cx,[5]~cy
    _pos_[0] = (_mapStartX+_qnode->_robotPose[1]*_scale)-a*cos(angle);
    _pos_[1] = (_mapStartY+_mapHeight-_qnode->_robotPose[0]*_scale)+a*sin(angle);
    _pos_[2] = (_mapStartX+_qnode->_robotPose[1]*_scale)-b*sin(angle);
    _pos_[3] = (_mapStartY+_mapHeight-_qnode->_robotPose[0]*_scale)-b*cos(angle);
    _pos_[4] = (_mapStartX+_qnode->_robotPose[1]*_scale)+a*cos(angle);
    _pos_[5] = (_mapStartY+_mapHeight-_qnode->_robotPose[0]*_scale)-a*sin(angle);
    qDebug() <<"angle:" << angle <<"\n"
             <<"ax:" << _pos_[0] <<"\n"
             <<"ay:" << _pos_[1] <<"\n"
             <<"bx:" << _pos_[2] <<"\n"
             <<"by:" << _pos_[3] <<"\n"
             <<"cx:" << _pos_[4] <<"\n"
             <<"cy:" << _pos_[5] <<"\n" <<"\n";
    update();
}

//界面析构函数
T3_AF_map::~T3_AF_map()
{
    delete ui;
    //日志
    T3LOG("7- 导航界面析构");
}
