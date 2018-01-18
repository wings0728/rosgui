#include "../../include/rosgui/qt/t3_af_facelog.hpp"
#include "ui_t3_af_facelog.h"

//界面构造函数
T3_AF_faceLog::T3_AF_faceLog(QDialog *face, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::T3_AF_faceLog),
  _face(face)
{
  //界面布局初始化
  ui->setupUi(this);
  this->move(0, 0);
  this->resize(800, 450);
  this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
  ui->_getImagePushBtn_->setFocusPolicy(Qt::NoFocus);
  ui->_checkPushBtn_->setFocusPolicy(Qt::NoFocus);
  ui->_clearPushBtn_->setFocusPolicy(Qt::NoFocus);
  ui->_exitPushBtn_->setFocusPolicy(Qt::NoFocus);
  ui->_addNewUserPushBtn_->setFocusPolicy(Qt::NoFocus);
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
  connect(ui->_exitPushBtn_, &QPushButton::clicked, this, &T3_AF_faceLog::exitToFace);
  //日志
  T3LOG("9+ 人脸日志界面构造");
}

//显示时间
void T3_AF_faceLog::timeUpdate()
{
    QDateTime dateTime_ = QDateTime::currentDateTime();
    QString dataTimeStr_ = dateTime_.toString("yyyy-MM-dd hh:mm:ss dddd");
    //QString timeStr_ = dateTime_.toString("hh:mm");
    ui->_dateTimeLabel_->setText(dataTimeStr_);
    //ui->_timeLabel_->setText(timeStr_);
}

//exitToFace
void T3_AF_faceLog::exitToFace()
{
    _face->show();
    this->close();
    delete this;
}

void T3_AF_faceLog::closeEvent(QCloseEvent *event)
{
    event->ignore();
}


//界面析构函数
T3_AF_faceLog::~T3_AF_faceLog()
{
  delete ui;
  //日志
  T3LOG("9- 人脸日志界面析构");
}
