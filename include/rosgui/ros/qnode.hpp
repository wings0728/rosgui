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
#include "nav_msgs/Path.h"
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

  std::vector<double> getRobotPose();
  std::vector<double> getMapOrigin();
  bool getGlobalPlan(QList<std::pair<double, double> >& plan);

Q_SIGNALS:
	void loggingUpdated();
  void rosShutdown();
  void poseUpdated();
  void globalPlanGet();



private:
  int init_argc;
  char** init_argv;
	ros::Publisher chatter_publisher;
  ros::Publisher _robotGoal;
  ros::Subscriber _robotPoseSub;
  ros::Subscriber _globalPlanSub;
  QStringListModel logging_model;
  //robot pose
  std::vector<double> _robotPose;
  //map origin pose
  std::vector<double> _mapOrigin;
  QList<std::pair<double, double> > _globalPlan;
//    ros::NodeHandle _privateNh;
  std::string _robotPoseTopicName;
  std::string _globalPlanTopicName;
  QNode();
  virtual ~QNode();


//    bool init(const std::string &master_url, const std::string &host_url);

    void getParam(ros::NodeHandle& n);
    void getPoseCallback(const nav_msgs::Odometry& msg);
    void getGlobalPlanCallback(const nav_msgs::Path& pathMsg);
};

}  // namespace rosgui

#endif /* rosgui_QNODE_HPP_ */
