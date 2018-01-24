#include "../../include/rosgui/qt/t3_af_vocaltext.hpp"
#include "ui_t3_af_vocaltext.h"

T3_AF_vocalText::T3_AF_vocalText(QWidget *parent) :
    T3Dialog(parent),
    ui(new Ui::T3_AF_vocalText)
{
    _father = new T3Dialog;
    ui->setupUi(this);
    this->setGeometry(0, 0, _father->_width_, _father->_height_);
//    this->move(0, 0);
//    this->resize(_father->_width_, _father->_height_);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->showFullScreen();
    ui->_exitPushBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_saveBtn_->setFocusPolicy(Qt::NoFocus);
    ui->_add_->setFocusPolicy(Qt::NoFocus);
    ui->_delete_->setFocusPolicy(Qt::NoFocus);
    //size
    ui->_backgroundLabel_->setGeometry(this->width()*0.4500,
                                       this->height()*0.0889,
                                       this->width()*0.5063,
                                       this->height()*0.8000);
    ui->_exitPushBtn_->setGeometry(this->width()*0.9000,
                                   this->height()*0.0889,
                                   this->width()*0.0488,
                                   this->height()*0.0556);
    ui->_exampleText_->setGeometry(this->width()*0.484,
                                   this->height()*0.1489,
                                   this->width()*0.4359,
                                   this->height()*0.3556);
    ui->_saveBtn_->setGeometry(this->width()*0.7875,
                              this->height()*0.7667,
                              this->width()*0.1000,
                              this->height()*0.0556);
    ui->_userTypeComboBox_->setGeometry(this->width()*0.6000,
                                       this->height()*0.5333,
                                       this->width()*0.1000,
                                       this->height()*0.0556);
    ui->_userTypeLabel_->setGeometry(this->width()*0.5125,
                                    this->height()*0.5333,
                                    this->width()*0.0688,
                                    this->height()*0.0444);
    ui->_voiceLabel_->setGeometry(this->width()*0.5125,
                                 this->height()*0.6444,
                                 this->width()*0.0688,
                                 this->height()*0.0444);
    ui->_voiceTextEdit_->setGeometry(this->width()*0.6000,
                                    this->height()*0.6444,
                                    this->width()*0.1500,
                                    this->height()*0.1778);
    ui->_add_->setGeometry(this->width()*0.1500,
                          this->height()*0.7778,
                          this->width()*0.0500,
                          this->height()*0.0889);
    ui->_back2_->setGeometry(this->width()*0.1000,
                             this->height()*0.0889,
                             this->width()*0.2525,
                             this->height()*0.8000);
    ui->_delete_->setGeometry(this->width()*0.2525,
                              this->height()*0.7778,
                              this->width()*0.0500,
                              this->height()*0.0889);
    ui->_groupName_->setGeometry(this->width()*0.1163,
                                 this->height()*0.7000,
                                 this->width()*0.2188,
                                 this->height()*0.0556);
    ui->_groups_->setGeometry(this->width()*0.1163,
                              this->height()*0.1489,
                              this->width()*0.2188,
                              this->height()*0.5200);
    //font
    QFont exitPushBtnLabel_;
    exitPushBtnLabel_.setPointSize(ui->_exitPushBtn_->height() * kBtnFontScal);
    ui->_exitPushBtn_->setFont(exitPushBtnLabel_);
    QFont exampleTextFont_;
    exampleTextFont_.setPointSize(ui->_exampleText_->height() * kLabelFontScal * 0.1);
    ui->_exampleText_->setFont(exampleTextFont_);
    QFont saveBtnFont_;
    saveBtnFont_.setPointSize(ui->_saveBtn_->height() * kBtnFontScal);
    ui->_saveBtn_->setFont(saveBtnFont_);
    QFont userTypeComboBoxFont_;
    userTypeComboBoxFont_.setPointSize(ui->_userTypeComboBox_->height() * kLabelFontScal * 0.6);
    ui->_userTypeComboBox_->setFont(userTypeComboBoxFont_);
    QFont userTypeLabelFont_;
    userTypeLabelFont_.setPointSize(ui->_userTypeLabel_->height() * kLabelFontScal * 0.8);
    ui->_userTypeLabel_->setFont(userTypeLabelFont_);
    QFont voiceLabelFont_;
    voiceLabelFont_.setPointSize(ui->_voiceLabel_->height() * kLabelFontScal * 0.8);
    ui->_voiceLabel_->setFont(voiceLabelFont_);
    QFont addFont_;
    QFont deleteFont_;
    QFont groupNameFont_;
    QFont groupsFont_;
    addFont_.setPointSize(ui->_add_->height() * kBtnFontScal * 0.5);
    deleteFont_.setPointSize(ui->_delete_->height() * kBtnFontScal * 0.5);
    groupNameFont_.setPointSize(ui->_groupName_->height() * kLabelFontScal * 0.5);
    groupsFont_.setPointSize(ui->_groups_->height() * kLabelFontScal / 10);
    ui->_add_->setFont(addFont_);
    ui->_delete_->setFont(deleteFont_);
    ui->_groupName_->setFont(groupNameFont_);
    ui->_groups_->setFont(groupsFont_);
    //

    initUserTypeComboBox();
    //func
    connect(ui->_exitPushBtn_, &QPushButton::clicked, this, &T3_AF_vocalText::exitVocalText);
//    QPropertyAnimation *animation_ = new QPropertyAnimation(this, "windowOpacity");
//    animation_->setDuration(50);
//    animation_->setStartValue(0);
//    animation_->setEndValue(0.9);
//    animation_->start();
    _network = T3_Face_Network::getT3FaceNetwork();
    //
    T3LOG("vocalText created");
}

void T3_AF_vocalText::exitVocalText()
{
    this->close();
    delete this;
}


void T3_AF_vocalText::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

void T3_AF_vocalText::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}

T3_AF_vocalText::~T3_AF_vocalText()
{
    delete ui;
    //
    T3LOG("vocalText deleted");
}

void T3_AF_vocalText::on__saveBtn__clicked()
{
    int userTypeIndex_ = ui->_userTypeComboBox_->currentIndex();
    QString TTSString_ = ui->_voiceTextEdit_->toPlainText();
    qDebug() << TTSString_;
    if(_network->_isNetworkConnected_)
    {
      _network->sendTTS(userTypeIndex_,TTSString_);
      T3_AF_warning *t3Warning = new T3_AF_warning(this,"更新成功",success);
      t3Warning->show();
      QSqlQuery query_;
      query_.prepare("update T3FaceUserType set voice = ? where id = ?");
      query_.bindValue(0,TTSString_);
      query_.bindValue(1,userTypeIndex_+1);
      query_.exec();

    }else
    {
      T3_AF_warning *t3Warning = new T3_AF_warning(this,"网络未连接，无法更新机器人语音数据");
      t3Warning->show();
    }


}

void T3_AF_vocalText::on__userTypeComboBox__currentIndexChanged(int index)
{
    qDebug() << index;
    QSqlQuery query_;
    query_.prepare("select voice from T3FaceUserType where id = ?");
    query_.bindValue(0,index + 1);
    query_.exec();
    query_.next();
    QString voice_ = query_.value(0).toString();
    ui->_voiceTextEdit_->setText(voice_);
}

void T3_AF_vocalText::initUserTypeComboBox()
{
  QSqlQuery query_;
  query_.exec("select UserType from T3FaceUserType");
  while(query_.next())
  {
    QString userType_ = query_.value(0).toString();
    ui->_userTypeComboBox_->addItem(userType_);
  }
}
