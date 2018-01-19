#ifndef T3_AF_CONFIRMEXIT_H
#define T3_AF_CONFIRMEXIT_H

#include "t3_af_config.hpp"
#include "T3Dialog.hpp"

namespace Ui {
class T3_AF_confirmExit;
}

class T3_AF_confirmExit : public T3Dialog
{
    Q_OBJECT

public:
    explicit T3_AF_confirmExit(T3Dialog *welcome, T3Dialog *mainWindow, QWidget *parent = 0);
    ~T3_AF_confirmExit();

    void confirmExit();
    void doNotExit();

private:
    Ui::T3_AF_confirmExit *ui;
    T3Dialog *_welcome;
    T3Dialog *_mainWindow;
    T3Dialog *_father;
    void paintEvent(QPaintEvent *enent);
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // T3_AF_CONFIRMEXIT_H
