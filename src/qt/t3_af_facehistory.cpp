#include "../../include/rosgui/qt/t3_af_facehistory.hpp"
#include "ui_t3_af_facehistory.h"

T3_AF_faceHistory::T3_AF_faceHistory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::T3_AF_faceHistory)
{
    ui->setupUi(this);
    this->move(0, 0);
    this->resize(800, 450);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->_exitPushBtn_->setFocusPolicy(Qt::NoFocus);
    connect(ui->_exitPushBtn_, &QPushButton::clicked, this, &T3_AF_faceHistory::exitFaceHistory);
    QPropertyAnimation *animation_ = new QPropertyAnimation(this, "windowOpacity");
    animation_->setDuration(300);
    animation_->setStartValue(0);
    animation_->setEndValue(0.9);
    animation_->start();
    //
    T3LOG("faceHis created");
}

void T3_AF_faceHistory::exitFaceHistory()
{
    this->close();
    delete this;
}

void T3_AF_faceHistory::closeEvent(QCloseEvent *event)
{
    event->ignore();
}


T3_AF_faceHistory::~T3_AF_faceHistory()
{
    delete ui;
    //
    T3LOG("faceHis deleted");
}
