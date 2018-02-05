#include <ros/ros.h>
#include <iostream>
#include <sys/time.h>
#include <Eigen/Dense>
#include <DataLogger.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TransformStamped.h>

struct timeval ti, tf;
void tic(){
	gettimeofday(&ti, NULL);
}
unsigned long toc(){
	gettimeofday(&tf, NULL);
	return (tf.tv_sec-ti.tv_sec)*1e6 + tf.tv_usec-ti.tv_usec;
}

using namespace Eigen;
typedef Matrix<double, 7, 1> PoseVector;

PoseVector current_pose = PoseVector::Zero();
bool pose_updated = false;
void current_pose_cb(const geometry_msgs::TransformStamped::ConstPtr& msg)
{
	current_pose(0,0) = msg->transform.translation.x;
	current_pose(1,0) = msg->transform.translation.y;
	current_pose(2,0) = msg->transform.translation.z;
	current_pose(3,0) = msg->transform.rotation.x;
	current_pose(4,0) = msg->transform.rotation.y;
	current_pose(5,0) = msg->transform.rotation.z;
	current_pose(6,0) = msg->transform.rotation.w;
//	Matrix3d R = Matrix3d::Zero();
//	R(0,0) = q0*q0 + q1*q1 - q2*q2 - q3*q3;
//	R(0,1) = 2*(q1*q2-q0*q3);
//	R(0,2) = 2*(q1*q3+q0*q2);
//	R(1,0) = 2*(q1*q2+q0*q3);
//	R(1,1) = q0*q0 - q1*q1 + q2*q2 - q3*q3;
//	R(1,2) = 2*(q2*q3-q0*q1);
//	R(2,0) = 2*(q1*q3-q0*q2);
//	R(2,1) = 2*(q2*q3+q0*q1);
//	R(2,2) = q0*q0 - q1*q1 - q2*q2 + q3*q3;
//	current_pose(3,0) = atan2(R(2,1),R(2,2));
//	current_pose(4,0) = atan2(-R(2,0),sqrt(R(2,1)*R(2,1)+R(2,2)*R(2,2)));
//	current_pose(5,0) = atan2(R(1,0),R(0,0));
	pose_updated = true;
}
void current_pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
	current_pose(0,0) = msg->pose.position.x;
	current_pose(1,0) = msg->pose.position.y;
	current_pose(2,0) = msg->pose.position.z;
	current_pose(3,0) = msg->pose.orientation.x;
	current_pose(4,0) = msg->pose.orientation.y;
	current_pose(5,0) = msg->pose.orientation.z;
	current_pose(6,0) = msg->pose.orientation.w;
	pose_updated = true;
}
void current_pose_cb(const geometry_msgs::Pose::ConstPtr& msg)
{
	current_pose(0,0) = msg->position.x;
	current_pose(1,0) = msg->position.y;
	current_pose(2,0) = msg->position.z;
	current_pose(3,0) = msg->orientation.x;
	current_pose(4,0) = msg->orientation.y;
	current_pose(5,0) = msg->orientation.z;
	current_pose(6,0) = msg->orientation.w;
	pose_updated = true;
}

int main(int argc, char **argv)
{

	SYD::DataLogger *logger = new SYD::DataLogger();	

	ros::init(argc, argv, "data_logger");
	ros::NodeHandle nh;
	std::string pose = "/divo/pose";
//	ros::Subscriber current_pose_sub = nh.subscribe<geometry_msgs::TransformStamped>("vicon/lsi_asus/lsi_asus", 10, &current_pose_cb);
	ros::Subscriber current_pose_sub = nh.subscribe<geometry_msgs::Pose>(pose, 10, &current_pose_cb);

	unsigned long time;
	while(ros::ok())
	{
		ros::spinOnce();
		time = toc();
		if(pose_updated) logger->addLine(current_pose, time);
		pose_updated = false;
	}

	delete logger;
	return 0;
}
