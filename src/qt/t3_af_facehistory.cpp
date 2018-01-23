#include "../../include/rosgui/qt/t3_af_facehistory.hpp"
#include "ui_t3_af_facehistory.h"

T3_AF_faceHistory::T3_AF_faceHistory(QWidget *parent) :
    T3Dialog(parent),
    ui(new Ui::T3_AF_faceHistory)
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
    ui->_faceInfoTableView_->setStyleSheet("background:transparent;border-width:0;color:white");
    ui->_faceInfoTableView_->horizontalHeader()->setStyleSheet("color:black");
    ui->_faceInfoTableView_->verticalHeader()->setStyleSheet("QHeaderView::section {background-color: rgba(232, 255, 213, 5);}");
    //size
    ui->_backgroungLabel_->setGeometry(this->width()*0.4625,
                                       this->height()*0.1556,
                                       this->width()*0.5063,
                                       this->height()*0.8000);
    ui->_exitPushBtn_->setGeometry(this->width()*0.9000,
                                   this->height()*0.1556,
                                   this->width()*0.0688,
                                   this->height()*0.0556);
    ui->_faceInfoTableView_->setGeometry(this->width()*0.4950,
                                         this->height()*0.2156,
                                         this->width()*0.4388,
                                         this->height()*0.6911);
    //font
    QFont exitPushBtnLabel_;
    exitPushBtnLabel_.setPointSize(ui->_exitPushBtn_->height() * kBtnFontScal);
    ui->_exitPushBtn_->setFont(exitPushBtnLabel_);
    QFont faceInfoTableViewFont_;
    faceInfoTableViewFont_.setPointSize(ui->_faceInfoTableView_->height() * kLabelFontScal / 20);
    ui->_faceInfoTableView_->setFont(faceInfoTableViewFont_);
    //func
    connect(ui->_exitPushBtn_, &QPushButton::clicked, this, &T3_AF_faceHistory::exitFaceHistory);
//    QPropertyAnimation *animation_ = new QPropertyAnimation(this, "windowOpacity");
//    animation_->setDuration(50);
//    animation_->setStartValue(0);
//    animation_->setEndValue(0.9);
//    animation_->start();
    //
    _model = new QSqlQueryModel(this);
    _model->setQuery("select * from T3FaceRecord limit 0,10");
    //_model->select();
    _model->setHeaderData(0,Qt::Horizontal,"记录编号");
    _model->setHeaderData(1,Qt::Horizontal,"身份编号");
    _model->setHeaderData(2,Qt::Horizontal,"姓名");
    _model->setHeaderData(4,Qt::Horizontal,"记录时间");
    //_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->_faceInfoTableView_->setModel(_model);

    ui->_faceInfoTableView_->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->_faceInfoTableView_->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->_faceInfoTableView_->setColumnHidden(3,true);
    ui->_faceInfoTableView_->resizeColumnsToContents();
    ui->_faceInfoTableView_->setEditTriggers(QAbstractItemView::NoEditTriggers);



    QHeaderView *header = ui->_faceInfoTableView_->horizontalHeader();
    header->setStretchLastSection(true);

    T3LOG("faceHis created");
}

void T3_AF_faceHistory::exitFaceHistory()
{
    this->close();
    delete this;
}

void T3_AF_faceHistory::closeEvent(QCloseEvent *event)
{
    event->ignore();
}


void T3_AF_faceHistory::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}

T3_AF_faceHistory::~T3_AF_faceHistory()
{
    delete ui;
    //
    T3LOG("faceHis deleted");
}
