cmake_minimum_required(VERSION 2.8.3)
project(learn_msg_filter)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  genmsg
  message_filters
)

add_message_files(
  FILES
  NewString.msg
)
generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
 INCLUDE_DIRS
 CATKIN_DEPENDS roscpp rospy std_msgs message_generation message_filters
)
include_directories(${catkin_INCLUDE_DIRS})

add_executable(firstNode src/firstNode.cpp)
target_link_libraries(firstNode ${catkin_LIBRARIES})
add_dependencies(firstNode learn_msg_filter_generate_messages_cpp)

add_executable(secondNode src/secondNode.cpp)
target_link_libraries(secondNode ${catkin_LIBRARIES})
add_dependencies(secondNode learn_msg_filter_generate_messages_cpp)

add_executable(combinedNode src/combinedNode.cpp)
target_link_libraries(combinedNode ${catkin_LIBRARIES})
add_dependencies(combinedNode learn_msg_filter_generate_messages_cpp)

add_executable(classCombinedNode src/classCombinedNode.cpp)
target_link_libraries(classCombinedNode ${catkin_LIBRARIES})
add_dependencies(classCombinedNode learn_msg_filter_generate_messages_cpp)

add_executable(classPubCombinedNode src/classPubCombinedNode.cpp)
target_link_libraries(classPubCombinedNode ${catkin_LIBRARIES})
add_dependencies(classPubCombinedNode learn_msg_filter_generate_messages_cpp)
