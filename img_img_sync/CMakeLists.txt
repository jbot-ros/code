cmake_minimum_required(VERSION 2.8.3)
project(img_img_sync)

find_package(catkin REQUIRED COMPONENTS
  message_filters
  roscpp
  sensor_msgs
)
catkin_package(
  INCLUDE_DIRS include
)

include_directories(
 include/img_img_sync
  ${catkin_INCLUDE_DIRS}
)

add_executable(node_img src/main.cpp src/subandpubImg.cpp)

target_link_libraries(node_img
   ${catkin_LIBRARIES}
 )
