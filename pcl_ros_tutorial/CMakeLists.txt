cmake_minimum_required(VERSION 2.8.3)
project(pcl_ros_tutorial)

find_package(catkin REQUIRED COMPONENTS
  pcl_ros
  pcl_conversions
  roscpp
  sensor_msgs
)
include_directories(
        include #for pcl_filter.h
  ${catkin_INCLUDE_DIRS}
)


#commet out catkin_package demo not move to devel
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES my_package
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)



## Declare a cpp executable
add_executable(pcl_publisher_node src/pcl_publisher.cpp)
add_executable(pcl_write src/pcl_write.cpp)
add_executable(pcl_read src/pcl_read.cpp)
add_executable(pcl_filter_v1 src/pcl_filter_v1.cpp)
add_executable(pcl_filter_v2 src/pcl_filter_v2.cpp)
add_executable(pcl_filter_v3 src/pcl_filter_v3.cpp)
add_executable(pcl_filter_class src/pcl_filter_class.cpp)

add_executable(pcl_filter src/node.cpp src/pcl_filter.cpp)


target_link_libraries(pcl_publisher_node
   ${catkin_LIBRARIES}
 )

target_link_libraries(pcl_filter
   ${catkin_LIBRARIES}
   #${OpenCV_LIBRARIES}
 )
target_link_libraries(pcl_write
   ${catkin_LIBRARIES}
 )
target_link_libraries(pcl_read
   ${catkin_LIBRARIES}
 )

target_link_libraries(pcl_filter_v1
   ${catkin_LIBRARIES}
 )

target_link_libraries(pcl_filter_v2
   ${catkin_LIBRARIES}
 )
target_link_libraries(pcl_filter_v3
   ${catkin_LIBRARIES}
 )
target_link_libraries(pcl_filter_class
   ${catkin_LIBRARIES}
 )

