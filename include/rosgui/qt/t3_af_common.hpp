#ifndef T3_AF_COMMON_H
#define T3_AF_COMMON_H

#include "T3Dialog.hpp"

namespace Ui {
class T3_AF_common;
}

class T3_AF_common : public T3Dialog
{
    Q_OBJECT

public:
    explicit T3_AF_common(QWidget *parent = 0);
    ~T3_AF_common();

private:
    Ui::T3_AF_common *ui;
    T3Dialog *_father;
    void paintEvent(QPaintEvent *event);
};

#endif // T3_AF_COMMON_H
