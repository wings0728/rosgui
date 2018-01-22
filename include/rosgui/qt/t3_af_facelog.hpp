#ifndef T3_AF_FACELOG_H
#define T3_AF_FACELOG_H

#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QFileDialog>
#include "t3_af_config.hpp"
#include "T3Dialog.hpp"
#include "t3_face_faceengine.hpp"
#include "t3_af_warning.hpp"

namespace Ui {
class T3_AF_faceLog;
}

class T3_AF_faceLog : public T3Dialog
{
  Q_OBJECT

public:
  explicit T3_AF_faceLog(T3Dialog *face, QWidget *parent = 0);
  ~T3_AF_faceLog();

    void exitToFace();

private slots:
    void on__clearPushBtn__clicked();

private Q_SLOTS:
    void timeUpdate();
    void on__getImagePushBtn__clicked();
    void on__addNewUserPushBtn__clicked();
        void on__checkPushBtn__clicked();

private:
  Ui::T3_AF_faceLog *ui;
  T3Dialog *_face;
  void closeEvent(QCloseEvent *event);
  void keyPressEvent(QKeyEvent *event);
  T3Dialog *_father;
  FaceEngine *_faceEngine;
  QByteArray _feature;
  T3_AF_warning *_t3AFWarning;
  QSqlTableModel *_model;
  int _ret;
  bool _readyAddNewFace = false;
};

#endif // T3_AF_FACELOG_H
