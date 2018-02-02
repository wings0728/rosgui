#ifndef T3_AF_MAPONLY_H
#define T3_AF_MAPONLY_H

#include "t3_af_config.hpp"
#include "T3Dialog.hpp"
#include "t3_af_map.hpp"

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

class T3_AF_map;

class T3_AF_mapOnly : public T3Dialog
{
    Q_OBJECT

public:
    explicit T3_AF_mapOnly(T3_AF_map *map, QWidget *parent = 0);
    ~T3_AF_mapOnly();

    void exit();
    void battery();
    void getMapGeometry();
    void posUpdate();
    void arrowUpdate();
    void routeUpdate();
    void clearPath();

private slots:
    void timeUpdate();
    void exitUI();

private:
    Ui::T3_AF_mapOnly *ui;
    T3_AF_map *_map;
    T3Dialog *_father;
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
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
    vector<float> _pos_;
    vector<float> _arrow_;
    vector<double> _robotPose;
    vector<double> _mapOrigin;
    QList<float> _pathX;
    QList<float> _pathY;
    float _originX;
    float _originY;
    QList<std::pair<double, double> > _route;

};

#endif // T3_AF_MAPONLY_H
