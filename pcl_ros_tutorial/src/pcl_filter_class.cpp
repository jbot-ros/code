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





FILTER::FILTER(){

        //Private parameters handler
        ros::NodeHandle pn("~");
        
        //不是Class的寫法 sub = nh.subscribe("kitti_point_cloud", 1, cb_cloud);
        sub = nh.subscribe("kitti_point_cloud", 1, &FILTER::cb_cloud, this);
        pub = nh.advertise<sensor_msgs::PointCloud2> ("pcl_filtered", 1);

}


FILTER::~FILTER(){

                                                                                                                                                   
}

void FILTER::cb_cloud(const sensor_msgs::PointCloud2ConstPtr& input_msg){
	sensor_msgs::PointCloud2 output;
	pcl::PCLPointCloud2* input_cloud = new pcl::PCLPointCloud2; 
	pcl::PCLPointCloud2ConstPtr cloudPtr(input_cloud);
	pcl::PCLPointCloud2 cloud_filtered;

	pcl_conversions::toPCL(*input_msg, *input_cloud);


	//process here
	pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
	sor.setInputCloud (cloudPtr);
	sor.setLeafSize (0.1f, 0.1f, 0.1f);
	sor.filter (cloud_filtered);

	pcl_conversions::fromPCL(cloud_filtered, output);
	
	pub.publish(output);

}

int main(int argc, char** argv){
	ros::init(argc, argv, "pcl_filter_class_node");
    FILTER filter;
	ros::spin();
	return 0;
}
