#include "../include/rosgui/qt/t3_af_common.hpp"
#include "ui_t3_af_common.h"

T3_AF_common::T3_AF_common(QWidget *parent) :
    T3Dialog(parent),
    ui(new Ui::T3_AF_common)
{
    _father = new T3Dialog;
    ui->setupUi(this);
    this->setGeometry(0, 0, _father->_width_, _father->_height_);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint|Qt::WindowStaysOnBottomHint);
    this->showFullScreen();
    //
    T3LOG("0+");
}

T3_AF_common::~T3_AF_common()
{
    delete ui;
    //
    T3LOG("0-");
}
