#include "ros/ros.h"
#include <bits/stdc++.h>
#include <sstream>
#include "learn_msg_filter/NewString.h"


int main(int argc, char** argv) {

	ros::init(argc, argv, "secondNode");
	ros::NodeHandle nh;
	ROS_INFO_STREAM("Second Node started");

	ros::Publisher pub = nh.advertise<learn_msg_filter::NewString>("my_heart_break", 5);
	ros::Rate loop_rate(3);

	while(ros::ok()) {
		learn_msg_filter::NewString msg;

		msg.header.stamp = ros::Time::now();
		msg.header.frame_id = "/loveSS";

		std::stringstream ss;
		ss << "I love you.";
		msg.st = ss.str();
		pub.publish(msg);

		ros::spinOnce();
		loop_rate.sleep();

	}

	return 0;
}
