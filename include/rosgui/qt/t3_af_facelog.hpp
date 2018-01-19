#ifndef T3_AF_FACELOG_H
#define T3_AF_FACELOG_H

#include "t3_af_config.hpp"
#include <QDialog>

namespace Ui {
class T3_AF_faceLog;
}

class T3_AF_faceLog : public QDialog
{
  Q_OBJECT

public:
  explicit T3_AF_faceLog(QDialog *face, QWidget *parent = 0);
  ~T3_AF_faceLog();

    void exitToFace();

private Q_SLOTS:
    void timeUpdate();

private:
  Ui::T3_AF_faceLog *ui;
  QDialog *_face;
  void closeEvent(QCloseEvent *event);
  void keyPressEvent(QKeyEvent *event);
};

#endif // T3_AF_FACELOG_H
