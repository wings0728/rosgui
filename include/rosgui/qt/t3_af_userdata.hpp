#ifndef T3_AF_USERDATA_H
#define T3_AF_USERDATA_H

#include "t3_af_config.hpp"
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>

namespace Ui {
class T3_AF_userData;
}

class T3_AF_userData : public QDialog
{
    Q_OBJECT

public:
    explicit T3_AF_userData(QWidget *parent = 0);
    ~T3_AF_userData();

    bool createConnection();
    bool removeConnection();
    bool createTable();
    bool insert();
    void queryAll();
    QSqlRecord searchByUserName(QString user);

private:
    Ui::T3_AF_userData *ui;
};

#endif // T3_AF_USERDATA_H
