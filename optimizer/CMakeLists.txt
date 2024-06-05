cmake_minimum_required(VERSION 3.0.2)
project(optimizer)

## Compile as C++11, supported in ROS Kinetic and newer
set(CMAKE_CXX_FLAGS "-std=c++1z")
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE "-O0 -Wall -fPIC")
add_definitions("-g")

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
        roscpp
        rospy
        std_msgs
        geometry_msgs
        pcl_conversions
        message_generation
        message_files
        message_generation
        sensor_msgs
        nav_msgs
        )

## System dependencies are found with CMake's conventions
find_package(Eigen3 REQUIRED)
find_package(PCL REQUIRED)

###################################
## catkin specific configuration ##
###################################
catkin_package(
         INCLUDE_DIRS include
#          LIBRARIES optimizer
          CATKIN_DEPENDS roscpp rospy std_msgs message_runtime message_files
        #  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
        include
        ${catkin_INCLUDE_DIRS}
        ${EIGEN3_INCLUDE_DIRS}
        ${PCL_INCLUDE_DIRS}
)

add_library(los_checker src/los_checker.cpp src/graph_constructor.cpp src/grid_map.cpp src/optimizer.cpp)

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(algorithm src/algorithm.cpp src/los_checker.cpp src/graph_constructor.cpp src/grid_map.cpp src/optimizer.cpp)

#add_executable(test_pruning src/test_pruning.cpp src/graph_constructor.cpp src/grid_map.cpp)
#target_link_libraries(test_pruning
#        ${catkin_LIBRARIES}
#        )

target_link_libraries(algorithm
        ${catkin_LIBRARIES}
        ${EIGEN_LIBRARIES}
        ${PCL_LIBRARIES}
        )

#add_executable(test_los src/test_los.cpp src/graph_constructor.cpp src/grid_map.cpp)
#target_link_libraries(test_los
#${catkin_LIBRARIES}
#${EIGEN_LIBRARIES}
#${PCL_LIBRARIES}
#)

# add_executable(pure_starconvex src/pure_starconvex.cpp)
# target_link_libraries(pure_starconvex
# ${catkin_LIBRARIES}
# ${EIGEN_LIBRARIES}
# ${PCL_LIBRARIES}
# )

