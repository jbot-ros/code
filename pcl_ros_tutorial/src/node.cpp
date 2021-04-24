#include "pcl_filter.h"

int main(int argc, char** argv){
    ros::init(argc, argv, "pcl_filter_class_node");
    ROS_INFO("Start Filter Node!!!");
    FILTER filter;
    ros::spin();
    return 0;
}

