#include "subandpub.h"
 
subscriberANDpublisher::subscriberANDpublisher()
{
    //订阅话题
    lidar_sub.subscribe(nh, "/kitti/velo/pointcloud", 1);
    camera_sub.subscribe(nh, "/kitti/camera_color_left/image_raw", 1);
 
    //发布者
    camera_pub=nh.advertise<sensor_msgs::Image>("sync/img",1000);
    lidar_pub = nh.advertise<sensor_msgs::PointCloud2>("sync/lidar", 1000);
 
    //回调
    sync_.reset(new Sync(syncpolicy(10), camera_sub, lidar_sub));
    sync_->registerCallback(boost::bind(&subscriberANDpublisher::callback, this, _1, _2));
}
void subscriberANDpublisher::callback(const sensor_msgs::ImageConstPtr &image, const sensor_msgs::PointCloud2ConstPtr &pointcloud) {
    ROS_INFO("done! ");
    camera_pub.publish(image);
    lidar_pub.publish(pointcloud);
}
