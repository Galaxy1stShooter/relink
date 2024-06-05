cmake_minimum_required(VERSION 3.0.2)
project(simulator)

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
        roslib
        pcl_conversions
        message_generation
        message_files
        optimizer
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
          CATKIN_DEPENDS roscpp rospy std_msgs roslib optimizer
        #  DEPENDS system_lib
          CATKIN_DEPENDS message_runtime
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


## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(episode_controller src/episode_controller.cpp)
add_executable(entity_controller src/entity_controller.cpp)
add_executable(measurement_calculator src/measurement_calculator.cpp)
add_executable(record_car src/record_car.cpp)

target_link_libraries(entity_controller
        ${catkin_LIBRARIES}
        ${EIGEN_LIBRARIES}
        ${PCL_LIBRARIES}
        )

target_link_libraries(episode_controller
        ${catkin_LIBRARIES}
        )

target_link_libraries(measurement_calculator
        ${catkin_LIBRARIES}
)

target_link_libraries(record_car
        ${catkin_LIBRARIES}
        )
