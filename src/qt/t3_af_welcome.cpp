#include "../../include/rosgui/qt/t3_af_welcome.hpp"
#include "ui_t3_af_welcome.h"


//界面构造函数
T3_AF_welcome::T3_AF_welcome(QWidget *parent) :
    T3Dialog(parent),
    ui(new Ui::T3_AF_welcome)
{
    //test
    _father = new T3Dialog;
    _common = new T3_AF_common;
    _common->show();
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

    ui->_battery_->setGeometry(this->width()*0.9288,
                               this->height()*0.0222,
                               this->width()*0.0588,
                               this->height()*0.0444);
    ui->_battIMG_->setGeometry(this->width()*0.7913,
                               this->height()*0.0222,
                               this->width()*0.1288,
                               this->height()*0.0444);
    ui->_battGIF_->setGeometry(this->width()*0.7913,
                               this->height()*0.0222,
                               this->width()*0.1288,
                               this->height()*0.0444);
    QMovie *battLow_ = new QMovie(":/Pictures/batt_4.gif");
    battLow_->setScaledSize(QSize(ui->_battGIF_->width(), ui->_battGIF_->height()));
    battLow_->setSpeed(130);
    ui->_battGIF_->setMovie(battLow_);
    battLow_->start();
    _qnode = rosgui::QNode::getInstance();
    //font
    QFont dateTimeLabelFont_;
    dateTimeLabelFont_.setPointSize(ui->_dateTimeLabel_->height() * kLabelFontScal);
    ui->_dateTimeLabel_->setFont(dateTimeLabelFont_);
    QFont battFont_;
    battFont_.setPointSize(ui->_battery_->height() * kLabelFontScal);
    ui->_battery_->setFont(battFont_);
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
    connect(_qnode, SIGNAL(lowPower()), this, SLOT(lowBatt()));
    //日志
    T3LOG("1+ 欢迎界面构造");
}

void T3_AF_welcome::lowBatt()
{
    emit lowBattSignal();
    if(rosgui::QNode::Auto == _qnode->getOprationMode())
    {
        _qnode->goalUpdate(0.0, 0.0, 0.0);
    }
    else
    {
        _qnode->setManualCmd(rosgui::QNode::Stop);
        _qnode->setOperationMode(rosgui::QNode::Auto);
        _qnode->goalUpdate(0.0, 0.0, 0.0);
    }
}

//进入logIn
void T3_AF_welcome::enterSystem()
{
    //T3_AF_logIn *logIn_ = new T3_AF_logIn(this);
    //logIn_->show();

    T3_AF_mainWindow *mainWindow_ = new T3_AF_mainWindow(this);
    mainWindow_->show();

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

void T3_AF_welcome::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Escape:
        delete this;
        break;
    default:
        break;
    }
}

void T3_AF_welcome::battery()
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

void T3_AF_welcome::paintEvent(QPaintEvent *)
{
    battery();
}

//界面析构函数
T3_AF_welcome::~T3_AF_welcome()
{
    delete ui;
    delete _common;
    _qnode->shutDownRos();
    //日志
    T3LOG("1- 欢迎界面析构");
}
