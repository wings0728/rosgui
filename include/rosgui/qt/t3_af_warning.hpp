#ifndef T3_AF_WARNING_H
#define T3_AF_WARNING_H

#include "t3_af_config.hpp"
#include "T3Dialog.hpp"

#include "../ros/qnode.hpp"

enum BgType
{
  warning,
  success
};
namespace Ui {
class T3_AF_warning;
}

class T3_AF_warning : public T3Dialog
{
    Q_OBJECT

public:
    explicit T3_AF_warning(QWidget *parent = 0,
                           QString string = "",
                           BgType bgType = warning);
    ~T3_AF_warning();

private slots:
    void closeThis();
//    void lowBatt();

private:
    Ui::T3_AF_warning *ui;
    T3Dialog *_father;
    QString _bgPath;
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    rosgui::QNode *_qnode;
};

#endif // T3_AF_WARNING_H
