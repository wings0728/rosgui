#ifndef T3_AF_WARNING_H
#define T3_AF_WARNING_H

#include "t3_af_config.hpp"
#include <QDialog>

namespace Ui {
class T3_AF_warning;
}

class T3_AF_warning : public QDialog
{
    Q_OBJECT

public:
    explicit T3_AF_warning(QWidget *parent = 0);
    ~T3_AF_warning();

private slots:
    void closeThis();

private:
    Ui::T3_AF_warning *ui;
    void paintEvent(QPaintEvent *event);
};

#endif // T3_AF_WARNING_H
