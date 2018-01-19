#ifndef T3_AF_VOCALTEXT_H
#define T3_AF_VOCALTEXT_H

#include "t3_af_config.hpp"
#include "T3Dialog.hpp"

namespace Ui {
class T3_AF_vocalText;
}

class T3_AF_vocalText : public T3Dialog
{
    Q_OBJECT

public:
    explicit T3_AF_vocalText(QWidget *parent = 0);
    ~T3_AF_vocalText();

    void exitVocalText();

private:
    Ui::T3_AF_vocalText *ui;
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    T3Dialog *_father;
};

#endif // T3_AF_VOCALTEXT_H
