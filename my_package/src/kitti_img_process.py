#!/usr/bin/env python
#modified from Tony kuo

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

    #gray_image = cv2.cvtColor(cv_image, cv2.COLOR_RGB2GRAY)
    blur_image = cv2.GaussianBlur(cv_image, (13, 13), 0)
    cv2.imshow('blur_image', blur_image)
    cv2.waitKey(1)

    canny_image = cv2.Canny(blur_image, 50, 150, apertureSize=3)

    #cv2.imshow('canny_image', canny_image)
    #cv2.waitKey(0)

#     lb,rb,rt,lt
    polygons = np.array([
        [(440, height), (645, height), (632, 221), (565, 220)]
    ])

    mask = np.zeros_like(canny_image)
    cv2.fillPoly(mask, polygons, 255)
    masked_image = cv2.bitwise_and(canny_image, mask)

    #cv2.imshow('mask', mask)
    #cv2.waitKey(0)

    cv2.imshow('masked_image', masked_image)
    cv2.waitKey(1)

    #find line
    rho = 2            #distance resolution in pixels of the Hough grid
    theta = np.pi/180  #angular resolution in radians of the Hough grid
    threshold = 100     #minimum number of votes (intersections in Hough grid cell)
    min_line_len = 30  #minimum number of pixels making up a line
    max_line_gap = 10  #maximum gap in pixels between connectable line segments
    lines = cv2.HoughLinesP(masked_image, rho, np.pi / 180, threshold, min_line_len, max_line_gap)

    if lines is not None:
        for index, line in enumerate(lines):
            line_count = len(lines)
            print(lines)
            print(line_count)
            x1, y1, x2, y2 = line[0]
            cv2.line(masked_image, (x1, y1), (x2, y2), (0, 0, 255), 2)
            cv2.imshow('line_image', masked_image)
            cv2.waitKey(1)

    else:
        rospy.logwarn("no lines")

    """
        for index, line in enumerate(lines):
            x1, y1, x2, y2 = line[0]
            (A, B) = (x1, y1), (x2, y2)
            cv2.line(cv_image, (x1, y1), (x2, y2), (0, 0, 255), 2)
            for compare_index in range(index+1, line_count):
                x1, y1, x2, y2 = lines[compare_index][0]
                (C, D) = (x1, y1), (x2, y2)
                intersection = line_intersection((A, B), (C, D))
                if intersection is not None:
                    if intersection[0] < width and intersection[0] > 0 and intersection[1] < height and intersection[1] > 0:
                        cv2.circle(cv_image, (int(intersection[0]), int(intersection[1])), 5, (0, 255, 0), 2)
                        intersections.append(intersection)
        if len(intersections) > 0:
            x, y = np.mean(intersections, axis=0)
            cv2.arrowedLine(cv_image, (width//2, height), (int(x), int(y)), (255, 0, 0), 2)
            pub_vel.linear.x = 1 - y / height
            pub_vel.angular.z = 0.5 - x / width
        """


    cmd_vel_pub.publish(pub_vel)
    try:
        image_pub.publish(bridge.cv2_to_imgmsg(cv_image, "bgr8"))
        #image_pub.publish(bridge.cv2_to_imgmsg(cv_image,encoding="passthrough"))
    except CvBridgeError as e:
        rospy.logerr(e)








if __name__ == '__main__':
    rospy.init_node('line_follower')
    bridge = CvBridge()
    image_pub = rospy.Publisher("~image_raw", Image, queue_size=1)
    cmd_vel_pub = rospy.Publisher("~cmd_vel", Twist, queue_size=1)
    image_sub = rospy.Subscriber("kitti_cam", Image, image_cb)
    rospy.spin()