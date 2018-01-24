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
#include "rosgui/SensorState.h"
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

  enum OprationMode {
           Auto,
           Manual
   };

  enum ManualCmd {
           Forward,
           Backward,
           LeftTurn,
           RightTurn,
           Stop
   };

	QStringListModel* loggingModel() { return &logging_model; }
	void log( const LogLevel &level, const std::string &msg);
  void shutDownRos();

  bool goalUpdate(float x, float y, float z);
  void setOperationMode(OprationMode mode);

  std::vector<double> getRobotPose();
  std::vector<double> getMapOrigin();
  bool getGlobalPlan(QList<std::pair<double, double> >& plan);
  bool setManualCmd(ManualCmd cmd);
  OprationMode getOprationMode();
  int getBatt();
  void getRobotSpeed(double* linearX, double* anglarZ);
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
  ros::Publisher _cmdVelPub;
  ros::Publisher _checkNetPub;
  ros::Subscriber _robotPoseSub;
  ros::Subscriber _globalPlanSub;
  ros::Subscriber _batterySub;
  QStringListModel logging_model;
  //robot pose
  std::vector<double> _robotPose;
  //map origin pose
  std::vector<double> _mapOrigin;
  QList<std::pair<double, double> > _globalPlan;
//    ros::NodeHandle _privateNh;
  std::string _robotPoseTopicName;
  std::string _globalPlanTopicName;
  double _linearX;
  double _angularZ;
  double _OdomLinearX;
  double _OdomAngularZ;
  double _maxLinearX;
  double _maxAngularZ;
  int _battPer;

  OprationMode _oprationMode;
  QNode();
  virtual ~QNode();


//    bool init(const std::string &master_url, const std::string &host_url);
    void pubRobotSpeed();
    void getParam(ros::NodeHandle& n);
    void getPoseCallback(const nav_msgs::Odometry& msg);
    void getGlobalPlanCallback(const nav_msgs::Path& pathMsg);
    void getStateCallback(const rosgui::SensorState& msg);

};

}  // namespace rosgui

#endif /* rosgui_QNODE_HPP_ */
