# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "tuw_multi_robot_msgs: 16 messages, 2 services")

set(MSG_I_FLAGS "-Ituw_multi_robot_msgs:/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg;-Igeometry_msgs:/opt/ros/melodic/share/geometry_msgs/cmake/../msg;-Inav_msgs:/opt/ros/melodic/share/nav_msgs/cmake/../msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg;-Iactionlib_msgs:/opt/ros/melodic/share/actionlib_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(tuw_multi_robot_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Graph.msg" NAME_WE)
add_custom_target(_tuw_multi_robot_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tuw_multi_robot_msgs" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Graph.msg" "geometry_msgs/Pose:tuw_multi_robot_msgs/Vertex:geometry_msgs/Point:geometry_msgs/Quaternion:std_msgs/Header"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotInfo.msg" NAME_WE)
add_custom_target(_tuw_multi_robot_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tuw_multi_robot_msgs" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotInfo.msg" "tuw_multi_robot_msgs/RoutePrecondition:geometry_msgs/Pose:geometry_msgs/PoseWithCovariance:std_msgs/Header:geometry_msgs/Quaternion:geometry_msgs/Point"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderArray.msg" NAME_WE)
add_custom_target(_tuw_multi_robot_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tuw_multi_robot_msgs" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderArray.msg" "tuw_multi_robot_msgs/Order:geometry_msgs/Pose:std_msgs/Header:tuw_multi_robot_msgs/Station:geometry_msgs/Quaternion:geometry_msgs/Point"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Order.msg" NAME_WE)
add_custom_target(_tuw_multi_robot_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tuw_multi_robot_msgs" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Order.msg" "tuw_multi_robot_msgs/Station:geometry_msgs/Pose:geometry_msgs/Point:geometry_msgs/Quaternion:std_msgs/Header"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Route.msg" NAME_WE)
add_custom_target(_tuw_multi_robot_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tuw_multi_robot_msgs" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Route.msg" "tuw_multi_robot_msgs/RoutePrecondition:tuw_multi_robot_msgs/RouteSegment:geometry_msgs/Pose:std_msgs/Header:geometry_msgs/Quaternion:geometry_msgs/Point"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg" NAME_WE)
add_custom_target(_tuw_multi_robot_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tuw_multi_robot_msgs" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg" "geometry_msgs/Pose:geometry_msgs/Point:geometry_msgs/Quaternion:std_msgs/Header"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteSegment.msg" NAME_WE)
add_custom_target(_tuw_multi_robot_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tuw_multi_robot_msgs" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteSegment.msg" "geometry_msgs/Pose:tuw_multi_robot_msgs/RoutePrecondition:geometry_msgs/Quaternion:geometry_msgs/Point"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerStationProtocol.srv" NAME_WE)
add_custom_target(_tuw_multi_robot_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tuw_multi_robot_msgs" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerStationProtocol.srv" "tuw_multi_robot_msgs/Station:geometry_msgs/Pose:geometry_msgs/Point:geometry_msgs/Quaternion:std_msgs/Header"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoalsArray.msg" NAME_WE)
add_custom_target(_tuw_multi_robot_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tuw_multi_robot_msgs" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoalsArray.msg" "geometry_msgs/Pose:geometry_msgs/Point:geometry_msgs/Quaternion:tuw_multi_robot_msgs/RobotGoals:std_msgs/Header"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Pickup.msg" NAME_WE)
add_custom_target(_tuw_multi_robot_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tuw_multi_robot_msgs" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Pickup.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerControlProtocol.srv" NAME_WE)
add_custom_target(_tuw_multi_robot_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tuw_multi_robot_msgs" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerControlProtocol.srv" ""
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Vertex.msg" NAME_WE)
add_custom_target(_tuw_multi_robot_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tuw_multi_robot_msgs" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Vertex.msg" "geometry_msgs/Point"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteProgress.msg" NAME_WE)
add_custom_target(_tuw_multi_robot_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tuw_multi_robot_msgs" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteProgress.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/StationArray.msg" NAME_WE)
add_custom_target(_tuw_multi_robot_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tuw_multi_robot_msgs" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/StationArray.msg" "tuw_multi_robot_msgs/Station:geometry_msgs/Pose:geometry_msgs/Point:geometry_msgs/Quaternion:std_msgs/Header"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoals.msg" NAME_WE)
add_custom_target(_tuw_multi_robot_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tuw_multi_robot_msgs" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoals.msg" "geometry_msgs/Pose:geometry_msgs/Quaternion:geometry_msgs/Point"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouterStatus.msg" NAME_WE)
add_custom_target(_tuw_multi_robot_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tuw_multi_robot_msgs" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouterStatus.msg" ""
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg" NAME_WE)
add_custom_target(_tuw_multi_robot_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tuw_multi_robot_msgs" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg" ""
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderPosition.msg" NAME_WE)
add_custom_target(_tuw_multi_robot_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tuw_multi_robot_msgs" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderPosition.msg" "geometry_msgs/Pose:geometry_msgs/Point:geometry_msgs/Quaternion:std_msgs/Header"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Graph.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Vertex.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_cpp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotInfo.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_cpp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderArray.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Order.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_cpp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Order.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_cpp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Route.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteSegment.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_cpp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Vertex.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_cpp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_cpp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteSegment.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_cpp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderPosition.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_cpp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Pickup.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_cpp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoalsArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoals.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_cpp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteProgress.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_cpp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/StationArray.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_cpp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouterStatus.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_cpp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_cpp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoals.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_multi_robot_msgs
)

### Generating Services
_generate_srv_cpp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerStationProtocol.srv"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_srv_cpp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerControlProtocol.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_multi_robot_msgs
)

### Generating Module File
_generate_module_cpp(tuw_multi_robot_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_multi_robot_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(tuw_multi_robot_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(tuw_multi_robot_msgs_generate_messages tuw_multi_robot_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Graph.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_cpp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotInfo.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_cpp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderArray.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_cpp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Order.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_cpp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Route.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_cpp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_cpp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteSegment.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_cpp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerStationProtocol.srv" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_cpp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoalsArray.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_cpp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Pickup.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_cpp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerControlProtocol.srv" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_cpp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Vertex.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_cpp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteProgress.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_cpp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/StationArray.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_cpp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoals.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_cpp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouterStatus.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_cpp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_cpp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderPosition.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_cpp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(tuw_multi_robot_msgs_gencpp)
add_dependencies(tuw_multi_robot_msgs_gencpp tuw_multi_robot_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS tuw_multi_robot_msgs_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Graph.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Vertex.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_eus(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotInfo.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_eus(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderArray.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Order.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_eus(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Order.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_eus(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Route.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteSegment.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_eus(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Vertex.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_eus(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_eus(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteSegment.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_eus(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderPosition.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_eus(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Pickup.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_eus(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoalsArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoals.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_eus(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteProgress.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_eus(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/StationArray.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_eus(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouterStatus.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_eus(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_eus(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoals.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_multi_robot_msgs
)

### Generating Services
_generate_srv_eus(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerStationProtocol.srv"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_srv_eus(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerControlProtocol.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_multi_robot_msgs
)

### Generating Module File
_generate_module_eus(tuw_multi_robot_msgs
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_multi_robot_msgs
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(tuw_multi_robot_msgs_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(tuw_multi_robot_msgs_generate_messages tuw_multi_robot_msgs_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Graph.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_eus _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotInfo.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_eus _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderArray.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_eus _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Order.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_eus _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Route.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_eus _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_eus _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteSegment.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_eus _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerStationProtocol.srv" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_eus _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoalsArray.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_eus _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Pickup.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_eus _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerControlProtocol.srv" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_eus _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Vertex.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_eus _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteProgress.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_eus _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/StationArray.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_eus _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoals.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_eus _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouterStatus.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_eus _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_eus _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderPosition.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_eus _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(tuw_multi_robot_msgs_geneus)
add_dependencies(tuw_multi_robot_msgs_geneus tuw_multi_robot_msgs_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS tuw_multi_robot_msgs_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Graph.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Vertex.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_lisp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotInfo.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_lisp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderArray.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Order.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_lisp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Order.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_lisp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Route.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteSegment.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_lisp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Vertex.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_lisp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_lisp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteSegment.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_lisp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderPosition.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_lisp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Pickup.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_lisp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoalsArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoals.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_lisp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteProgress.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_lisp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/StationArray.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_lisp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouterStatus.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_lisp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_lisp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoals.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_multi_robot_msgs
)

### Generating Services
_generate_srv_lisp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerStationProtocol.srv"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_srv_lisp(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerControlProtocol.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_multi_robot_msgs
)

### Generating Module File
_generate_module_lisp(tuw_multi_robot_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_multi_robot_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(tuw_multi_robot_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(tuw_multi_robot_msgs_generate_messages tuw_multi_robot_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Graph.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_lisp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotInfo.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_lisp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderArray.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_lisp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Order.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_lisp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Route.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_lisp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_lisp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteSegment.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_lisp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerStationProtocol.srv" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_lisp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoalsArray.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_lisp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Pickup.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_lisp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerControlProtocol.srv" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_lisp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Vertex.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_lisp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteProgress.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_lisp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/StationArray.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_lisp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoals.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_lisp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouterStatus.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_lisp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_lisp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderPosition.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_lisp _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(tuw_multi_robot_msgs_genlisp)
add_dependencies(tuw_multi_robot_msgs_genlisp tuw_multi_robot_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS tuw_multi_robot_msgs_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Graph.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Vertex.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_nodejs(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotInfo.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_nodejs(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderArray.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Order.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_nodejs(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Order.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_nodejs(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Route.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteSegment.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_nodejs(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Vertex.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_nodejs(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_nodejs(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteSegment.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_nodejs(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderPosition.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_nodejs(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Pickup.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_nodejs(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoalsArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoals.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_nodejs(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteProgress.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_nodejs(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/StationArray.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_nodejs(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouterStatus.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_nodejs(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_nodejs(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoals.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_multi_robot_msgs
)

### Generating Services
_generate_srv_nodejs(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerStationProtocol.srv"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_srv_nodejs(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerControlProtocol.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_multi_robot_msgs
)

### Generating Module File
_generate_module_nodejs(tuw_multi_robot_msgs
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_multi_robot_msgs
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(tuw_multi_robot_msgs_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(tuw_multi_robot_msgs_generate_messages tuw_multi_robot_msgs_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Graph.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_nodejs _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotInfo.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_nodejs _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderArray.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_nodejs _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Order.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_nodejs _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Route.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_nodejs _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_nodejs _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteSegment.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_nodejs _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerStationProtocol.srv" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_nodejs _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoalsArray.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_nodejs _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Pickup.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_nodejs _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerControlProtocol.srv" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_nodejs _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Vertex.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_nodejs _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteProgress.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_nodejs _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/StationArray.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_nodejs _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoals.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_nodejs _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouterStatus.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_nodejs _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_nodejs _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderPosition.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_nodejs _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(tuw_multi_robot_msgs_gennodejs)
add_dependencies(tuw_multi_robot_msgs_gennodejs tuw_multi_robot_msgs_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS tuw_multi_robot_msgs_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Graph.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Vertex.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_py(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotInfo.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseWithCovariance.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_py(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderArray.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Order.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_py(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Order.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_py(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Route.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteSegment.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_py(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Vertex.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_py(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_py(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteSegment.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_py(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderPosition.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_py(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Pickup.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_py(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoalsArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoals.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_py(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteProgress.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_py(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/StationArray.msg"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_py(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouterStatus.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_py(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_msg_py(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoals.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs
)

### Generating Services
_generate_srv_py(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerStationProtocol.srv"
  "${MSG_I_FLAGS}"
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs
)
_generate_srv_py(tuw_multi_robot_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerControlProtocol.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs
)

### Generating Module File
_generate_module_py(tuw_multi_robot_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(tuw_multi_robot_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(tuw_multi_robot_msgs_generate_messages tuw_multi_robot_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Graph.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_py _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotInfo.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_py _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderArray.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_py _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Order.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_py _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Route.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_py _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Station.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_py _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteSegment.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_py _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerStationProtocol.srv" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_py _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoalsArray.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_py _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Pickup.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_py _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/srv/StationManagerControlProtocol.srv" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_py _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/Vertex.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_py _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouteProgress.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_py _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/StationArray.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_py _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RobotGoals.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_py _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RouterStatus.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_py _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/RoutePrecondition.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_py _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_multi_robot_msgs/msg/OrderPosition.msg" NAME_WE)
add_dependencies(tuw_multi_robot_msgs_generate_messages_py _tuw_multi_robot_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(tuw_multi_robot_msgs_genpy)
add_dependencies(tuw_multi_robot_msgs_genpy tuw_multi_robot_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS tuw_multi_robot_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_multi_robot_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_multi_robot_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(tuw_multi_robot_msgs_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET nav_msgs_generate_messages_cpp)
  add_dependencies(tuw_multi_robot_msgs_generate_messages_cpp nav_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_multi_robot_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_multi_robot_msgs
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(tuw_multi_robot_msgs_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()
if(TARGET nav_msgs_generate_messages_eus)
  add_dependencies(tuw_multi_robot_msgs_generate_messages_eus nav_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_multi_robot_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_multi_robot_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(tuw_multi_robot_msgs_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET nav_msgs_generate_messages_lisp)
  add_dependencies(tuw_multi_robot_msgs_generate_messages_lisp nav_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_multi_robot_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_multi_robot_msgs
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(tuw_multi_robot_msgs_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()
if(TARGET nav_msgs_generate_messages_nodejs)
  add_dependencies(tuw_multi_robot_msgs_generate_messages_nodejs nav_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_multi_robot_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(tuw_multi_robot_msgs_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET nav_msgs_generate_messages_py)
  add_dependencies(tuw_multi_robot_msgs_generate_messages_py nav_msgs_generate_messages_py)
endif()
