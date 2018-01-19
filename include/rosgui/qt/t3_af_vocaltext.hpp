#ifndef T3_AF_VOCALTEXT_H
#define T3_AF_VOCALTEXT_H

#include "t3_af_config.hpp"
#include <QDialog>

namespace Ui {
class T3_AF_vocalText;
}

class T3_AF_vocalText : public QDialog
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
};

#endif // T3_AF_VOCALTEXT_H
