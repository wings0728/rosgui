/**
 * @file /include/rosgui/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef rosgui_QNODE_HPP_
#define rosgui_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <string>
#include <QThread>
#include <QStringListModel>
#include <vector>
#include <nav_msgs/Odometry.h>
#include "../qt/t3_af_config.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace rosgui {

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
  std::vector<double> _robotPose;
  std::vector<double> _mapOrigin;
  static QNode * getInstance();
  bool init(int argc, char** argv );
	void run();

	/*********************
	** Logging
	**********************/
	enum LogLevel {
	         Debug,
	         Info,
	         Warn,
	         Error,
	         Fatal
	 };

	QStringListModel* loggingModel() { return &logging_model; }
	void log( const LogLevel &level, const std::string &msg);

  void goalUpdate(float x, float y, float z);
  void operationMode(bool isManual = true);

Q_SIGNALS:
	void loggingUpdated();
    void rosShutdown();
    void poseUpdated();




private:
  int init_argc;
  char** init_argv;
	ros::Publisher chatter_publisher;
  ros::Publisher _robotGoal;
  ros::Subscriber _robotPoseSub;
    QStringListModel logging_model;
//    ros::NodeHandle _privateNh;
    std::string _robotPoseTopicName;
    QNode();
    virtual ~QNode();


//    bool init(const std::string &master_url, const std::string &host_url);

    void getParam(ros::NodeHandle& n);
    void getPoseCallback(const nav_msgs::Odometry& msg);
};

}  // namespace rosgui

#endif /* rosgui_QNODE_HPP_ */
