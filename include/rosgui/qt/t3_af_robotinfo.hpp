#ifndef T3_AF_ROBOTINFO_H
#define T3_AF_ROBOTINFO_H

#include "t3_af_config.hpp"
#include <QDialog>

namespace Ui {
class T3_AF_robotInfo;
}

class T3_AF_robotInfo : public QDialog
{
    Q_OBJECT

public:
    explicit T3_AF_robotInfo(QDialog *mainWindow, QWidget *parent = 0);
    ~T3_AF_robotInfo();

    void exitToMainWindow();

private slots:
    void timeUpdate();

private:
    Ui::T3_AF_robotInfo *ui;
    QDialog *_mainWindow;
    void paintEvent(QPaintEvent *event);
};

#endif // T3_AF_ROBOTINFO_H
