#include<ros/ros.h>
#include<sensor_msgs/PointCloud2.h>
#include<pcl_conversions/pcl_conversions.h>
#include<pcl/point_cloud.h>
#include<pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>


ros::Publisher pub;
const clock_t t_start = clock();
clock_t t_now = 0;
clock_t t_last = 0;

void cb_cloud(const sensor_msgs::PointCloud2& input_msg){
    t_now = clock();
    clock_t get_in_cb = t_now-t_last;
    t_last = t_now;

std::cout <<" Took " << get_in_cb << "time ticks "<< std::endl;
//std::cout << " Took " << (t_end -t_start)/CLOCKS_PER_SEC << " s "<< std::endl;
    sensor_msgs::PointCloud2 output;

    //pcl::PointCloud<pcl::PointXYZ> cloud;
    //pcl::PointCloud<pcl::PointXYZ> cloud_filtered;
    
    pcl::PCLPointCloud2* input_cloud = new pcl::PCLPointCloud2; 
	pcl::PCLPointCloud2ConstPtr cloudPtr(input_cloud);
	pcl::PCLPointCloud2 cloud_filtered;


//    pcl::fromROSMsg(input_msg, *input_cloud);
//	pcl_conversions::toPCL(*input_msg, *input_cloud);
	pcl_conversions::toPCL(input_msg, *input_cloud);


	//process here
	pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
	sor.setInputCloud (cloudPtr);
	sor.setLeafSize (0.1f, 0.1f, 0.1f);
	sor.filter (cloud_filtered);

	pcl_conversions::fromPCL(cloud_filtered, output);
	
	pub.publish(output);

}

int main(int argc, char** argv){
	ros::init(argc, argv, "pcl_filter_node");
	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("kitti_point_cloud", 1, cb_cloud);
	pub = nh.advertise<sensor_msgs::PointCloud2> ("pcl_filtered", 1);
	ros::spin();
	return 0;
}
