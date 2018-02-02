#ifndef T3_AF_FACEHISTORY_H
#define T3_AF_FACEHISTORY_H

#include <QSqlTableModel>
#include "t3_af_config.hpp"
#include "T3Dialog.hpp"

#include "../ros/qnode.hpp"


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

private slots:
//    void lowBatt();

private:
    Ui::T3_AF_faceHistory *ui;
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    T3Dialog *_father;
    QSqlQueryModel *_model;
    rosgui::QNode *_qnode;
};

#endif // T3_AF_FACEHISTORY_H
