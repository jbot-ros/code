cmake_minimum_required(VERSION 2.8.3)
project(my_package)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES my_package
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(my_package src/my_package.cpp )
target_link_libraries(my_package ${catkin_LIBRARIES})

