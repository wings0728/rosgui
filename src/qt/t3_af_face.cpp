#include "../../include/rosgui/qt/t3_af_face.hpp"
#include "ui_t3_af_face.h"



//界面构造函数
T3_AF_face::T3_AF_face(T3Dialog *mainWindow, QWidget *parent) :
    T3Dialog(parent),
    _mainWindow(mainWindow),
    ui(new Ui::T3_AF_face)
{
    _father = new T3Dialog;
    //界面布局初始化
    ui->setupUi(this);
    this->setGeometry(0, 0, _father->_width_, _father->_height_);
//    this->move(0, 0);
//    this->resize(_father->_width_, _father->_height_);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    this->showFullScreen();
    _stopPushBtn_ = new QPushButton(this);
    _stopPushBtn_->setFocusPolicy(Qt::NoFocus);
    _stopPushBtn_->setStyleSheet("QPushButton{border-image:url(:/Pictures/mainWindow_stop.png);}"
                                 "QPushButton:pressed{border-image:url(:/Pictures/mainWindow_stop2.png);}");
    _stopPushBtn_->show();
    _stopPushBtn_->setText("");
    ui->_dateLabel_->setText("");
    ui->_dateLabel_->setStyleSheet("color:white");
    ui->_timeLabel_->setText("");
    ui->_timeLabel_->setStyleSheet("color:white");
    ui->_exitPushBtn_->setText("");
    ui->_exitPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_exitPushBtn_->setStyleSheet("border-image:url(:/Pictures/face_back.png)");
    ui->_faceGifLabel_->setText("");
    ui->_faceGifLabel_->setStyleSheet("border-image:url(:/Pictures/face_gif.png)");
    ui->_textLabel_->setText("");
    ui->_textLabel_->setStyleSheet("border-image:url(:/Pictures/face_text.png)");
    ui->_squareLabel_->setText("");
    ui->_squareLabel_->setStyleSheet("border-image:url(:/Pictures/face_square.png)");
    ui->_videoLabel_->setText("");
    ui->_videoLabel_->setStyleSheet("color:white");
    ui->_logBackgroundLabel_->setText("");
    ui->_logBackgroundLabel_->setStyleSheet("border-image:url(:/Pictures/face_logBackground.png)");
    ui->_morePushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_enterFaceLogPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_vocalPushBtn_->setFocusPolicy(Qt::NoFocus);
    //size
    ui->_dateLabel_->setGeometry(this->width()*0.0688,
                                 this->height()*0.0667,
                                 this->width()*0.1625,
                                 this->height()*0.0667);
    ui->_enterFaceLogPushBtn_->setGeometry(this->width()*0.7625,
                                           this->height()*0.1444,
                                           this->width()*0.1538,
                                           this->height()*0.0622);
    ui->_exitPushBtn_->setGeometry(this->width()*0.9313,
                                   this->height()*0.0178,
                                   this->width()*0.0375,
                                   this->height()*0.0600);
    ui->_faceGifLabel_->setGeometry(this->width()*0.0375,
                                    this->height()*0.3111,
                                    this->width()*0.2000,
                                    this->height()*0.4222);
    ui->_logBackgroundLabel_->setGeometry(this->width()*0.7350,
                                          this->height()*0.2356,
                                          this->width()*0.2213,
                                          this->height()*0.5022);
    ui->_morePushBtn_->setGeometry(this->width()*0.8813,
                                   this->height()*0.2333,
                                   this->width()*0.0750,
                                   this->height()*0.0889);
    ui->_squareLabel_->setGeometry(this->width()*0.2875,
                                   this->height()*0.2333,
                                   this->width()*0.6688,
                                   this->height()*0.6000);
    ui->_textLabel_->setGeometry(this->width()*0.0375,
                                 this->height()*0.8000,
                                 this->width()*0.2000,
                                 this->height()*0.0889);
    ui->_timeLabel_->setGeometry(this->width()*0.0688,
                                 this->height()*0.1111,
                                 this->width()*0.1625,
                                 this->height()*0.1778);
    ui->_videoLabel_->setGeometry(this->width()*0.2888,
                                  this->height()*0.2356,
                                  this->width()*0.4463,
                                  this->height()*0.5933);
    _videoLabelHeight = this->height()*0.5933;
    _videoLabelWidth = this->width()*0.4463;
    ui->_vocalPushBtn_->setGeometry(this->width()*0.7875,
                                    this->height()*0.1556,
                                    this->width()*0.1000,
                                    this->height()*0.5956);
    ui->_vocalPushBtn_->setGeometry(this->width()*0.7625,
                                    this->height()*0.0600,
                                    this->width()*0.1538,
                                    this->height()*0.0622);
    ui->_logListView_->setGeometry(this->width()*0.7370,
                                   this->height()*0.32,
                                   this->width()*0.2160,
                                   this->height()*0.4200);
    ui->_headLabel_->setGeometry(this->width()*0.4300,
                                   this->height()*0.0444,
                                   this->width()*0.1400,
                                   this->height()*0.1489);
    _stopPushBtn_->setGeometry(this->width()*0.7500,
                               this->height()*0.75,
                               this->width()*0.1875,
                               this->height()*0.2000);
    ui->_battery_->setGeometry(this->width()*0.5993,
                               this->height()*0.91,
                               this->width()*0.0875,
                               this->height()*0.06);
    ui->_battIMG_->setGeometry(this->width()*0.3430,
                               this->height()*0.91,
                               this->width()*0.2375,
                               this->height()*0.06);
    ui->_battGIF_->setGeometry(this->width()*0.3430,
                               this->height()*0.91,
                               this->width()*0.2375,
                               this->height()*0.06);
    QMovie *battLow_ = new QMovie(":/Pictures/batt_4.gif");
    battLow_->setScaledSize(QSize(ui->_battGIF_->width(), ui->_battGIF_->height()));
    battLow_->setSpeed(130);
    ui->_battGIF_->setMovie(battLow_);
    battLow_->start();

    //font
    QFont dateLabelFont_;
    dateLabelFont_.setPointSize(ui->_dateLabel_->height() * kLabelFontScal*0.55);
    QFont timeLabelFont_;
    timeLabelFont_.setPointSize(ui->_timeLabel_->height() * kLabelFontScal*0.8);
    QFont vocalPushBtnFont_;
    vocalPushBtnFont_.setPointSize(ui->_vocalPushBtn_->height() * kBtnFontScal);
    QFont morePushBtnFont_;
    morePushBtnFont_.setPointSize(ui->_morePushBtn_->height() * kBtnFontScal * 0.7);
    QFont enterFaceLogPushBtnFont_;
    enterFaceLogPushBtnFont_.setPointSize(ui->_enterFaceLogPushBtn_->height() * kBtnFontScal);
    QFont logListViewFont_;
    logListViewFont_.setPointSize(ui->_logListView_->height() * kLabelFontScal / 10);

    ui->_dateLabel_->setFont(dateLabelFont_);
    ui->_timeLabel_->setFont(timeLabelFont_);
    ui->_vocalPushBtn_->setFont(vocalPushBtnFont_);
    ui->_morePushBtn_->setFont(morePushBtnFont_);
    ui->_enterFaceLogPushBtn_->setFont(enterFaceLogPushBtnFont_);
    ui->_logListView_->setFont(logListViewFont_);
    QFont battFont_;
    battFont_.setPointSize(ui->_battery_->height() * kLabelFontScal);
    ui->_battery_->setFont(battFont_);
    //界面浮现动画
//    QPropertyAnimation *animation_ = new QPropertyAnimation(this, "windowOpacity");
//    animation_->setDuration(150);
//    animation_->setStartValue(0);
//    animation_->setEndValue(1);
//    animation_->start();
    //定时器
    QTimer *timer_ = new QTimer(this);
    timer_->start(100);
    //链接ui部件与功能
    connect(timer_, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    connect(ui->_exitPushBtn_, &QPushButton::clicked, this, &T3_AF_face::exitToMainWindow);
    connect(ui->_enterFaceLogPushBtn_, &QPushButton::clicked, this, &T3_AF_face::enterFaceLog);
    connect(ui->_morePushBtn_, &QPushButton::clicked, this, &T3_AF_face::enterFaceHistory);
    connect(ui->_vocalPushBtn_, &QPushButton::clicked, this, &T3_AF_face::enterVocalText);
    connect(_stopPushBtn_, &QPushButton::clicked, this, &T3_AF_face::stopRobot);

    //视频展示
     _netWork = T3_Face_Network::getT3FaceNetwork();
     _decoder = _netWork->_decoder_;

     if(_netWork->_isNetworkConnected_)
     {
       _netWork->getVideo();
     }else
     {
            //T3_AF_warning *warning = new T3_AF_warning(this,"网络未连接");
            //warning->show();
            ui->_videoLabel_->setText("网络未连接，请检查网络");
     }
     connect(_netWork,&T3_Face_Network::networkDisconnect,this,&T3_AF_face::networkDisconnected);
     _frameLineData = _netWork->_frameLineData_;
     connect(_decoder,&Decoder::newFrame,this,&T3_AF_face::printVideo);
     connect(_netWork,&T3_Face_Network::getLog,this,&T3_AF_face::log);
     //数据库连接
     _database = QSqlDatabase::addDatabase(kDatabaseEngine);
     _database.setDatabaseName(kDatabaseName);
     _database.setHostName(kServerURL);
     _database.setUserName(kDatabaseUserName);
     _database.setPassword(kDatabasePassword);
     _database.open();

    //
     _qnode = rosgui::QNode::getInstance();
     _battQString = "";
     _battInt = 0;
    //日志
    T3LOG("5+ 人脸界面构造");
    //connect(_qnode, SIGNAL(lowPower()), this, SLOT(lowBatt()));
}

//void T3_AF_face::lowBatt()
//{
//    if(rosgui::QNode::Auto == _qnode->getOprationMode())
//    {
//        _qnode->goalUpdate(0.0, 0.0, 0.0);
//    }
//    else
//    {
//        _qnode->setManualCmd(rosgui::QNode::Stop);
//        _qnode->setOperationMode(rosgui::QNode::Auto);
//        _qnode->goalUpdate(0.0, 0.0, 0.0);
//    }
//}

//显示时间
void T3_AF_face::timeUpdate()
{
    QDateTime dateTime_ = QDateTime::currentDateTime();
    QString dataStr_ = dateTime_.toString("yyyy-MM-dd dddd");
    QString timeStr_ = dateTime_.toString("hh:mm");
    ui->_dateLabel_->setText(dataStr_);
    ui->_timeLabel_->setText(timeStr_);
}

//界面背景绘制
void T3_AF_face::paintEvent(QPaintEvent *)
{
    QPainter paint_(this);
    paint_.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/Pictures/face_background.png"));
    battery();
}
//退出
void T3_AF_face::exitToMainWindow()
{
    _mainWindow->show();
    if(_netWork->_isNetworkConnected_)
    {
      _netWork->closeVideo();
    }

    this->close();
    delete this;
}

void T3_AF_face::battery()
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


//enterFaceLog
void T3_AF_face::enterFaceLog()
{
    T3_AF_faceLog *faceLog_ = new T3_AF_faceLog(this);
    faceLog_->show();
    stopRobot();


    this->hide();
}

//enterFaceHistory
void T3_AF_face::enterFaceHistory()
{
    T3_AF_faceHistory *faceHistory_ = new T3_AF_faceHistory;
    faceHistory_->show();
    stopRobot();
}

void T3_AF_face::enterVocalText()
{
    T3_AF_vocalText *vocalText_ = new T3_AF_vocalText;
    vocalText_->show();
    stopRobot();
}

void T3_AF_face::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

void T3_AF_face::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        exitToMainWindow();
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}
//绘制视频
void T3_AF_face::printVideo(QImage faceImage)
{
  //faceImage = faceImage.mirrored(true,false);

  QPainter paint(&faceImage);
  QPen pen(Qt::yellow,2);
  paint.setPen(pen);
  paint.setFont(QFont(QString::fromLocal8Bit("宋体"),20,-1,false));
  //qDebug() << _frameLineData->personNum;
 for(int i = 0; i<_frameLineData->personNum; i++)
 {

     paint.drawLine(QPoint(_frameLineData->rightList[i],_frameLineData->topList[i]),QPoint(_frameLineData->leftList[i],_frameLineData->topList[i]));
     paint.drawLine(QPoint(_frameLineData->rightList[i],_frameLineData->bottomList[i]),QPoint(_frameLineData->leftList[i],_frameLineData->bottomList[i]));
     paint.drawLine(QPoint(_frameLineData->rightList[i],_frameLineData->topList[i]),QPoint(_frameLineData->rightList[i],_frameLineData->bottomList[i]));
     paint.drawLine(QPoint(_frameLineData->leftList[i],_frameLineData->topList[i]),QPoint(_frameLineData->leftList[i],_frameLineData->bottomList[i]));
     if(-1 != _frameLineData->idList[i])
     {
         QSqlQuery query_(_database);
         query_.prepare("select name from T3Face where id = ?");
         query_.bindValue(0, _frameLineData->idList[i]);

         query_.exec();
         query_.next();
         QString name_ = query_.value(0).toString();
         paint.drawText(QPointF(_frameLineData->dot2List[i]-1-(_frameLineData->rightList[i]-_frameLineData->leftList[i]),_frameLineData->dot1List[i]),name_);
     }

 }

  paint.end();
  faceImage = faceImage.scaled(_videoLabelWidth,_videoLabelHeight,Qt::KeepAspectRatio);
  ui->_videoLabel_->setPixmap(QPixmap::fromImage(faceImage));
}

void T3_AF_face::stopRobot()
{
    _qnode->setOperationMode(rosgui::QNode::Manual);
    _qnode->setManualCmd(rosgui::QNode::Stop);
}
void T3_AF_face::networkDisconnected()
{
  ui->_videoLabel_->clear();
  ui->_videoLabel_->setText("网络连接断开，请重新连接");
}

void T3_AF_face::log(int id)
{
  qDebug() << "log:" << id ;
  QSqlQuery query_;
  query_.prepare("select name from T3Face where id = ?");
  query_.bindValue(0,id);
  query_.exec();
  query_.next();
  QString name = query_.value(0).toString();
  QString time = QTime::currentTime().toString("hh:mm:ss");
  QString showString = time +"    "+ name;
  //记录日志展示
  if( 8 <=_strList.size())
  {
    _strList.removeAt(0);
  }
  _strList.append(showString);

  _stringListModel = new QStringListModel(_strList);
  ui->_logListView_->setModel(_stringListModel);
}

//界面析构函数
T3_AF_face::~T3_AF_face()
{
    delete ui;
    delete _stopPushBtn_;
    //日志
    T3LOG("5- 人脸界面析构");
}
