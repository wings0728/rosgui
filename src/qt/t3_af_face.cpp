#include "../../include/rosgui/qt/t3_af_face.hpp"
#include "ui_t3_af_face.h"

//界面构造函数
T3_AF_face::T3_AF_face(QDialog *mainWindow, QWidget *parent) :
    QDialog(parent),
    _mainWindow(mainWindow),
    ui(new Ui::T3_AF_face)
{
    //界面布局初始化
    ui->setupUi(this);
    this->move(0, 0);
    this->resize(800, 450);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    ui->_dateLabel_->setText("");
    ui->_dateLabel_->setStyleSheet("color:white");
    ui->_timeLabel_->setText("");
    ui->_timeLabel_->setStyleSheet("color:white");
    ui->_exitPushBtn_->setText("");
    ui->_exitPushBtn_->setStyleSheet("border-image:url(:/Pictures/face_back.png)");
    ui->_faceGifLabel_->setText("");
    ui->_faceGifLabel_->setStyleSheet("border-image:url(:/Pictures/face_gif.png)");
    ui->_textLabel_->setText("");
    ui->_textLabel_->setStyleSheet("border-image:url(:/Pictures/face_text.png)");
    ui->_squareLabel_->setText("");
    ui->_squareLabel_->setStyleSheet("border-image:url(:/Pictures/face_square.png)");
    ui->_videoLabel_->setText("视频显示区");
    ui->_videoLabel_->setStyleSheet("color:white");
    ui->_logBackgroundLabel_->setText("");
    ui->_logBackgroundLabel_->setStyleSheet("border-image:url(:/Pictures/face_logBackground.png)");
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
    connect(ui->_exitPushBtn_, &QPushButton::clicked, this, &T3_AF_face::exitToMainWindow);
    //日志
    T3LOG("5+ 人脸界面构造");
}

//显示时间
void T3_AF_face::timeUpdate()
{
    QDateTime dateTime_ = QDateTime::currentDateTime();
    QString dataStr_ = dateTime_.toString("yyyy-MM-dd dddd");
    QString timeStr_ = dateTime_.toString("hh:mm");
    ui->_dateLabel_->setText(dataStr_);
    ui->_timeLabel_->setText(timeStr_);
}

//界面背景绘制
void T3_AF_face::paintEvent(QPaintEvent *)
{
    QPainter paint_(this);
    paint_.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/Pictures/face_background.png"));
}
//退出
void T3_AF_face::exitToMainWindow()
{
    _mainWindow->show();
    this->close();
    delete this;
}

//界面析构函数
T3_AF_face::~T3_AF_face()
{
    delete ui;
    //日志
    T3LOG("5- 人脸界面析构");
}
