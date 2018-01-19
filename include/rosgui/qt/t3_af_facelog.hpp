#ifndef T3_AF_FACELOG_H
#define T3_AF_FACELOG_H

#include "t3_af_config.hpp"
#include "T3Dialog.hpp"

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

private Q_SLOTS:
    void timeUpdate();

private:
  Ui::T3_AF_faceLog *ui;
  T3Dialog *_face;
  void closeEvent(QCloseEvent *event);
  void keyPressEvent(QKeyEvent *event);
  T3Dialog *_father;
};

#endif // T3_AF_FACELOG_H
