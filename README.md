# rosgui
## ros接口 v1.0
> 主要方法：
- public:

> `static QNode * getInstance();`
*获取单例对象*

> `bool init(int argc, char** argv);`
*初始化*

- 信号:

> `void rosShutdown();`
*ros系统关闭*
    
> `void poseUpdated();`
*坐标点更新*

> 使用方法：
- 包含qnode.hpp
- 创建一个单例对象：rosgui::QNode *qnode = rosgui::QNode::getInstance();
- 第一次创建单例时，需要调用init函数并传入argc、argv，所以一般在main中第一次创建**qnode->init(argc, argv)**;
- 第一次创建之后，其余类再创建时，可以直接使用**rosgui::QNode *qnode = rosgui::QNode::getInstance()**获取对象;
- 当有数据更新时，会有**signals：poseUpdated()**, 坐标点数组为**std::vector<double> _robotPose**;当信号被触发时，可以写一个槽来调用_robotPose，查看最新坐标点。
- 当ros被关闭时，会有**signals：rosShutdown()**，可以写对应的槽函数来做相应处理。
> example:
- 初始化(第一次调用)
```cpp
    rosgui::QNode *qnode = rosgui::QNode::getInstance();
    qnode->init(argc, argv);
```
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
    rosgui::QNode *qnode;
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
    qnode = rosgui::QNode::getInstance();
    QObject::connect(qnode, SIGNAL(rosShutdown()), this, SLOT(close()));
    QObject::connect(qnode, SIGNAL(poseUpdated()), this, SLOT(rosUpdate()));
    //----------jason end
...
}

void T3_AF_welcome::rosUpdate()
{
  T3LOG("%f %f %f",qnode->_robotPose[0], qnode->_robotPose[1], qnode->_robotPose[2]);
}
```

