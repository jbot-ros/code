#!/usr/bin/env python
import cv2
import os
import rospy
from cv_bridge import CvBridge
from sensor_msgs.msg import Image, PointCloud2
import sensor_msgs.point_cloud2 as pcl2
import numpy as np
from std_msgs.msg import Header

DATA_PATH = '/home/corleone/jbot/data/kitti/RawData/2011_09_26/2011_09_26_drive_0001_sync/'

if __name__ == '__main__':
    frame = 0
    rospy.init_node('kitti_node', anonymous=True)
    cam_pub = rospy.Publisher('kitti_cam', Image,queue_size=10)
    pcl_pub = rospy.Publisher('kitti_point_cloud', PointCloud2, queue_size=10)

    bridge= CvBridge()

    rate = rospy.Rate(10)

    while not rospy.is_shutdown():
        header = Header()
        header.stamp = rospy.Time.now()
        header.frame_id = 'map'

        img = cv2.imread(os.path.join(DATA_PATH,'image_00/data/%010d.png'%frame))
        point_cloud = np.fromfile(os.path.join(DATA_PATH, 'velodyne_points/data/%010d.bin'%frame), dtype=np.float32).reshape(-1, 4)


        #cam_pub.publish(bridge.cv2_to_imgmsg(img, "bgr8"))

        img_msg = bridge.cv2_to_imgmsg(img, "bgr8")
        img_msg.header.stamp = header.stamp
        img_msg.header.frame_id = 'map'
        cam_pub.publish(img_msg)


        #http://docs.ros.org/melodic/api/sensor_msgs/html/point__cloud2_8py.html
        pcl_pub.publish(pcl2.create_cloud_xyz32(header, point_cloud[:, :3]))
        rospy.loginfo("camera image published!!!")
        rospy.loginfo("point cloud published!!!")
        rate.sleep()
        frame +=1
        frame %= 107