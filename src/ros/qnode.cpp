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

QNode::QNode()
{
  _robotPose.push_back(0.0);
  _robotPose.push_back(0.0);
  _robotPose.push_back(0.0);
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
	// Add your ros communications here.
	chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
  getParam(n);
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

void QNode::getParam(ros::NodeHandle n)
{
  //get param
  n.param("robotPoseTopicName", _robotPoseTopicName, std::string("/odometry/filtered_map"));
//  _robotPoseTopicName = "odometry/filtered_map";
  //get pose topic
  _robotPoseSub = n.subscribe(_robotPoseTopicName.c_str(), 100, &QNode::getPoseCallback, this);
//  ROS_WARN("set param");
  T3LOG(_robotPoseTopicName.c_str());
//  std::count << "set param" << std::endl;
}


void QNode::getPoseCallback(const nav_msgs::Odometry& msg)
{
  if(msg.header.frame_id == "")
  {
    ROS_WARN("Received initial pose with empty frame_id.  You should always supply a frame_id.");
  }
  tf::Pose currentPose_;
  tf::poseMsgToTF(msg.pose.pose, currentPose_);
  _robotPose[0] = currentPose_.getOrigin().x();
  _robotPose[1] = currentPose_.getOrigin().y();
  _robotPose[2] = currentPose_.getRotation().z();
  std::string pose;
//  pose += _robotPose[0];
//  pose += ", ";
//  pose += _robotPose[1];
//  pose += ", ";
//  pose += _robotPose[2];
//  pose = "123";
//  log(Info,pose);
//  std::count << "get pose" << std::endl;
//  T3LOG("%f",_robotPose[0]);
//  T3LOG("%f",_robotPose[1]);
//  T3LOG("%f",_robotPose[2]);
  Q_EMIT poseUpdated();
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

}  // namespace rosgui
