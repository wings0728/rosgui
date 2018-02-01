#include "../../include/rosgui/qt/T3Dialog.hpp"

T3Dialog::T3Dialog(QWidget *parent) :
    QDialog(parent)
{
    deskWgt = QApplication::desktop();
    screenRect  =deskWgt->screenGeometry();
    _width_ = screenRect.width();
    _height_ = screenRect.height();
}

T3Dialog::~T3Dialog()
{
}

