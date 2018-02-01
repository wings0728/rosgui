#ifndef T3_AF_MAP_H
#define T3_AF_MAP_H

#include "t3_af_config.hpp"
#include "T3Dialog.hpp"
#include "t3_af_warning.hpp"
#include "t3_face_network.hpp"
#include "t3_af_mainwindow.hpp"

#include <QTime>
#include <QList>
#include <QLabel>
#include <QMouseEvent>
#include <math.h>
#include <vector>
using std::vector;

#include "../ros/qnode.hpp"

namespace Ui {
class T3_AF_map;
}

class T3_AF_map : public T3Dialog
{
    Q_OBJECT

public:
    explicit T3_AF_map(T3Dialog *mainWindow, QWidget *parent = 0);
    ~T3_AF_map();

    void exitToMainWindow();
    void getPoint();
    void getTarget();
    void routeUpdate();
    void manualCmd();
    void sleepBtn(int delayTime);

    void battery();


    vector<float> _pos_;
    vector<float> _arrow_;

    void pathClear();

    void buttonStatus(bool status);

    void stopRobot();
    void backToOrigin();

    void showSpeed();



signals:
    void lowBattSignal();

private slots:
    void timeUpdate();
    void autoMode();
    void checkMode();
    void printVideo(QImage faceImage);
    void ifConnected();
    void networkDisconnected();
    void lowBatt();
    void fullScreenMap();
    void exitFullScreenMap();



private:
    Ui::T3_AF_map *ui;
    T3Dialog *_mainWindow;
    T3Dialog *_father;
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *m);
    void mousePressEvent(QMouseEvent *p);
    void mouseReleaseEvent(QMouseEvent *r);
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent * event);
    rosgui::QNode *_qnode;
    float _mapStartX;
    float _mapStartY;
    float _mapWidth;
    float _mapHeight;
    int _startX;
    int _startY;
    int _startXCurrent;
    int _startYcurrent;
    int _startXTemp;
    int _startYTemp;
    int _moveX;
    int _moveY;
    float _originX;
    float _originY;
    QList<float> _pathX;
    QList<float> _pathY;
    QList<std::pair<double, double> > _route;
    vector<double> _robotPose;
    vector<double> _mapOrigin;
    float _scale;
    QTimer *_connect;
    double _lineS;
    double _angleS;
    QString _lineSText;
    QString _angleSText;
    int _videoLabelWidth = 0;
    int _videoLabelHeight = 0;



    T3_Face_Network *_netWork;
    Decoder *_decoder;
    FrameLineData *_frameLineData;
    QSqlDatabase _database;

    float _realWidth;
    float _realHeight;
    //ui
    QPushButton *_forwardPusbBtn_;
    QPushButton *_backwordPushBtn_;
    QPushButton *_leftTurnPushBtn_;
    QPushButton *_rightTurnPushBtn_;
    QPushButton *_stopPushBtn_;
    QPushButton *_backToOrigin_;
    QLabel *_lineSLabel_;
    QLabel *_angleSLabel_;
    int _battInt;
    QString _battQString;
    int i;


};

#endif // T3_AF_MAP_H
