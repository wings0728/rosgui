#include "../../include/rosgui/qt/t3_af_maponly.hpp"
#include "ui_t3_af_maponly.h"

T3_AF_mapOnly::T3_AF_mapOnly(T3Dialog *map, QWidget *parent) :
    T3Dialog(parent),
    _map(map),
    ui(new Ui::T3_AF_mapOnly)
{
    //father
    _father = new T3Dialog;
    //basic settings
    ui->setupUi(this);
    this->setGeometry(0, 0, _father->_width_, _father->_height_);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->showFullScreen();
    //date/time update timer
    QTimer *timer_ = new QTimer(this);
    timer_->start(100);
    //low batt GIF
    QMovie *battLow_ = new QMovie(":/Pictures/batt_4.gif");
    battLow_->setScaledSize(QSize(ui->_battGIF_->width(), ui->_battGIF_->height()));
    battLow_->setSpeed(130);
    ui->_battGIF_->setMovie(battLow_);
    battLow_->start();
    //func
    connect(timer_, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    //initialization
    _qnode = rosgui::QNode::getInstance();
    _battInt = 0;
    _battQString = "";
    _mapIMG.load(":/Pictures/map_realMap.pgm");
    _mapWidthReal = ((float)(_mapIMG.width()))/20.0;
    _mapHeightReal = ((float)(_mapIMG.height()))/20.0;
    _Hcenter = this->width() * 0.5;
    _Vcenter = this->height() * 0.5;
    getMapGeometry();
    //LOG
    T3LOG("** mapOnly created");
}

///
/// \brief T3_AF_mapOnly::getMapGeometry --> get map x/y/width/height
///
void T3_AF_mapOnly::getMapGeometry()
{
    if(((this->width()) * 0.9 / _mapWidthReal) >= ((this->height() * 0.84) / _mapHeightReal))
    {
        _mapHeight = this->height() * 0.84;
        _scale = _mapHeight / _mapHeightReal;
        _mapWidth = _scale * _mapWidthReal;
        _mapX = _Vcenter - (_mapWidth / 2);
        _mapX = _Hcenter - (_mapHeight / 2);
        qDebug() << "switch 1";
    }
    else
    {
        _mapWidth = this->width() * 0.9;
        _scale = _mapWidth / _mapWidthReal;
        _mapHeight = _scale * _mapHeightReal;
        _mapX = _Vcenter - (_mapWidth / 2);
        _mapX = _Hcenter - (_mapHeight / 2);
    }
}

///
/// \brief T3_AF_mapOnly::lowBatt --> send low batt signal and turn robot to origin point
///
void T3_AF_mapOnly::lowBatt()
{
    emit lowBattSignal();
    //unfinished.
}

///
/// \brief T3_AF_mapOnly::battery --> show batt status
///
void T3_AF_mapOnly::battery()
{
    _battInt = _qnode->getBatt();
    _battQString = QString::number(_battInt) + "%";
    ui->_battery_->setText(_battQString);
    if(_battInt <= 30)
    {
        ui->_battIMG_->setStyleSheet("");
    }
    else if(_battInt > 30 && _battInt <= 60)
    {
        ui->_battIMG_->setStyleSheet("border-image:url(:/Pictures/batt_3.png)");
    }
    else if(_battInt > 60 && _battInt <= 90)
    {
        ui->_battIMG_->setStyleSheet("border-image:url(:/Pictures/batt_2.png)");
    }
    else if(_battInt > 90)
    {
        ui->_battIMG_->setStyleSheet("border-image:url(:/Pictures/batt_1.png)");
    }
    update();
}

///
/// \brief T3_AF_mapOnly::timeUpdate --> show time/date info
///
void T3_AF_mapOnly::timeUpdate()
{
    QDateTime dateTime_ = QDateTime::currentDateTime();
    QString dateTimeStr_ = dateTime_.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->_dateTimeLabel_->setText(dateTimeStr_);
}

void T3_AF_mapOnly::paintEvent(QPaintEvent *)
{
    QPainter paint_(this);
    paint_.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/Pictures/map_background.png"));
    paint_.drawPixmap(_mapX, _mapY, _mapWidth, _mapHeight, QPixmap(":/Pictures/map_realMap.pgm"));

}

void T3_AF_mapOnly::mousePressEvent(QMouseEvent *p)
{}

void T3_AF_mapOnly::mouseMoveEvent(QMouseEvent *m)
{}

void T3_AF_mapOnly::mouseReleaseEvent(QMouseEvent *r)
{}

void T3_AF_mapOnly::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case    Qt::Key_Escape:
        exit();
        break;
    default:
        QDialog::keyReleaseEvent(event);
    }
}

void T3_AF_mapOnly::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

void T3_AF_mapOnly::exit()
{
    _map->show();
    this->hide();
    delete this;
}

T3_AF_mapOnly::~T3_AF_mapOnly()
{
    delete ui;
    //log
    T3LOG("** mapOnly deleted");
}
