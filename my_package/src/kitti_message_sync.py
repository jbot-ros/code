import rospy
import numpy as np


from sensor_msgs.msg import Image, CameraInfo, PointCloud2, PointField
from visualization_msgs.msg import Marker
import sensor_msgs.point_cloud2 as pc2


from cv_bridge import CvBridge, CvBridgeError
import message_filters
import math
import cv2  # OpenCV module
import pcl # https://github.com/udacity/RoboND-Perception-Exercises
from pcl_helper import ros_to_pcl,pcl_to_ros

rospy.init_node('syncronize_node', anonymous=True)

# Publisher for publishing pyramid marker in rviz
vis_pub = rospy.Publisher('/visualization_marker', Marker, queue_size=10)

# Bridge to convert ROS Image type to OpenCV Image type
cv_bridge = CvBridge()



def do_voxel_grid_filter(point_cloud, LEAF_SIZE = 0.01):
    voxel_filter = point_cloud.make_voxel_grid_filter()
    voxel_filter.set_leaf_size(LEAF_SIZE, LEAF_SIZE, LEAF_SIZE)
    return voxel_filter.filter()


# Returns only the point cloud information at a specific range of a specific axis
def do_passthrough_filter(point_cloud, name_axis = 'z', min_axis = 0.6, max_axis = 1.1):
    pass_filter = point_cloud.make_passthrough_filter()
    pass_filter.set_filter_field_name(name_axis);
    pass_filter.set_filter_limits(min_axis, max_axis)
    return pass_filter.filter()


def camPCLCallBack(rgb_data, pcl_data ):

    rospy.loginfo("in camPCLCallBack!!!")

"""
    try:
        cv_image = cv_bridge.imgmsg_to_cv2(rgb_data, "bgr8")
        point_cloud=ros_to_pcl(pcl_data)
        downsampled_cloud = do_voxel_grid_filter(point_cloud = point_cloud, LEAF_SIZE = 0.01)
        # Get only information in our region of interest as we don't care about the other parts
        filtered_cloud = do_passthrough_filter(point_cloud = downsampled_cloud,name_axis = 'z', min_axis = 0.6, max_axis = 1.1)
        objects_msg=pcl_to_ros(filtered_cloud)
        objects_publisher.publish(objects_msg)

    except CvBridgeError as e:
        print(e)
"""

def main():
    #  Subscribe to both RGB and point cloud with a Synchronizer
        image_sub = message_filters.Subscriber("kitti_cam", Image)
        pcl_sub = message_filters.Subscriber("kitti_point_cloud", PointCloud2)
        ts = message_filters.ApproximateTimeSynchronizer([image_sub, pcl_sub], 10, 0.5)
        ts.registerCallback(camPCLCallBack)
        objects_publisher = rospy.Publisher("/pcl_objects", PointCloud2, queue_size = 1)
        rospy.spin()





if __name__=='__main__':
    main()
