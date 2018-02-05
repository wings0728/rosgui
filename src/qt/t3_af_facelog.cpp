#include "../../include/rosgui/qt/t3_af_facelog.hpp"
#include "ui_t3_af_facelog.h"

//界面构造函数
T3_AF_faceLog::T3_AF_faceLog(T3Dialog *face, QWidget *parent) :
    T3Dialog(parent),
    ui(new Ui::T3_AF_faceLog),
    _face(face)
{
    _father = new T3Dialog;
    //界面布局初始化
    ui->setupUi(this);
    this->move(0, 0);
    this->resize(_father->_width_, _father->_height_);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    this->showFullScreen();
    _deletePushBtn_ = new QPushButton(this);
    _deletePushBtn_->setFocusPolicy(Qt::NoFocus);
    _deletePushBtn_->setStyleSheet("border-image:url(:/Pictures/faceLog_button.png);color:white");
    _deletePushBtn_->show();
    ui->_getImagePushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_checkPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_clearPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_exitPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_addNewUserPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_faceInfoTableView_->setStyleSheet("background:transparent;border-width:0;color:white");
    ui->_faceInfoTableView_->horizontalHeader()->setStyleSheet("color:black");
    ui->_faceInfoTableView_->verticalHeader()->setStyleSheet("QHeaderView::section {background-color: rgba(232, 255, 213, 5);}");
    //size
    ui->_addNewUserPushBtn_->setGeometry(this->width()*0.9375,
                                         this->height()*0.556,
                                         this->width()*0.0375,
                                         this->height()*0.0667);
    ui->_addUserBackgroundLabel_->setGeometry(this->width()*0.6313,
                                              this->height()*0.0000,
                                              this->width()*0.3688,
                                              this->height()*0.6022);
    ui->_ageLabel->setGeometry(this->width()*0.6438,
                               this->height()*0.2711,
                               this->width()*0.0625,
                               this->height()*0.0889);
    ui->_ageLineEdit_->setGeometry(this->width()*0.7000,
                                   this->height()*0.2822,
                                   this->width()*0.0938,
                                   this->height()*0.0556);
    ui->_backgroundLabel_->setGeometry(this->width()*0.0000,
                                       this->height()*0.0000,
                                       this->width()*1.0000,
                                       this->height()*1.0000);
    ui->_checkPushBtn_->setGeometry(this->width()*0.7344,
                                    this->height()*0.8711,
                                    this->width()*0.0500,
                                    this->height()*0.0889);
    ui->_clearPushBtn_->setGeometry(this->width()*0.8125,
                                    this->height()*0.8711,
                                    this->width()*0.0500,
                                    this->height()*0.0889);
    _deletePushBtn_->setGeometry(this->width()*0.8906,
                                 this->height()*0.8711,
                                 this->width()*0.0500,
                                 this->height()*0.0889);
    ui->_dateTimeLabel_->setGeometry(this->width()*0.3900,
                                     this->height()*0.9467,
                                     this->width()*0.2300,
                                     this->height()*0.0467);
    ui->_exitPushBtn_->setGeometry(this->width()*0.9625,
                                   this->height()*0.0044,
                                   this->width()*0.0363,
                                   this->height()*0.0556);
    ui->_getImagePushBtn_->setGeometry(this->width()*0.8875,
                                       this->height()*0.5556,
                                       this->width()*0.0375,
                                       this->height()*0.0667);
    ui->_imageAddressLineEdit_->setGeometry(this->width()*0.7000,
                                            this->height()*0.5489,
                                            this->width()*0.1538,
                                            this->height()*0.0556);
    ui->_imageLabel_->setGeometry(this->width()*0.6438,
                                  this->height()*0.5378,
                                  this->width()*0.0625,
                                  this->height()*0.0889);
    ui->_nameLabel_->setGeometry(this->width()*0.6438,
                                 this->height()*0.1400,
                                 this->width()*0.0625,
                                 this->height()*0.0889);
    ui->_nameLineEdit_->setGeometry(this->width()*0.7000,
                                    this->height()*0.1511,
                                    this->width()*0.0938,
                                    this->height()*0.0556);
    ui->_searchByNameLabel_->setGeometry(this->width()*0.6438,
                                         this->height()*0.7556,
                                         this->width()*0.0625,
                                         this->height()*0.0889);
    ui->_searchByNameLineEdit_->setGeometry(this->width()*0.7063,
                                            this->height()*0.7556,
                                            this->width()*0.2624,
                                            this->height()*0.0889);
    ui->_userImageLabel_->setGeometry(this->width()*0.8295,
                                      this->height()*0.018,
                                      this->width()*0.1300,
                                      this->height()*0.3100);
    ui->_userTypeLabel_->setGeometry(this->width()*0.6438,
                                     this->height()*0.4044,
                                     this->width()*0.1000,
                                     this->height()*0.0889);
    ui->_userTypeComboBox_->setGeometry(this->width()*0.7438,
                                        this->height()*0.4156,
                                        this->width()*0.2013,
                                        this->height()*0.0556);
    ui->_faceInfoTableView_->setGeometry(this->width() * 0.0413,
                                         this->height() * 0.0733,
                                         this->width() * 0.5488,
                                         this->height() * 0.8644);
    ui->_battery_->setGeometry(this->width()*0.438,
                               this->height()*0.944,
                               this->width()*0.0613,
                               this->height()*0.0467);
    ui->_battIMG_->setGeometry(this->width()*0.33,
                               this->height()*0.962,
                               this->width()*0.1012,
                               this->height()*0.0284);
    ui->_battGIF_->setGeometry(this->width()*0.33,
                               this->height()*0.962,
                               this->width()*0.1012,
                               this->height()*0.0284);
    QMovie *battLow_ = new QMovie(":/Pictures/batt_4.gif");
    battLow_->setScaledSize(QSize(ui->_battGIF_->width(), ui->_battGIF_->height()));
    battLow_->setSpeed(130);
    ui->_battGIF_->setMovie(battLow_);
    battLow_->start();
    QFont battFont_;
    battFont_.setPointSize(ui->_battery_->height() * kLabelFontScal * 0.6);
    ui->_battery_->setFont(battFont_);

    ui->_userTypeComboBox_->setFocusPolicy(Qt::NoFocus);
    _deletePushBtn_->setText("删除");
    //数据库显示设置
    _model = new QSqlTableModel(this);
    //_model = new QSqlQueryModel(this);
    _model->setTable("T3Face");
    _model->select();
    _model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    _model->setHeaderData(0,Qt::Horizontal,"编号");
    _model->setHeaderData(1,Qt::Horizontal,"姓名");
    _model->setHeaderData(2,Qt::Horizontal,"角色");
    _model->setHeaderData(3,Qt::Horizontal,"年龄");
    _model->setHeaderData(5,Qt::Horizontal,"账户状态");
    _model->setHeaderData(6,Qt::Horizontal,"记录次数");
    _model->setHeaderData(7,Qt::Horizontal,"修改时间");
    ui->_faceInfoTableView_->setModel(_model);
    ui->_faceInfoTableView_->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->_faceInfoTableView_->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->_faceInfoTableView_->resizeColumnsToContents();
    ui->_faceInfoTableView_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->_faceInfoTableView_->setColumnHidden(0,true);
    ui->_faceInfoTableView_->setColumnHidden(4,true);
    QHeaderView *header = ui->_faceInfoTableView_->horizontalHeader();
    header->setStretchLastSection(true);
    QRegExp regx_("[0-9]+$");
    ui->_ageLineEdit_->setValidator(new QRegExpValidator(regx_, ui->_ageLineEdit_));
    //font
    QFont ageLabelFont_;
    ageLabelFont_.setPointSize(ui->_ageLabel->height() * kLabelFontScal * 0.5);
    QFont ageLineEditFont_;
    ageLineEditFont_.setPointSize(ui->_ageLineEdit_->height() * kLabelFontScal * 0.8);
    QFont checkPushBtnFont_;
    checkPushBtnFont_.setPointSize(ui->_checkPushBtn_->height() * kBtnFontScal * 0.5);
    QFont clearPushBtnFont_;
    clearPushBtnFont_.setPointSize(ui->_clearPushBtn_->height() * kBtnFontScal * 0.5);
    QFont deletePushBtnFont_;
    deletePushBtnFont_.setPointSize(_deletePushBtn_->height() * kBtnFontScal * 0.5);
    QFont dateTimeLabelFont_;
    dateTimeLabelFont_.setPointSize(ui->_dateTimeLabel_->height() * kLabelFontScal * 0.6);
    QFont imageAddressLineEditFont_;
    imageAddressLineEditFont_.setPointSize(ui->_imageAddressLineEdit_->height() * kLabelFontScal * 0.6);
    QFont imageLabelFont_;
    imageLabelFont_.setPointSize(ui->_imageLabel_->height() * kLabelFontScal * 0.5);
    QFont nameLabelFont_;
    nameLabelFont_.setPointSize(ui->_nameLabel_->height() * kLabelFontScal * 0.5);
    QFont nameLineEditFont_;
    nameLineEditFont_.setPointSize(ui->_nameLineEdit_->height() * kLabelFontScal * 0.8);
    QFont searchByNameLabelFont_;
    searchByNameLabelFont_.setPointSize(ui->_searchByNameLabel_->height() * kLabelFontScal * 0.5);
    QFont searchByNameLineEditFont_;
    searchByNameLineEditFont_.setPointSize(ui->_searchByNameLineEdit_->height() * kLabelFontScal * 0.5);
    QFont userTypeLabelFont_;
    userTypeLabelFont_.setPointSize(ui->_userTypeLabel_->height() * kLabelFontScal * 0.5);
    QFont userTypeComboBoxFont_;
    userTypeComboBoxFont_.setPointSize(ui->_userTypeComboBox_->height() * kLabelFontScal * 0.8);
    ui->_ageLabel->setFont(ageLabelFont_);
    ui->_ageLineEdit_->setFont(ageLineEditFont_);
    ui->_checkPushBtn_->setFont(checkPushBtnFont_);
    ui->_clearPushBtn_->setFont(clearPushBtnFont_);
    _deletePushBtn_->setFont(deletePushBtnFont_);
    ui->_dateTimeLabel_->setFont(dateTimeLabelFont_);
    ui->_imageAddressLineEdit_->setFont(imageAddressLineEditFont_);
    ui->_imageLabel_->setFont(imageLabelFont_);
    ui->_nameLabel_->setFont(nameLabelFont_);
    ui->_nameLineEdit_->setFont(nameLineEditFont_);
    ui->_searchByNameLabel_->setFont(searchByNameLabelFont_);
    ui->_searchByNameLineEdit_->setFont(searchByNameLineEditFont_);
    ui->_userTypeLabel_->setFont(userTypeLabelFont_);
    ui->_userTypeComboBox_->setFont(userTypeComboBoxFont_);
    //
    _qnode = rosgui::QNode::getInstance();
    _battInt = 0;
    _battQString = "";


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
    connect(ui->_exitPushBtn_, &QPushButton::clicked, this, &T3_AF_faceLog::exitToFace);
    connect(_deletePushBtn_,&QPushButton::clicked,this,&T3_AF_faceLog::deletePushBtn__clicked);
    //人脸识别引擎
    _faceEngine = new FaceEngine();
    _network = T3_Face_Network::getT3FaceNetwork();
    //相关控件设置初始化
    initUserTypeComboBox();
    //日志
    T3LOG("9+ 人脸日志界面构造");
    //connect(_qnode, SIGNAL(lowPower()), this, SLOT(lowBatt()));
}

