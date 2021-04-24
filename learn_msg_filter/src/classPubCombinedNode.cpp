#include "ros/ros.h"
#include <sstream>
#include <bits/stdc++.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include "learn_msg_filter/NewString.h"
#include <std_msgs/String.h>

//using namespace ros;
//using namespace message_filters;

class Collector{
        public:
                Collector();
                ~Collector();
                void callback(const learn_msg_filter::NewString::ConstPtr &f1, 
                              const learn_msg_filter::NewString::ConstPtr &s1);
        private:
                ros::NodeHandle nh_;
                //message filter
                message_filters::Subscriber<learn_msg_filter::NewString> f_sub;
                message_filters::Subscriber<learn_msg_filter::NewString> s_sub;
                typedef message_filters::sync_policies::ApproximateTime<learn_msg_filter::NewString, learn_msg_filter::NewString> MySyncPolicy;
                typedef message_filters::Synchronizer<MySyncPolicy> Sync;
                boost::shared_ptr<Sync> sync_;
                //publisher
                ros::Publisher pub;
        
};

//Construtor to initialize Pub, Sub Content
Collector::Collector()
{
        //message filter
        f_sub.subscribe(nh_, "ss",1);
        s_sub.subscribe(nh_, "my_heart_break",1);
        sync_.reset(new Sync(MySyncPolicy(10), f_sub, s_sub));
        sync_->registerCallback(boost::bind(&Collector::callback, this, _1,_2));

        //Publisher
        pub = nh_.advertise<learn_msg_filter::NewString>("combineMsg", 5);

};

Collector::~Collector()
{

};
void Collector::callback(const learn_msg_filter::NewString::ConstPtr &f1, 
	          const learn_msg_filter::NewString::ConstPtr &s1) {

	std_msgs::String out_String;

	//out_String.data = f1->st + s1->st;
    //ROS_INFO_STREAM(out_String);
    ROS_INFO_STREAM("Sync!");
    
    learn_msg_filter::NewString msg;   
    msg.header.stamp = ros::Time::now(); 
    msg.header.frame_id = "/mySS";
    msg.st = f1->st + s1->st;;
    pub.publish(msg);
    
}


int main(int argc, char** argv) {

	ros::init(argc, argv, "synchronizer");
	//ros::NodeHandle nh;
    //message_filters::Subscriber<learn_msg_filter::NewString> f_sub(nh, "ss", 1);
	//message_filters::Subscriber<learn_msg_filter::NewString> s_sub(nh, "my_heart_break", 1);
    
	//typedef sync_policies::ApproximateTime<learn_msg_filter::NewString, learn_msg_filter::NewString> MySyncPolicy;

	//Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), f_sub, s_sub);
	//sync.registerCallback(boost::bind(&callback, _1, _2));
	
    Collector synchronizer;
    ROS_INFO_STREAM("checking ...");
	
	ros::spin();

	return 0;

}
