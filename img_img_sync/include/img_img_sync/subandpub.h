#ifndef __SUBANDPUB_H__
#define __SUBANDPUB_H__
//ros header
#include <ros/ros.h>
//time syncronize
#include <message_filters/subscriber.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/synchronizer.h>
//sensor topic
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
 
class subscriberANDpublisher{
public:
    subscriberANDpublisher();
    void callback(const sensor_msgs::ImageConstPtr &image_left, const sensor_msgs::ImageConstPtr &image_right);
 
private:
    ros::NodeHandle nh;
    ros::Publisher camera_left_pub;
    ros::Publisher camera_right_pub;
    message_filters::Subscriber<sensor_msgs::Image> camera_left_sub;//camera_left_sub
    message_filters::Subscriber<sensor_msgs::Image> camera_right_sub;//camera_right_sub
 
    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image> syncpolicy;//policy for time syncronize
    typedef message_filters::Synchronizer<syncpolicy> Sync;
    boost::shared_ptr<Sync> sync_;//syncronizer
 
};
#endif
