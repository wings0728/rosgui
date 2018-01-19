#ifndef T3_AF_FACEHISTORY_H
#define T3_AF_FACEHISTORY_H

#include "t3_af_config.hpp"
#include <QDialog>

namespace Ui {
class T3_AF_faceHistory;
}

class T3_AF_faceHistory : public QDialog
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
};

#endif // T3_AF_FACEHISTORY_H
