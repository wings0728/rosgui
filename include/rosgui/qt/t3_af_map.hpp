#ifndef T3_AF_MAP_H
#define T3_AF_MAP_H

#include "t3_af_config.hpp"
#include <QDialog>

#include <QList>
#include <QMouseEvent>
#include <math.h>
#include <vector>
using std::vector;

#include "../ros/qnode.hpp"

namespace Ui {
class T3_AF_map;
}

class T3_AF_map : public QDialog
{
    Q_OBJECT

public:
    explicit T3_AF_map(QDialog *mainWindow, QWidget *parent = 0);
    ~T3_AF_map();

    void exitToMainWindow();
    void getPoint();
    void getTarget();


    vector<float> _pos_;
    vector<float> _arrow_;

    void pathClear();


private slots:
    void timeUpdate();
    void autoMode();

private:
    Ui::T3_AF_map *ui;
    QDialog *_mainWindow;
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *m);
    void mousePressEvent(QMouseEvent *p);
    void mouseReleaseEvent(QMouseEvent *r);
    void closeEvent(QCloseEvent *event);
    rosgui::QNode *_qnode;
    float _mapStartX;
    float _mapStartY;
    float _mapWidth;
    float _mapHeight;
    int _startX;
    int _startY;
    int _moveX;
    int _moveY;
    float _originX;
    float _originY;
    QList<float> _pathX;
    QList<float> _pathY;
};

#endif // T3_AF_MAP_H
