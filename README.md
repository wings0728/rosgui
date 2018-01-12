# rosgui
## ros接口 v1.0
> 主要方法：
- public:
**构造函数：**QNode(int argc, char** argv );
**初始化：**bool init();
- 信号:
**ros关闭：**void rosShutdown();
    
**坐标点更新：**void poseUpdated();


> 使用方法：
- 包含qnode.hpp
- 创建一个对象：rosgui::qnode qnode;
- 调用qnode的构造函数时，需要传入argc和argv;
- 当有数据更新时，会有**signals：poseUpdated()**, 坐标点数组为**std::vector<double> _robotPose**;当信号被触发时，可以写一个槽来调用_robotPose，查看最新坐标点。
- 当ros被关闭时，会有**signals：rosShutdown()**，可以写对应的槽函数来做相应处理。
> example:
- hpp
```cpp
namespace Ui {
class T3_AF_welcome;
}

class T3_AF_welcome : public QDialog
{
    Q_OBJECT

public:
    explicit T3_AF_welcome(int argc, char** argv, QWidget *parent = 0);


private slots:
//--------------jason code
    void rosUpdate();
//--------------jason end
private:
    Ui::T3_AF_welcome *ui;
    rosgui::QNode qnode;
};
```
- cpp
```cpp
T3_AF_welcome::T3_AF_welcome(int argc, char** argv, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::T3_AF_welcome),
    qnode(argc,argv)
{
...
    //----------jason code
    qnode.init();
    QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));
    QObject::connect(&qnode, SIGNAL(poseUpdated()), this, SLOT(rosUpdate()));
    //----------jason end
...
}

void T3_AF_welcome::rosUpdate()
{
  T3LOG("%f %f %f",qnode._robotPose[0], qnode._robotPose[1], qnode._robotPose[2]);
}
```

