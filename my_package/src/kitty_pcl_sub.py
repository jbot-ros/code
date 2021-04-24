import rospy
from sensor_msgs.msg import PointCloud2
from  pcl_helper import ros_to_pcl, pcl_to_ros,ros_to_pcl_XYZ, pcl_to_ros_XYZ
from std_msgs.msg import Header

def callback(pc):


    pcl_data = ros_to_pcl(pc)
    ros_pc = pcl_to_ros(pcl_data)
    pub.publish(ros_pc)
    #rospy.loginfo("Publish to /kitty_sub_pcl")
    rate.sleep()

rospy.init_node('pcl_sub_test', anonymous=True)
rospy.Subscriber('kitti_point_cloud', PointCloud2, callback,queue_size=10,  buff_size=2**30)

rate = rospy.Rate(float(5))
pub = rospy.Publisher('/kitty_sub_pcl', PointCloud2, queue_size=10)
rospy.spin()
