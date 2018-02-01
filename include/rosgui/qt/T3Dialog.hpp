#ifndef T3DIALOG_H
#define T3DIALOG_H

#include "t3_af_config.hpp"
#include <QDialog>
#include <QDesktopWidget>
#include <QApplication>
#include <QSize>

class T3Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit T3Dialog(QWidget *parent = 0);
    ~T3Dialog();

    float _width_;
    float _height_;


//    QSize sizeHint() const
//    {
//        return QSize(1200, 1000);
//    }

private:
    QDesktopWidget *deskWgt;
    QRect screenRect;
};


#endif // T3DIALOG_H
