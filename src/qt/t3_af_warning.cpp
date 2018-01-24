#include "../../include/rosgui/qt/t3_af_warning.hpp"
#include "ui_t3_af_warning.h"



T3_AF_warning::T3_AF_warning(QWidget *parent , QString string, BgType bgType) :
    T3Dialog(parent),
    ui(new Ui::T3_AF_warning)
{
    _father = new T3Dialog;
    //
    T3LOG("*+ warning create");
    ui->setupUi(this);
    this->setGeometry(0, 0, _father->_width_, _father->_height_);
//    this->move(0, 0);
//    this->resize(_father->_width_, _father->_height_);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->showFullScreen();
    ui->_exitPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_exitPushBtn_->setStyleSheet("background:transparent;border-width:0;border-style:outset;color:white");
    //size
    ui->_warningLabel_->setGeometry(this->width()*0.2125,
                                    this->height()*0.7111,
                                    this->width()*0.5750,
                                    this->height()*0.1000);
    ui->_exitPushBtn_->setGeometry(this->width()*0.0000,
                                   this->height()*0.0000,
                                   this->width()*1.0000,
                                   this->height()*1.0000);
    //font
    QFont warningLabelFont_;
    warningLabelFont_.setPointSize(ui->_warningLabel_->height() * kLabelFontScal);
    ui->_warningLabel_->setFont(warningLabelFont_);
    //func
    connect(ui->_exitPushBtn_, SIGNAL(clicked()), this, SLOT(closeThis()));
//    QPropertyAnimation *animation_ = new QPropertyAnimation(this, "windowOpacity");
//    animation_->setDuration(50);
//    animation_->setStartValue(0);
//    //
//    animation_->setEndValue(0.9);
//    animation_->start();
    //
    ui->_warningLabel_->setText(string);
    switch (bgType) {
    case warning:
      _bgPath = ":/Pictures/warning_background.png";
      break;
    case success:
      _bgPath = ":/Pictures/warning_success.png";
    default:
      break;
    }
}

void T3_AF_warning::paintEvent(QPaintEvent *)
{
    QPainter paint_(this);
    paint_.drawPixmap(0, 0, this->width(), this->height(), QPixmap(_bgPath));
}

void T3_AF_warning::closeThis()
{
    this->close();
    delete this;
}

void T3_AF_warning::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

void T3_AF_warning::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}

T3_AF_warning::~T3_AF_warning()
{
    delete ui;
    //
    T3LOG("*- warning delete");
}