//void T3_AF_faceLog::lowBatt()
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
void T3_AF_faceLog::timeUpdate()
{
    QDateTime dateTime_ = QDateTime::currentDateTime();
    QString dataTimeStr_ = dateTime_.toString("yyyy-MM-dd hh:mm:ss dddd");
    //QString timeStr_ = dateTime_.toString("hh:mm");
    ui->_dateTimeLabel_->setText(dataTimeStr_);
    //ui->_timeLabel_->setText(timeStr_);
}

//exitToFace
void T3_AF_faceLog::exitToFace()
{
    _face->show();

    for(int idx = 0; idx < kDelay; idx++){}

    this->close();
    delete this;
}

void T3_AF_faceLog::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

void T3_AF_faceLog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        exitToFace();
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}

//界面析构函数
T3_AF_faceLog::~T3_AF_faceLog()
{
    delete ui;
    delete _deletePushBtn_;
    //日志
    T3LOG("9- 人脸日志界面析构");
}

void T3_AF_faceLog::on__addNewUserPushBtn__clicked()
{
    QString name_ = ui->_nameLineEdit_->displayText();
    if(name_ == "")
    {
        _readyAddNewFace = false;
    }
    int age_ = ui->_ageLineEdit_->displayText().toInt();
    QString role_ = ui->_userTypeComboBox_->currentText();
    if(role_ == "")
    {
        _readyAddNewFace = false;
    }

    if(_readyAddNewFace)
    {
        QSqlQuery query_;
        query_.prepare("insert into T3Face values(NULL,?,?,?,?,?,?,?)");

        query_.bindValue(0,name_);

        query_.bindValue(1,role_);
        query_.bindValue(2,age_);
        query_.bindValue(3,_feature,QSql::Binary);
        query_.bindValue(4,1);//帐号状态：1表示活跃账户。
        query_.bindValue(5,0);//记录次数：初始化的时候为0。
        QString dateTime_ = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        query_.bindValue(6,dateTime_);
        bool succ = query_.exec();
        if(succ)
        {
          T3LOG("success add new faceInfo.");
          _t3AFWarning = new T3_AF_warning(this,"人员信息添加成功",success);
          _t3AFWarning->show();
          ui->_nameLineEdit_->clear();
          ui->_ageLineEdit_->clear();
          ui->_userImageLabel_->setStyleSheet("");
          ui->_imageAddressLineEdit_->clear();
          name_ = "";
          age_ = NULL;
          role_ = "";
          on__clearPushBtn__clicked();
          if(_network->_isNetworkConnected_)
          {
            _network->updateClientDataBase();
          }

        }

    }else
    {
      _t3AFWarning = new T3_AF_warning(this,"信息未填写完整，请补充完整后在提交");
      _t3AFWarning->show();
    }

}

