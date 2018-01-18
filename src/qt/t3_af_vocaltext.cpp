#include "../../include/rosgui/qt/t3_af_vocaltext.hpp"
#include "ui_t3_af_vocaltext.h"

T3_AF_vocalText::T3_AF_vocalText(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::T3_AF_vocalText)
{
    ui->setupUi(this);
    ui->setupUi(this);
    this->move(0, 0);
    this->resize(800, 450);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->_exitPushBtn_->setFocusPolicy(Qt::NoFocus);
    connect(ui->_exitPushBtn_, &QPushButton::clicked, this, &T3_AF_vocalText::exitVocalText);
    QPropertyAnimation *animation_ = new QPropertyAnimation(this, "windowOpacity");
    animation_->setDuration(300);
    animation_->setStartValue(0);
    animation_->setEndValue(0.9);
    animation_->start();
    //
    T3LOG("vocalText deleted");
}

void T3_AF_vocalText::exitVocalText()
{
    this->close();
    delete this;
}


void T3_AF_vocalText::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

T3_AF_vocalText::~T3_AF_vocalText()
{
    delete ui;
    //
    T3LOG("vocalText deleted")
}
