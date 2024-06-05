cmake_minimum_required(VERSION 3.0.2)
project(map_generator)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++1z")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall")
# add_definitions("-g")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  roslib
  pcl_conversions
)
find_package(PCL REQUIRED)
find_package(Eigen3 REQUIRED)

catkin_package(
        #  INCLUDE_DIRS include
        #  LIBRARIES irobot_msgs
         CATKIN_DEPENDS roscpp std_msgs roslib
        #  DEPENDS system_lib
#        CATKIN_DEPENDS message_runtime
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
  ${PCL_INCLUDE_DIRS}
)

add_executable (random_forest src/random_forest_sensing.cpp )
target_link_libraries(random_forest
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES})

add_executable (test_load_pcd src/test_load_pcd.cpp )
target_link_libraries(test_load_pcd
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES})