void T3_AF_faceLog::on__getImagePushBtn__clicked()
{
  QImage _faceimage;
  QString filePath = QFileDialog::getOpenFileName(this,tr("Open file"),"/home",tr("Images (*.jpg)"));
  if(filePath != "")
  {
      _faceimage.load(filePath);
      QString _path = "border-image:url(" + filePath + ")";
      qDebug() << _path;
      ui->_userImageLabel_->setStyleSheet(_path);
      AFR_FSDK_FACEMODEL faceModel_ = {0};
      _ret = _faceEngine->getFaceFeatureFromImage(_faceimage,&faceModel_);
      qDebug() << _ret;
      if(_ret == 1)
      {

        _feature.resize(faceModel_.lFeatureSize);
        memcpy(_feature.data(),faceModel_.pbFeature,faceModel_.lFeatureSize);
        _readyAddNewFace = true;
        ui->_imageAddressLineEdit_->setText(filePath);
      }else
      {

          ui->_userImageLabel_->setStyleSheet("");
          _t3AFWarning = new T3_AF_warning(this,"当前图片无法正确识别，请更换图片");
          _t3AFWarning->show();
      }
  }
}

void T3_AF_faceLog::on__checkPushBtn__clicked()
{
  QString name_ = ui->_searchByNameLineEdit_->text();
  _model->setFilter(QString("name = '%1'").arg(name_));
  _model->select();
  ui->_faceInfoTableView_->setColumnHidden(4,true);
}

