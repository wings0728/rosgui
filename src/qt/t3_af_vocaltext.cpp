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
    //
    ui->_userTypeComboBox_->addItem("领导");
    ui->_userTypeComboBox_->addItem("访客");
    ui->_userTypeComboBox_->addItem("测试人员");
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
    T3LOG("vocalText deleted")
}

void T3_AF_vocalText::on__saveBtn__clicked()
{
    int userTypeIndex_ = ui->_userTypeComboBox_->currentIndex();
    QString TTSString_ = ui->_voiceTextEdit_->toPlainText();
    qDebug() << TTSString_;
    _network->sendTTS(userTypeIndex_,TTSString_);
}
