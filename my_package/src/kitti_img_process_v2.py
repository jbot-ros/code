#!/usr/bin/env python
#modified from Tony kuo https://github.com/tony2guo/track_racecar/blob/master/scripts/line_follower.py

import rospy
import cv2
import numpy as np
from sensor_msgs.msg import Image
from geometry_msgs.msg import Twist
from cv_bridge import CvBridge, CvBridgeError




def line_intersection(line1, line2):
    xdiff = (line1[0][0] - line1[1][0], line2[0][0] - line2[1][0])
    ydiff = (line1[0][1] - line1[1][1], line2[0][1] - line2[1][1])

    def det(a, b):
        return a[0] * b[1] - a[1] * b[0]

    div = det(xdiff, ydiff)
    if div == 0:
        return None

    d = (det(*line1), det(*line2))
    x = det(d, xdiff) / div
    y = det(d, ydiff) / div
    return x, y

def image_cb(msg):
    try:
        cv_image = bridge.imgmsg_to_cv2(msg, "bgr8")
        clone_img = cv_image.copy()
    except CvBridgeError as e:
        rospy.logerr(e)
        return
    pub_vel = Twist()
    height = cv_image.shape[0]
    width = cv_image.shape[1]

    blur_image = cv2.GaussianBlur(cv_image, (13, 13), 0)
    cv2.imshow('blur_image', blur_image)
    cv2.waitKey(1)

    canny_image = cv2.Canny(blur_image, 50, 150, apertureSize=3)
    #cv2.imshow('canny_image', canny_image)
    #cv2.waitKey(0)

    #    ROI lb,rb,rt,lt
    polygons = np.array([
        [(440, height), (645, height), (632, 221), (565, 220)]
    ])

    mask = np.zeros_like(canny_image)
    cv2.fillPoly(mask, polygons, 255)
    masked_image = cv2.bitwise_and(canny_image, mask)

    contours, hierarchy = cv2.findContours(masked_image,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
    for cnt in contours:
        cv2.drawContours(clone_img, cnt, -1, (0,200,0), 3)

    cv2.imshow('clone_img', clone_img)
    cv2.waitKey(1)


    try:
        image_pub.publish(bridge.cv2_to_imgmsg(clone_img, "bgr8"))
        #image_pub.publish(bridge.cv2_to_imgmsg(cv_image,encoding="passthrough"))
    except CvBridgeError as e:
        rospy.logerr(e)








if __name__ == '__main__':
    rospy.init_node('line_follower')
    bridge = CvBridge()
    image_pub = rospy.Publisher("~image_raw", Image, queue_size=1)
    #cmd_vel_pub = rospy.Publisher("~cmd_vel", Twist, queue_size=1)
    image_sub = rospy.Subscriber("kitti_cam", Image, image_cb)
    rospy.spin()