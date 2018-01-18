#ifndef T3_AF_CONFIRMEXIT_H
#define T3_AF_CONFIRMEXIT_H

#include "t3_af_config.hpp"
#include <QDialog>

namespace Ui {
class T3_AF_confirmExit;
}

class T3_AF_confirmExit : public QDialog
{
    Q_OBJECT

public:
    explicit T3_AF_confirmExit(QDialog *welcome, QDialog *mainWindow, QWidget *parent = 0);
    ~T3_AF_confirmExit();

    void confirmExit();
    void doNotExit();

private:
    Ui::T3_AF_confirmExit *ui;
    QDialog *_welcome;
    QDialog *_mainWindow;
    void paintEvent(QPaintEvent *enent);
    void closeEvent(QCloseEvent *event);
};

#endif // T3_AF_CONFIRMEXIT_H