void T3_AF_faceLog::on__clearPushBtn__clicked()
{
  _model->setTable("T3Face");
  _model->select();
  _model->setEditStrategy(QSqlTableModel::OnManualSubmit);
  _model->setHeaderData(0,Qt::Horizontal,"编号");
  _model->setHeaderData(1,Qt::Horizontal,"姓名");
  _model->setHeaderData(2,Qt::Horizontal,"角色");
  _model->setHeaderData(3,Qt::Horizontal,"年龄");
  _model->setHeaderData(5,Qt::Horizontal,"账户状态");
  _model->setHeaderData(6,Qt::Horizontal,"记录次数");
  _model->setHeaderData(7,Qt::Horizontal,"修改时间");
  ui->_faceInfoTableView_->setModel(_model);
  ui->_faceInfoTableView_->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->_faceInfoTableView_->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->_faceInfoTableView_->resizeColumnsToContents();
  ui->_faceInfoTableView_->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->_faceInfoTableView_->setColumnHidden(0,true);
  ui->_faceInfoTableView_->setColumnHidden(4,true);
  ui->_searchByNameLineEdit_->clear();
}


void T3_AF_faceLog::battery()
{
    _battInt = _qnode->getBatt();
    _battQString = QString::number(_battInt) + "%";
    ui->_battery_->setText(_battQString);
    if(_battInt <= 30)
    {
        ui->_battIMG_->setStyleSheet("");
        ui->_battery_->setStyleSheet("color:rgb(252,34,32)");
    }
    else if(_battInt > 30 && _battInt <= 60)
    {
        ui->_battIMG_->setStyleSheet("border-image:url(:/Pictures/batt_3.png)");
        ui->_battery_->setStyleSheet("color:rgb(254,249,19)");
    }
    else if(_battInt > 60 && _battInt <= 90)
    {
        ui->_battIMG_->setStyleSheet("border-image:url(:/Pictures/batt_2.png)");
        ui->_battery_->setStyleSheet("color:rgb(46,254,19)");
    }
    else if(_battInt > 90)
    {
        ui->_battIMG_->setStyleSheet("border-image:url(:/Pictures/batt_1.png)");
        ui->_battery_->setStyleSheet("color:rgb(46,254,19)");
    }
    update();
}

void T3_AF_faceLog::paintEvent(QPaintEvent *)
{
    battery();
}

void T3_AF_faceLog::deletePushBtn__clicked()
{
  int curRow_ = ui->_faceInfoTableView_->currentIndex().row();
  QModelIndex index = _model->index(curRow_,0);
  QVariant data = _model->data(index);
  _model->removeRow(curRow_);
  _model->submitAll();
  if(_network->_isNetworkConnected_)
  {
    _network->sendDeteleFaceInfoById(data.toInt());
  }
}

void T3_AF_faceLog::initUserTypeComboBox()
{
  QSqlQuery query_;
  query_.exec("select UserType from T3FaceUserType");
  while(query_.next())
  {
    QString userType_ = query_.value(0).toString();
    if(userType_!="未注册")
    {
      ui->_userTypeComboBox_->addItem(userType_);
    }

  }
}
