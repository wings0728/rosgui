#ifndef T3_AF_WEATHERFORECAST_H
#define T3_AF_WEATHERFORECAST_H

#include "t3_af_config.hpp"
#include <QDialog>

namespace Ui {
class T3_AF_weatherForecast;
}

class T3_AF_weatherForecast : public QDialog
{
    Q_OBJECT

public:
    explicit T3_AF_weatherForecast(QDialog *mainWindow, QWidget *parent = 0);
    ~T3_AF_weatherForecast();

    void exitToMainWindow();

private slots:
    void timeUpdate();

private:
    Ui::T3_AF_weatherForecast *ui;
    QDialog *_mainWindow;
    void paintEvent(QPaintEvent *event);
};

#endif // T3_AF_WEATHERFORECAST_H
