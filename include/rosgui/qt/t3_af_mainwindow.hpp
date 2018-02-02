#ifndef T3_AF_MAINWINDOW_H
#define T3_AF_MAINWINDOW_H

#include "t3_af_config.hpp"
#include "T3Dialog.hpp"

#include "t3_af_confirmexit.hpp"
#include "t3_af_face.hpp"
#include "t3_af_weatherforecast.hpp"
#include "t3_af_map.hpp"
#include "t3_af_robotinfo.hpp"

#include "../ros/qnode.hpp"

namespace Ui {
class T3_AF_mainWindow;
}

class T3_AF_mainWindow : public T3Dialog
{
    Q_OBJECT

public:
    explicit T3_AF_mainWindow(T3Dialog *welcome, QWidget *parent = 0);
    ~T3_AF_mainWindow();

    void exitToWelcome();
    void toFace();
    void toWeatherForecast();
    void toMap();
    void toRobotInfo();
    void stopRobot();
    void battery();

signals:
    void updateMode();

private slots:
    void timeUpdate();
    void weatherUpdate(Today today);
//    void lowBatt();

private:
    Ui::T3_AF_mainWindow *ui;
    T3Dialog *_welcome;
    T3Dialog *_map;
    void paintEvent(QPaintEvent *event);
    T3_AF_getWeather *_weather;
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    T3Dialog *_father;
    rosgui::QNode *_qnode;
    int _battInt;
    QString _battQString;
    //ui
    QPushButton *_stopPushBtn_;

};

#endif // T3_AF_MAINWINDOW_H
