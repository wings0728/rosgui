#include "../../include/rosgui/qt/t3_af_warning.hpp"
#include "ui_t3_af_warning.h"

T3_AF_warning::T3_AF_warning(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::T3_AF_warning)
{
    //
    T3LOG("*+ warning create");
    ui->setupUi(this);
    this->move(0, 0);
    this->resize(800, 450);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    ui->_exitPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_exitPushBtn_->setStyleSheet("background:transparent;border-width:0;border-style:outset;color:white");
    connect(ui->_exitPushBtn_, SIGNAL(clicked()), this, SLOT(closeThis()));
    QPropertyAnimation *animation_ = new QPropertyAnimation(this, "windowOpacity");
    animation_->setDuration(100);
    animation_->setStartValue(0);
    //
    animation_->setEndValue(0.9);
    animation_->start();
    //
    ui->_warningLabel_->setText("warning label");
}

void T3_AF_warning::paintEvent(QPaintEvent *)
{
    QPainter paint_(this);
    paint_.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/Pictures/warning_background.png"));
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

T3_AF_warning::~T3_AF_warning()
{
    delete ui;
    //
    T3LOG("*- warning delete")
}
