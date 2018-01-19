#include "../../include/rosgui/qt/t3_af_welcome.hpp"
#include "ui_t3_af_welcome.h"


//界面构造函数
T3_AF_welcome::T3_AF_welcome(QWidget *parent) :
    T3Dialog(parent),
    ui(new Ui::T3_AF_welcome)
{
    //test
    _father = new T3Dialog;
    //test FIN.
    //界面布局初始化
    ui->setupUi(this);
    this->setGeometry(0, 0, _father->_width_, _father->_height_);
//    this->move(0, 0);
//    this->resize(_father->_width_, _father->_height_);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    this->showFullScreen();
    ui->_enterSystemPushBtn_->setGeometry(0, 0, this->width(), this->height());
    ui->_enterSystemPushBtn_->setText("");
    ui->_enterSystemPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_enterSystemPushBtn_->setStyleSheet("background:transparent;border-width:0;border-style:outset;color:white");
    ui->_gifLabel_->setGeometry(0, 0, this->width(), this->height());
    ui->_gifLabel_->setText("");
    ui->_dateTimeLabel_->setGeometry(0.0125*this->width(), 0.02222*this->height(), 0.3125*this->width(), 0.04444*this->height());
    ui->_dateTimeLabel_->setText("");
    ui->_dateTimeLabel_->setStyleSheet("color:white");
    //界面浮现动画
//    QPropertyAnimation *animation_ = new QPropertyAnimation(this, "windowOpacity");
//    animation_->setDuration(300);
//    animation_->setStartValue(0);
//    animation_->setEndValue(1);
//    animation_->start();
    //设置GIF动画
    QMovie *welcomeBackground_ = new QMovie(":/Pictures/welcome_background.gif");
    welcomeBackground_->setScaledSize(QSize(this->width(), this->height()));
    welcomeBackground_->setSpeed(90);
    ui->_gifLabel_->setMovie(welcomeBackground_);
    welcomeBackground_->start();
    //定时器
    QTimer *timer_ = new QTimer(this);
    timer_->start(100);
    //链接ui部件与功能
    connect(timer_, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    connect(ui->_enterSystemPushBtn_, &QPushButton::clicked, this, &T3_AF_welcome::enterSystem);
    //日志
    T3LOG("1+ 欢迎界面构造");
}

//进入logIn
void T3_AF_welcome::enterSystem()
{
    //T3_AF_logIn *logIn_ = new T3_AF_logIn(this);
    //logIn_->show();

    T3_AF_mainWindow *mainWindow_ = new T3_AF_mainWindow(this);
    mainWindow_->show();

    for(int idx = 0; idx < kDelay; idx++){}

    qDebug("delay done");

    this->hide();
}

//显示时间
void T3_AF_welcome::timeUpdate()
{
    QDateTime dateTime_ = QDateTime::currentDateTime();
    QString dataTimeStr_ = dateTime_.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->_dateTimeLabel_->setText(dataTimeStr_);
}

//
void T3_AF_welcome::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

//界面析构函数
T3_AF_welcome::~T3_AF_welcome()
{
    delete ui;
    //日志
    T3LOG("1- 欢迎界面析构");
}
