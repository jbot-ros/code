cmake_minimum_required(VERSION 2.8.3)
project(create_custom_msg)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  genmsg
)

## Generate messages in the 'msg' folder
add_message_files(
  FILES
  NewString.msg
)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
 INCLUDE_DIRS
 CATKIN_DEPENDS roscpp rospy std_msgs message_generation
)
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(firstNode src/firstNode.cpp)
target_link_libraries(firstNode ${catkin_LIBRARIES})
add_dependencies(firstNode create_sutom_msg_generate_messages_cpp)
