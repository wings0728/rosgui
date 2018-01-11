#ifndef T3_AF_MAP_H
#define T3_AF_MAP_H

#include "t3_af_config.hpp"
#include <QDialog>

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

private slots:
    void timeUpdate();

private:
    Ui::T3_AF_map *ui;
    QDialog *_mainWindow;
    void paintEvent(QPaintEvent *event);
};

#endif // T3_AF_MAP_H
