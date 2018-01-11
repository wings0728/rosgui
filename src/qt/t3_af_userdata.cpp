#include "../../include/rosgui/qt/t3_af_userdata.hpp"
#include "ui_t3_af_userdata.h"

//数据库界面构造
T3_AF_userData::T3_AF_userData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::T3_AF_userData)
{
    QSqlDatabase userDatabase_ = QSqlDatabase::addDatabase("QSQLITE");
    userDatabase_.setDatabaseName("T3_AF_userData");
    ui->setupUi(this);
    this->move(0, 0);
    ui->tableView->setStyleSheet("background:transparent;color:white");
//    ui->tableView->setStyleSheet("border-style:outset");
//    ui->tableView->setStyleSheet("color:rgb(7, 221, 225)");
    ui->tableView->setShowGrid(false);
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("userInfo");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);
    //日志
    T3LOG("++ 数据库界面构造");
}

//建立链接
bool T3_AF_userData::createConnection()
{
    QSqlDatabase userDatabase_ = QSqlDatabase::addDatabase("QSQLITE","connectToUserData");
    userDatabase_.setDatabaseName("T3_AF_userData");
    if(!userDatabase_.open())
    {
        T3LOG("userData创建失败");
        return false;
    }
    else
    {
        T3LOG("userData创建成功");
        return true;
    }
}

//断开链接
bool T3_AF_userData::removeConnection()
{
    QSqlDatabase::removeDatabase("connectToUserData");
    T3LOG("UserData断开链接");
    return true;
}

//创建表单
bool T3_AF_userData::createTable()
{
    QSqlDatabase userDatabase_ = QSqlDatabase::database("connectToUserData");
    QSqlQuery query(userDatabase_);
    bool success_ = query.exec("create table userInfo(userName QString primary key,"
                                                     "password QString)");
    if(success_)
    {
        T3LOG("tabel创建成功");
        return true;
    }
    else
    {
        T3LOG("tabel创建失败");
        return false;
    }
}

//插入行
bool T3_AF_userData::insert()
{
    QSqlDatabase userDatabase_ = QSqlDatabase::database("connectToUserData");
    QSqlQuery query(userDatabase_);
    query.exec("insert into userInfo values('cc', '666')");
    query.exec("insert into userInfo values('CHENCHEN', 'a000000A')");
    return true;
}

//查询全部
void T3_AF_userData::queryAll()
{
    QSqlDatabase userDatabase_ = QSqlDatabase::database("connectToUserData");
    QSqlQuery query(userDatabase_);
    query.exec("select * from userInfo");
    while(query.next())
    {
        qDebug() << query.value(0).toString()
                 << query.value(1).toString();
    }
}

//根据用户名查询
QSqlRecord T3_AF_userData::searchByUserName(QString user)
{
    QSqlDatabase userDatabase_ = QSqlDatabase::database("connectToUserData");
    QSqlQuery query(userDatabase_);

    query.prepare("select * from userInfo where userName = ?");
    query.addBindValue(user);
    query.exec();
    query.last();

    return query.record();
}

//界面析构
T3_AF_userData::~T3_AF_userData()
{
    delete ui;
    //日志
    T3LOG("-- 数据库界面析构");
}
