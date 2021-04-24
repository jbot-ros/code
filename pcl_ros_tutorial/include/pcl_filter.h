#include<ros/ros.h>                                                                       
#include<sensor_msgs/PointCloud2.h>
#include<pcl_conversions/pcl_conversions.h>
#include<pcl/point_cloud.h>
#include<pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>



class FILTER{

        private:
                ros::NodeHandle nh;
                ros::Subscriber sub;
                ros::Publisher pub;

        public:
                FILTER();
                ~FILTER();
                void cb_cloud(const sensor_msgs::PointCloud2ConstPtr& input_msg);
};
//FILTER CLASS ";"
