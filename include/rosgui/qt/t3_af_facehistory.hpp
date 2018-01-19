#ifndef T3_AF_FACEHISTORY_H
#define T3_AF_FACEHISTORY_H

#include "t3_af_config.hpp"
#include "T3Dialog.hpp"

namespace Ui {
class T3_AF_faceHistory;
}

class T3_AF_faceHistory : public T3Dialog
{
    Q_OBJECT

public:
    explicit T3_AF_faceHistory(QWidget *parent = 0);
    ~T3_AF_faceHistory();

    void exitFaceHistory();

private:
    Ui::T3_AF_faceHistory *ui;
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    T3Dialog *_father;
};

#endif // T3_AF_FACEHISTORY_H
