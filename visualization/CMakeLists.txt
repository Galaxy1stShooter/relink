cmake_minimum_required(VERSION 3.0.2)
project(visualization)

set(CMAKE_CXX_FLAGS "-std=c++1z")
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -fPIC")
add_definitions("-g")

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(Eigen3 REQUIRED)
find_package(PCL REQUIRED)
find_package(catkin REQUIRED COMPONENTS
        roscpp
        pcl_conversions
        std_msgs
        sensor_msgs
        nav_msgs
        geometry_msgs
        message_files
        optimizer
        )

catkin_package(
         INCLUDE_DIRS include
        #  LIBRARIES irobot_msgs
         CATKIN_DEPENDS geometry_msgs nav_msgs message_files roscpp std_msgs sensor_msgs optimizer
        #  DEPENDS system_lib
#        CATKIN_DEPENDS message_runtime
)

###########
## Build ##
###########
# find_package(Armadillo REQUIRED)
# include_directories(${ARMADILLO_INCLUDE_DIRS})

## Specify additional locations of header files
## Your package locations should be listed before other locations

include_directories(
        include
        ${catkin_INCLUDE_DIRS}
        ${EIGEN3_INCLUDE_DIRS}
        ${PCL_INCLUDE_DIRS}
)

## Declare a cpp library
# add_library(irobot_msgs
#   src/${PROJECT_NAME}/irobot_msgs.cpp
# )

## Declare a cpp executable
add_executable(entities_visualization src/entities_visualization.cpp )
add_executable(scp_visualization src/scp_visualization.cpp)

## Specify libraries to link a library or executable target against
# target_link_libraries(network
#         ${catkin_LIBRARIES}
#         )
target_link_libraries(entities_visualization
        ${catkin_LIBRARIES}
        ${EIGEN_LIBRARIES}
        ${PCL_LIBRARIES}
        los_checker
        )
target_link_libraries(scp_visualization
        ${catkin_LIBRARIES}
        ${EIGEN_LIBRARIES}
        ${PCL_LIBRARIES}
        )
