#ifndef T3_AF_FACE_H
#define T3_AF_FACE_H

#include "t3_af_config.hpp"
#include "T3Dialog.hpp"

#include "t3_af_facelog.hpp"
#include "t3_af_facehistory.hpp"
#include "t3_af_vocaltext.hpp"



namespace Ui {
class T3_AF_face;
}

class T3_AF_face : public T3Dialog
{
    Q_OBJECT

public:
    explicit T3_AF_face(T3Dialog *mainWindow, QWidget *parent = 0);
    ~T3_AF_face();

    void exitToMainWindow();
    void enterFaceLog();
    void enterFaceHistory();
    void enterVocalText();

private slots:
    void timeUpdate();

private:
    Ui::T3_AF_face *ui;
    T3Dialog *_mainWindow;
    T3Dialog *_father;
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // T3_AF_FACE_H
