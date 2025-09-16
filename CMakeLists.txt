cmake_minimum_required(VERSION 3.0.2)
project(markers2pcl)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  sensor_msgs
  std_msgs
  vicon_bridge
)

catkin_package()

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

# Exec
add_executable(markers2pcl src/markers2pcl.cpp)
target_link_libraries(markers2pcl ${catkin_LIBRARIES})
add_dependencies(markers2pcl ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})