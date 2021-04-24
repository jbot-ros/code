#include "subandpub.h"
 
subscriberANDpublisher::subscriberANDpublisher()
{
    //subscribe topic
    camera_left_sub.subscribe(nh, "/kitti/camera_color_left/image_raw", 1);
    camera_right_sub.subscribe(nh, "/kitti/camera_color_right/image_raw", 1);
 
    //publisher
    camera_left_pub=nh.advertise<sensor_msgs::Image>("sync/img1",1000);
    camera_right_pub = nh.advertise<sensor_msgs::Image>("sync/img2", 1000);
 
    //callback
    sync_.reset(new Sync(syncpolicy(10), camera_left_sub, camera_right_sub));
    sync_->registerCallback(boost::bind(&subscriberANDpublisher::callback, this, _1, _2));
}
void subscriberANDpublisher::callback(const sensor_msgs::ImageConstPtr &image_left, const sensor_msgs::ImageConstPtr &image_right) {
    ROS_INFO("done! ");
    camera_left_pub.publish(image_left);
    camera_right_pub.publish(image_right);
}
