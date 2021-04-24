#include "ros/ros.h"
#include <sstream>
#include <bits/stdc++.h>
#include "learn_msg_filter/NewString.h"


int main(int argc, char** argv) {

	ros::init(argc, argv, "firstNode");
	ros::NodeHandle nh;
	ROS_INFO_STREAM("First node started.");
	ros::Publisher pub = nh.advertise<learn_msg_filter::NewString>("ss", 5);
	ros::Rate loop_rate(2);

	while(ros::ok()) {
		learn_msg_filter::NewString msg;
		
		msg.header.stamp = ros::Time::now();
		msg.header.frame_id = "/mySS";


		std::stringstream ss;
		ss << "I'm sorry. ";
		msg.st = ss.str();
		
		pub.publish(msg);

		ros::spinOnce();

		loop_rate.sleep();

	}

	return 0;
	
}

