#include "../../include/rosgui/qt/t3_af_facelog.hpp"
#include "ui_t3_af_facelog.h"

//界面构造函数
T3_AF_faceLog::T3_AF_faceLog(T3Dialog *face, QWidget *parent) :
    T3Dialog(parent),
    ui(new Ui::T3_AF_faceLog),
    _face(face)
{
    _father = new T3Dialog;
    //界面布局初始化
    ui->setupUi(this);
    this->move(0, 0);
    this->resize(_father->_width_, _father->_height_);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    this->showFullScreen();
    ui->_getImagePushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_checkPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_clearPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_exitPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_addNewUserPushBtn_->setFocusPolicy(Qt::NoFocus);
    //size
    ui->_addNewUserPushBtn_->setGeometry(this->width()*0.9375,
                                         this->height()*0.556,
                                         this->width()*0.0375,
                                         this->height()*0.0667);
    ui->_addUserBackgroundLabel_->setGeometry(this->width()*0.6313,
                                              this->height()*0.0000,
                                              this->width()*0.3688,
                                              this->height()*0.6022);
    ui->_ageLabel->setGeometry(this->width()*0.6438,
                               this->height()*0.2711,
                               this->width()*0.0625,
                               this->height()*0.0889);
    ui->_ageLineEdit_->setGeometry(this->width()*0.7000,
                                   this->height()*0.2822,
                                   this->width()*0.0938,
                                   this->height()*0.0556);
    ui->_backgroundLabel_->setGeometry(this->width()*0.0000,
                                       this->height()*0.0000,
                                       this->width()*1.0000,
                                       this->height()*1.0000);
    ui->_checkPushBtn_->setGeometry(this->width()*0.7375,
                                    this->height()*0.8711,
                                    this->width()*0.0500,
                                    this->height()*0.0889);
    ui->_clearPushBtn_->setGeometry(this->width()*0.8813,
                                    this->height()*0.8711,
                                    this->width()*0.0500,
                                    this->height()*0.0889);
    ui->_dateTimeLabel_->setGeometry(this->width()*0.3900,
                                     this->height()*0.9467,
                                     this->width()*0.2375,
                                     this->height()*0.0467);
    ui->_exitPushBtn_->setGeometry(this->width()*0.9625,
                                   this->height()*0.0044,
                                   this->width()*0.0363,
                                   this->height()*0.0556);
    ui->_getImagePushBtn_->setGeometry(this->width()*0.8875,
                                       this->height()*0.5556,
                                       this->width()*0.0375,
                                       this->height()*0.0667);
    ui->_imageAddressLineEdit_->setGeometry(this->width()*0.7000,
                                            this->height()*0.5489,
                                            this->width()*0.1538,
                                            this->height()*0.0556);
    ui->_imageLabel_->setGeometry(this->width()*0.6438,
                                  this->height()*0.5378,
                                  this->width()*0.0625,
                                  this->height()*0.0889);
    ui->_nameLabel_->setGeometry(this->width()*0.6438,
                                 this->height()*0.1400,
                                 this->width()*0.0625,
                                 this->height()*0.0889);
    ui->_nameLineEdit_->setGeometry(this->width()*0.7000,
                                    this->height()*0.1511,
                                    this->width()*0.0938,
                                    this->height()*0.0556);
    ui->_searchByNameLabel_->setGeometry(this->width()*0.6438,
                                         this->height()*0.7556,
                                         this->width()*0.0625,
                                         this->height()*0.0889);
    ui->_searchByNameLineEdit_->setGeometry(this->width()*0.7063,
                                            this->height()*0.7556,
                                            this->width()*0.2625,
                                            this->height()*0.0889);
    ui->_userImageLabel_->setGeometry(this->width()*0.8363,
                                      this->height()*0.0200,
                                      this->width()*0.1163,
                                      this->height()*0.3111);
    ui->_userTypeLabel_->setGeometry(this->width()*0.6438,
                                     this->height()*0.4044,
                                     this->width()*0.1000,
                                     this->height()*0.0889);
    ui->_userTypeLineEdit_->setGeometry(this->width()*0.7438,
                                        this->height()*0.4156,
                                        this->width()*0.2013,
                                        this->height()*0.0556);


    //界面浮现动画
    QPropertyAnimation *animation_ = new QPropertyAnimation(this, "windowOpacity");
//    animation_->setDuration(150);
//    animation_->setStartValue(0);
//    animation_->setEndValue(1);
//    animation_->start();
    //定时器
    QTimer *timer_ = new QTimer(this);
    timer_->start(100);
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

    for(int idx = 0; idx < kDelay; idx++){}

    this->close();
    delete this;
}

void T3_AF_faceLog::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

void T3_AF_faceLog::keyPressEvent(QKeyEvent *event)
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
T3_AF_faceLog::~T3_AF_faceLog()
{
  delete ui;
  //日志
  T3LOG("9- 人脸日志界面析构");
}
