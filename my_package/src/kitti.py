#!/usr/bin/env python
import cv2
import os
import rospy
from cv_bridge import CvBridge
from sensor_msgs.msg import Image

DATA_PATH = '/home/corleone/jbot/data/kitti/RawData/2011_09_26/2011_09_26_drive_0001_sync/'

if __name__ == '__main__':
    frame = 0
    rospy.init_node('kitti_node', anonymous=True)
    cam_pub = rospy.Publisher('kitti_cam', Image,queue_size=10)

    bridge= CvBridge()

    rate = rospy.Rate(10)

    while not rospy.is_shutdown():
        #img = cv2.imread(os.path.join(DATA_PATH,'image_00/data/%010d.png'%0))
        img = cv2.imread(os.path.join(DATA_PATH,'image_00/data/%010d.png'%frame))
        cam_pub.publish(bridge.cv2_to_imgmsg(img, "bgr8"))
        rospy.loginfo("camera image published!!!")
        rate.sleep()
        frame +=1
        frame %= 107