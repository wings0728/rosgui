#ifndef T3_AF_MAPONLY_H
#define T3_AF_MAPONLY_H

#include "t3_af_config.hpp"
#include "T3Dialog.hpp"

#include <QTimer>
#include <QList>
#include <QMouseEvent>
#include <math.h>
#include <vector>
using std::vector;

#include "../ros/qnode.hpp"

namespace Ui {
class T3_AF_mapOnly;
}

class T3_AF_mapOnly : public T3Dialog
{
    Q_OBJECT

public:
    explicit T3_AF_mapOnly(T3Dialog *map, QWidget *parent = 0);
    ~T3_AF_mapOnly();

    void exit();
    void battery();
    void getMapGeometry();

signals:
    void lowBattSignal();

private slots:
    void lowBatt();
    void timeUpdate();

private:
    Ui::T3_AF_mapOnly *ui;
    T3Dialog *_map;
    T3Dialog *_father;
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *m);
    void mousePressEvent(QMouseEvent *p);
    void mouseReleaseEvent(QMouseEvent *r);
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    rosgui::QNode *_qnode;

    int _battInt;
    QString _battQString;

    QImage _mapIMG;
    float _mapHeightReal;
    float _mapWidthReal;
    float _mapX;
    float _mapY;
    float _mapHeight;
    float _mapWidth;
    float _Vcenter;
    float _Hcenter;
    float _scale;
};

#endif // T3_AF_MAPONLY_H
