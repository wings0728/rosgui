#ifndef T3_AF_FACE_H
#define T3_AF_FACE_H


#include <QStringListModel>
#include <QStringList>
#include "t3_af_config.hpp"
#include "T3Dialog.hpp"

#include "t3_af_facelog.hpp"
#include "t3_af_facehistory.hpp"
#include "t3_af_vocaltext.hpp"
#include "t3_face_network.hpp"

#include "../ros/qnode.hpp"



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
    void stopRobot();
    void battery();

private slots:
    void timeUpdate();
    void printVideo(QImage faceImage);
    void networkDisconnected();

private:
    Ui::T3_AF_face *ui;
    T3Dialog *_mainWindow;
    T3Dialog *_father;
    T3_Face_Network *_netWork;

    Decoder *_decoder;
    FrameLineData *_frameLineData;
    QSqlDatabase _database;
    QStringListModel *_stringListModel;
    int _videoLabelHeight = 0;
    int _videoLabelWidth = 0;


    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    rosgui::QNode *_qnode;

    QString _battQString;
    int _battInt;
    //ui
    QPushButton *_stopPushBtn_;
};

#endif // T3_AF_FACE_H
