#include "ros/ros.h"
#include <sstream>
#include <bits/stdc++.h>
#include "create_custom_msg/NewString.h"


int main(int argc, char** argv) {

	ros::init(argc, argv, "firstNode");
	ros::NodeHandle nh;
	ROS_INFO_STREAM("First node started.");
	ros::Publisher pub = nh.advertise<create_custom_msg::NewString>("ss", 5);
	ros::Rate loop_rate(5);

	while(ros::ok()) {
		create_custom_msg::NewString msg;
		
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

