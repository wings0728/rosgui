/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include "../../include/rosgui/ros/qnode.hpp"
#include <tf/tf.h>
#include "t3_description/goal.h"
#include "yaml-cpp/yaml.h"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace rosgui {

/*****************************************************************************
** Implementation
*****************************************************************************/

QNode * QNode::getInstance()
{
  static QNode qnode;
  return &qnode;
}

QNode::QNode():
  _mapOrigin(3, 0.0),
  _robotPose(4, 0.0)
{
}

QNode::~QNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
	wait();
}

bool QNode::init(int argc, char** argv ) {
  init_argc = argc;
  init_argv = argv;

  ros::init(init_argc,init_argv,"rosgui");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
  ros::NodeHandle pn("~");
	// Add your ros communications here.
	chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
  _robotGoal = n.advertise<t3_description::goal>("robotGoal", 100);
  getParam(pn);
	start();
	return true;
}

//bool QNode::init(const std::string &master_url, const std::string &host_url) {
//	std::map<std::string,std::string> remappings;
//	remappings["__master"] = master_url;
//	remappings["__hostname"] = host_url;
//	ros::init(remappings,"rosgui");
//	if ( ! ros::master::check() ) {
//		return false;
//	}
//	ros::start(); // explicitly needed since our nodehandle is going out of scope.
//	ros::NodeHandle n;
//	// Add your ros communications here.
//	chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
//  getParam(n);
//	start();
//	return true;
//}

void QNode::getParam(ros::NodeHandle& n)
{
//  double tempX;
  //get param
  n.param("robotPoseTopicName", _robotPoseTopicName, std::string("/odometry/filtered_map"));
  n.param("originX", _mapOrigin[0], 0.0);
  n.param("originY", _mapOrigin[1], 0.0);
  n.param("originZ", _mapOrigin[2], 0.0);

  qDebug() << "x:" << _mapOrigin[0] << " y:" << _mapOrigin[1] << " z:" << _mapOrigin[2];
//  std::string fname(init_argv[1]);
//  std::ifstream fin(fname.c_str());
//  if (fin.fail()) {
//    ROS_ERROR("Map_server could not open %s.", fname.c_str());
//    exit(-1);
//  }
//  YAML::Parser parser(fin);
//  YAML::Node doc;
//  parser.GetNextDocument(doc);
//  try {
//              doc["origin"][0] >> _mapOrigin[0];
//              doc["origin"][1] >> _mapOrigin[1];
//              doc["origin"][2] >> _mapOrigin[2];
//            } catch (YAML::InvalidScalar) {
//              ROS_ERROR("The map does not contain an origin tag or it is invalid.");
//              exit(-1);
//            }
//  _robotPoseTopicName = "odometry/filtered_map";
  //get pose topic
  _robotPoseSub = n.subscribe(_robotPoseTopicName.c_str(), 100, &QNode::getPoseCallback, this);
  _globalPlanSub = n.subscribe("TrajectoryPlannerROS/global_plan", 1000, &QNode::getGlobalPlanCallback, this);
//  ROS_WARN("set param");
//  T3LOG(_robotPoseTopicName.c_str());
//  std::count << "set param" << std::endl;
}

//**********************call back********************//

void QNode::getPoseCallback(const nav_msgs::Odometry& msg)
{
  if(msg.header.frame_id == "")
  {
    ROS_WARN("Received initial pose with empty frame_id.  You should always supply a frame_id.");
  }

  _robotPose[0] = msg.pose.pose.position.x;
  _robotPose[1] = msg.pose.pose.position.y;
  _robotPose[2] = msg.pose.pose.orientation.z;
  _robotPose[3] = msg.pose.pose.orientation.w;

  Q_EMIT poseUpdated();
}

///
/// \brief getGlobalPlanCallback
/// \param pathMsg
///
void QNode::getGlobalPlanCallback(const nav_msgs::Path& pathMsg)
{
  if(pathMsg.header.frame_id == "")
    {
      // This should be removed at some point
      ROS_WARN("Received path with empty frame_id.  You should always supply a frame_id.");
    }
  int pathSize = pathMsg.poses.size();
  std::vector<geometry_msgs::PoseStamped> path(pathSize);
  for(unsigned int i=0; i < pathSize; i++){
    path[i] = pathMsg.poses[i];
    ROS_INFO("%f %f",path[i].pose.position.x, path[i].pose.position.y);
  }
}

void QNode::run() {
	ros::Rate loop_rate(1);
//  int count = 0;
	while ( ros::ok() ) {

//    std_msgs::String msg;
//    std::stringstream ss;
//    ss << "hello world " << count;
//    msg.data = ss.str();
//    chatter_publisher.publish(msg);
//    log(Info,std::string("I sent: ")+msg.data);
		ros::spinOnce();
		loop_rate.sleep();
//		++count;
	}
	std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
	Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}


void QNode::log( const LogLevel &level, const std::string &msg) {
  logging_model.insertRows(logging_model.rowCount(),1);
  std::stringstream logging_model_msg;
  switch ( level ) {
    case(Debug) : {
        ROS_DEBUG_STREAM(msg);
        logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    case(Info) : {
        ROS_INFO_STREAM(msg);
        logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    case(Warn) : {
        ROS_WARN_STREAM(msg);
        logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    case(Error) : {
        ROS_ERROR_STREAM(msg);
        logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    case(Fatal) : {
        ROS_FATAL_STREAM(msg);
        logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
        break;
    }
  }
  QVariant new_row(QString(logging_model_msg.str().c_str()));
  logging_model.setData(logging_model.index(logging_model.rowCount()-1),new_row);
//  Q_EMIT loggingUpdated(); // used to readjust the scrollbar
  Q_EMIT poseUpdated();
}

///
/// \brief when goal update, publish it.
/// \param pose x
/// \param pose y
/// \param pose_oritation z
///
void QNode::goalUpdate(float x, float y, float z)
{
  t3_description::goal goalMsg_;
  goalMsg_.x = x;
  goalMsg_.y = y;
  goalMsg_.z = z;
  _robotGoal.publish(goalMsg_);
}
///
/// \brief QNode::operationMode
/// \param isManual
///
void QNode::operationMode(bool isManual)
{
    qDebug() << isManual;
}

//***********************get set*********************//
std::vector<double> QNode::getRobotPose()
{
  std::vector<double> tempPose(_robotPose);
  return tempPose;
}

std::vector<double> QNode::getMapOrigin()
{
  std::vector<double> tempOrigin(_mapOrigin);
  return tempOrigin;
}

}  // namespace rosgui


