#include "../../include/rosgui/qt/t3_af_confirmexit.hpp"
#include "ui_t3_af_confirmexit.h"

//界面构造函数
T3_AF_confirmExit::T3_AF_confirmExit(T3Dialog *welcome, T3Dialog *mainWindow, QWidget *parent) :
    T3Dialog(parent),
    _welcome(welcome),
    _mainWindow(mainWindow),
    ui(new Ui::T3_AF_confirmExit)
{
    _father = new T3Dialog;
    //界面布局初始化
    ui->setupUi(this);
    this->setGeometry(0, 0, _father->_width_, _father->_height_);
//    this->move(0, 0);
//    this->resize(_father->_width_, _father->_height_);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->showFullScreen();
    ui->_yesPushBtn_->setText("");
    ui->_yesPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_yesPushBtn_->setStyleSheet("border-image:url(:/Pictures/confirmExit_yes.png)");
    ui->_noPushBtn_->setText("");
    ui->_noPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_noPushBtn_->setStyleSheet("border-image:url(:/Pictures/confirmExit_no.png)");
    ui->_confirmLabel_->setText("");
    ui->_confirmLabel_->setStyleSheet("border-image:url(:/Pictures/confirmExit_label.png)");
    //size
    ui->_confirmLabel_->setGeometry(this->width()*0.4250,
                                    this->height()*0.3333,
                                    this->width()*0.1500,
                                    this->height()*0.0889);
    ui->_noPushBtn_->setGeometry(this->width()*0.5500,
                               this->height()*0.4889,
                               this->width()*0.1000,
                               this->height()*0.1778);
    ui->_yesPushBtn_->setGeometry(this->width()*0.3500,
                                this->height()*0.4889,
                                this->width()*0.1000,
                                this->height()*0.1778);
    //界面浮现动画
//    QPropertyAnimation *animation_ = new QPropertyAnimation(this, "windowOpacity");
//    animation_->setDuration(50);
//    animation_->setStartValue(0);
//    animation_->setEndValue(0.9);
//    animation_->start();
    //链接ui部件与功能
    connect(ui->_yesPushBtn_, &QPushButton::clicked, this, &T3_AF_confirmExit::confirmExit);
    connect(ui->_noPushBtn_, &QPushButton::clicked, this, &T3_AF_confirmExit::doNotExit);
    //
    _qnode = rosgui::QNode::getInstance();
    //日志
    T3LOG("4+ 退出确认界面构造");
    connect(_qnode, SIGNAL(lowPower()), this, SLOT(lowBatt()));
}

void T3_AF_confirmExit::lowBatt()
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

//界面背景绘制
void T3_AF_confirmExit::paintEvent(QPaintEvent *)
{
    QPainter paint_(this);
    paint_.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/Pictures/confirmExit_background.png"));
}

//返回welcome
void T3_AF_confirmExit::confirmExit()
{
    stopRobot();
    _welcome->show();
    this->close();
    _mainWindow->close();
    delete this;
    delete _mainWindow;
}

//返回mainWindow
void T3_AF_confirmExit::doNotExit()
{
    this->close();
    delete this;
}

void T3_AF_confirmExit::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

void T3_AF_confirmExit::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Escape:
        confirmExit();
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}

void T3_AF_confirmExit::stopRobot()
{
    _qnode->setOperationMode(rosgui::QNode::Manual);
    _qnode->setManualCmd(rosgui::QNode::Stop);
}

//界面析构函数
T3_AF_confirmExit::~T3_AF_confirmExit()
{
    delete ui;
    //日志
    T3LOG("4- 退出确认界面析构");
}
