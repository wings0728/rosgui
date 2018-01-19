#ifndef T3_AF_FACE_H
#define T3_AF_FACE_H

#include "t3_af_config.hpp"
#include <QDialog>

#include "t3_af_facelog.hpp"
#include "t3_af_facehistory.hpp"
#include "t3_af_vocaltext.hpp"



namespace Ui {
class T3_AF_face;
}

class T3_AF_face : public QDialog
{
    Q_OBJECT

public:
    explicit T3_AF_face(QDialog *mainWindow, QWidget *parent = 0);
    ~T3_AF_face();

    void exitToMainWindow();
    void enterFaceLog();
    void enterFaceHistory();
    void enterVocalText();

private slots:
    void timeUpdate();

private:
    Ui::T3_AF_face *ui;
    QDialog *_mainWindow;
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // T3_AF_FACE_H
