#ifndef T3_AF_WELCOME_H
#define T3_AF_WELCOME_H

#include "t3_af_config.hpp"
#include "T3Dialog.hpp"

//#include "t3_af_login.h"
#include "t3_af_mainwindow.hpp"


namespace Ui {
class T3_AF_welcome;
}

class T3_AF_welcome : public T3Dialog
{
    Q_OBJECT

public:
    explicit T3_AF_welcome(QWidget *parent = 0);
    ~T3_AF_welcome();

    void enterSystem();

private slots:
    void timeUpdate();

private:
    Ui::T3_AF_welcome *ui;
    void closeEvent(QCloseEvent *event);
    T3Dialog *_father;
};

#endif // T3_AF_WELCOME_H
