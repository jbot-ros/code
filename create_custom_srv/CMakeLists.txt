cmake_minimum_required(VERSION 3.0.2)
project(create_custom_srv)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  rospy
  std_msgs
  genmsg #Need
)


## Generate services in the 'srv' folder
add_service_files(
	FILES
    AddTwoInts.srv
)

generate_messages()

catkin_package(CATKIN_DEPENDS roscpp roslib message_runtime)
include_directories(${catkin_INCLUDE_DIRS})
#Demo service server
add_executable(demo_service_server src/demo_service_server.cpp)
target_link_libraries(demo_service_server ${catkin_LIBRARIES})
add_dependencies(demo_service_server create_custom_srv_gencpp)# Need


#Demo service client
add_executable(demo_service_client src/demo_service_client.cpp)
target_link_libraries(demo_service_client ${catkin_LIBRARIES})
add_dependencies(demo_service_client create_custom_srv_gencpp)# Need

# 備註：以下兩指令同義 (<pkg>_gencpp == <pkg>_generate_messages_cpp)
# add_dependencies(demo_service_client create_custom_srv_gencpp)
# add_dependencies(demo_service_client create_custom_srv_generate_messages_cpp)
