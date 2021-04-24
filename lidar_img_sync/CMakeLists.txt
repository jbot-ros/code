cmake_minimum_required(VERSION 3.0.2)
project(lidar_img_sync)

find_package(catkin REQUIRED COMPONENTS
  message_filters
  roscpp
  sensor_msgs
)
catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES lidar_img_sync
#  CATKIN_DEPENDS message_filters roscpp sensor_msgs
#  DEPENDS system_lib
)

include_directories(
 include/lidar_img_sync
  ${catkin_INCLUDE_DIRS}
)

 add_executable(node src/main.cpp src/subandpub.cpp)

# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
 target_link_libraries(node
   ${catkin_LIBRARIES}
 )
