#include "../../include/rosgui/qt/t3_af_login.hpp"
#include "ui_t3_af_login.h"

//界面构造函数
T3_AF_logIn::T3_AF_logIn(QDialog *welcome, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::T3_AF_logIn),
    _welcome(welcome)
{
    //界面布局初始化
    ui->setupUi(this);
    this->move(0, 0);
    this->resize(800, 450);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    ui->_dateTimeLabel_->setText("");
    ui->_dateTimeLabel_->setStyleSheet("color:rgb(7, 221, 225)");
    ui->_logLabel_->setText("");
    ui->_logLabel_->setStyleSheet("border-image:url(:/Pictures/logIn_logBackground)");
    ui->_titleLabel_->setText("登  录");
    ui->_userNameLabel_->setText("用户名");
    ui->_userNameLineEdit_->setText("cc");
    ui->_userNameLineEdit_->setStyleSheet("background:transparent;border-width:0;border-style:outset;color:white");
    ui->_userNameLineEdit_->setFocus();
    ui->_passwordLabel_->setText("密码");
    ui->_passwordLineEdit_->setText("666");
    ui->_passwordLineEdit_->setStyleSheet("background:transparent;border-width:0;border-style:outset;color:white");
    ui->_returnPushBtn_->setText("退出");
    ui->_returnPushBtn_->setFlat(true);
    ui->_logInPushBtn_->setText("确定");
    ui->_logInPushBtn_->setFlat(true);
    //EditLine限制
    QRegExp regx_("[a-zA-Z0-9]+$");
    ui->_userNameLineEdit_->setValidator(new QRegExpValidator(regx_, ui->_userNameLineEdit_));
    ui->_passwordLineEdit_->setValidator(new QRegExpValidator(regx_, ui->_passwordLineEdit_));
    ui->_passwordLineEdit_->setEchoMode(QLineEdit::Password);
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
    connect(ui->_returnPushBtn_, &QPushButton::clicked, this, &T3_AF_logIn::backToWelcome);\
    connect(ui->_logInPushBtn_, &QPushButton::clicked, this, &T3_AF_logIn::logIn);
    //日志
    T3LOG("2+ 登录界面构造");
}

//显示时间
void T3_AF_logIn::timeUpdate()
{
    QDateTime dateTime_ = QDateTime::currentDateTime();
    QString dataTimeStr_ = dateTime_.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->_dateTimeLabel_->setText(dataTimeStr_);
}

//界面背景绘制
void T3_AF_logIn::paintEvent(QPaintEvent *)
{
    QPainter paint_(this);
    paint_.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/Pictures/logIn_background.png"));
}

//返回welome
void T3_AF_logIn::backToWelcome()
{
    ui->_userNameLineEdit_->clear();
    ui->_passwordLineEdit_->clear();
    _welcome->show();
    this->hide();
    delete this;
}

//确认密码
QString T3_AF_logIn::getPassword(QString getUserName)
{
    QString password_;
    QSqlRecord record_;
    T3_AF_userData userDatabase_;
    userDatabase_.createConnection();
    record_ = userDatabase_.searchByUserName(getUserName);
    password_ = record_.value(1).toString();
    qDebug() << getUserName << password_;
    userDatabase_.removeConnection();
    return password_;
}
//进入mainWindow
void T3_AF_logIn::logIn()
{
    QString checkPassword_;
    checkPassword_ = getPassword(ui->_userNameLineEdit_->text());
    if("" == checkPassword_)
    {
        QMessageBox::warning(this, tr("错误"), tr("用户名或密码不正确\n请重新输入"), QMessageBox::Yes);
    }
    else if(ui->_passwordLineEdit_->text() != checkPassword_)
    {
        QMessageBox::warning(this, tr("错误"), tr("用户名或密码不正确\n请重新输入"), QMessageBox::Yes);
    }
    else
    {
        T3_AF_mainWindow *_mainWindow = new T3_AF_mainWindow(_welcome);
        _mainWindow->show();
        this->close();
        delete this;
    }
}

//界面析构函数
T3_AF_logIn::~T3_AF_logIn()
{
    delete ui;
    //日志
    T3LOG("2- 登陆界面析构");
}
