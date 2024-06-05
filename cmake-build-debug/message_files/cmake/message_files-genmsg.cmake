# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "message_files: 6 messages, 2 services")

set(MSG_I_FLAGS "-Imessage_files:/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/melodic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(message_files_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg" NAME_WE)
add_custom_target(_message_files_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "message_files" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg" "geometry_msgs/Point32:geometry_msgs/Point:geometry_msgs/Polygon:std_msgs/Header"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Optimize.srv" NAME_WE)
add_custom_target(_message_files_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "message_files" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Optimize.srv" "geometry_msgs/Polygon:geometry_msgs/PointStamped:geometry_msgs/Point32:std_msgs/Header:message_files/StarConvexPolytope:message_files/StarConvexPolytopesStamped:geometry_msgs/Point"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PoseStampedArray.msg" NAME_WE)
add_custom_target(_message_files_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "message_files" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PoseStampedArray.msg" "geometry_msgs/Pose:geometry_msgs/Quaternion:geometry_msgs/Point:geometry_msgs/PoseStamped:std_msgs/Header"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg" NAME_WE)
add_custom_target(_message_files_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "message_files" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg" "geometry_msgs/Point:std_msgs/Header"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Assign.srv" NAME_WE)
add_custom_target(_message_files_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "message_files" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Assign.srv" "geometry_msgs/Point:message_files/SteinerTreeNode:std_msgs/Header"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytopesStamped.msg" NAME_WE)
add_custom_target(_message_files_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "message_files" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytopesStamped.msg" "geometry_msgs/Point32:message_files/StarConvexPolytope:geometry_msgs/Point:geometry_msgs/Polygon:std_msgs/Header"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeArray.msg" NAME_WE)
add_custom_target(_message_files_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "message_files" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeArray.msg" "geometry_msgs/Point:message_files/SteinerTreeNode:std_msgs/Header"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PolygonArrayStamped.msg" NAME_WE)
add_custom_target(_message_files_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "message_files" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PolygonArrayStamped.msg" "geometry_msgs/Polygon:geometry_msgs/Point32:std_msgs/Header"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/message_files
)
_generate_msg_cpp(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PoseStampedArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/message_files
)
_generate_msg_cpp(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/message_files
)
_generate_msg_cpp(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytopesStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/message_files
)
_generate_msg_cpp(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/message_files
)
_generate_msg_cpp(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PolygonArrayStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/message_files
)

### Generating Services
_generate_srv_cpp(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Assign.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/message_files
)
_generate_srv_cpp(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Optimize.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PointStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytopesStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/message_files
)

### Generating Module File
_generate_module_cpp(message_files
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/message_files
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(message_files_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(message_files_generate_messages message_files_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg" NAME_WE)
add_dependencies(message_files_generate_messages_cpp _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Optimize.srv" NAME_WE)
add_dependencies(message_files_generate_messages_cpp _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PoseStampedArray.msg" NAME_WE)
add_dependencies(message_files_generate_messages_cpp _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg" NAME_WE)
add_dependencies(message_files_generate_messages_cpp _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Assign.srv" NAME_WE)
add_dependencies(message_files_generate_messages_cpp _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytopesStamped.msg" NAME_WE)
add_dependencies(message_files_generate_messages_cpp _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeArray.msg" NAME_WE)
add_dependencies(message_files_generate_messages_cpp _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PolygonArrayStamped.msg" NAME_WE)
add_dependencies(message_files_generate_messages_cpp _message_files_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(message_files_gencpp)
add_dependencies(message_files_gencpp message_files_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS message_files_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/message_files
)
_generate_msg_eus(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PoseStampedArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/message_files
)
_generate_msg_eus(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/message_files
)
_generate_msg_eus(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytopesStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/message_files
)
_generate_msg_eus(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/message_files
)
_generate_msg_eus(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PolygonArrayStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/message_files
)

### Generating Services
_generate_srv_eus(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Assign.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/message_files
)
_generate_srv_eus(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Optimize.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PointStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytopesStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/message_files
)

### Generating Module File
_generate_module_eus(message_files
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/message_files
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(message_files_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(message_files_generate_messages message_files_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg" NAME_WE)
add_dependencies(message_files_generate_messages_eus _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Optimize.srv" NAME_WE)
add_dependencies(message_files_generate_messages_eus _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PoseStampedArray.msg" NAME_WE)
add_dependencies(message_files_generate_messages_eus _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg" NAME_WE)
add_dependencies(message_files_generate_messages_eus _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Assign.srv" NAME_WE)
add_dependencies(message_files_generate_messages_eus _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytopesStamped.msg" NAME_WE)
add_dependencies(message_files_generate_messages_eus _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeArray.msg" NAME_WE)
add_dependencies(message_files_generate_messages_eus _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PolygonArrayStamped.msg" NAME_WE)
add_dependencies(message_files_generate_messages_eus _message_files_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(message_files_geneus)
add_dependencies(message_files_geneus message_files_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS message_files_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/message_files
)
_generate_msg_lisp(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PoseStampedArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/message_files
)
_generate_msg_lisp(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/message_files
)
_generate_msg_lisp(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytopesStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/message_files
)
_generate_msg_lisp(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/message_files
)
_generate_msg_lisp(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PolygonArrayStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/message_files
)

### Generating Services
_generate_srv_lisp(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Assign.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/message_files
)
_generate_srv_lisp(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Optimize.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PointStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytopesStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/message_files
)

### Generating Module File
_generate_module_lisp(message_files
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/message_files
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(message_files_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(message_files_generate_messages message_files_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg" NAME_WE)
add_dependencies(message_files_generate_messages_lisp _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Optimize.srv" NAME_WE)
add_dependencies(message_files_generate_messages_lisp _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PoseStampedArray.msg" NAME_WE)
add_dependencies(message_files_generate_messages_lisp _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg" NAME_WE)
add_dependencies(message_files_generate_messages_lisp _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Assign.srv" NAME_WE)
add_dependencies(message_files_generate_messages_lisp _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytopesStamped.msg" NAME_WE)
add_dependencies(message_files_generate_messages_lisp _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeArray.msg" NAME_WE)
add_dependencies(message_files_generate_messages_lisp _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PolygonArrayStamped.msg" NAME_WE)
add_dependencies(message_files_generate_messages_lisp _message_files_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(message_files_genlisp)
add_dependencies(message_files_genlisp message_files_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS message_files_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/message_files
)
_generate_msg_nodejs(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PoseStampedArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/message_files
)
_generate_msg_nodejs(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/message_files
)
_generate_msg_nodejs(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytopesStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/message_files
)
_generate_msg_nodejs(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/message_files
)
_generate_msg_nodejs(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PolygonArrayStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/message_files
)

### Generating Services
_generate_srv_nodejs(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Assign.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/message_files
)
_generate_srv_nodejs(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Optimize.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PointStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytopesStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/message_files
)

### Generating Module File
_generate_module_nodejs(message_files
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/message_files
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(message_files_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(message_files_generate_messages message_files_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg" NAME_WE)
add_dependencies(message_files_generate_messages_nodejs _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Optimize.srv" NAME_WE)
add_dependencies(message_files_generate_messages_nodejs _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PoseStampedArray.msg" NAME_WE)
add_dependencies(message_files_generate_messages_nodejs _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg" NAME_WE)
add_dependencies(message_files_generate_messages_nodejs _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Assign.srv" NAME_WE)
add_dependencies(message_files_generate_messages_nodejs _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytopesStamped.msg" NAME_WE)
add_dependencies(message_files_generate_messages_nodejs _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeArray.msg" NAME_WE)
add_dependencies(message_files_generate_messages_nodejs _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PolygonArrayStamped.msg" NAME_WE)
add_dependencies(message_files_generate_messages_nodejs _message_files_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(message_files_gennodejs)
add_dependencies(message_files_gennodejs message_files_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS message_files_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/message_files
)
_generate_msg_py(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PoseStampedArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/message_files
)
_generate_msg_py(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/message_files
)
_generate_msg_py(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytopesStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/message_files
)
_generate_msg_py(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeArray.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/message_files
)
_generate_msg_py(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PolygonArrayStamped.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/message_files
)

### Generating Services
_generate_srv_py(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Assign.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/message_files
)
_generate_srv_py(message_files
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Optimize.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Polygon.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/PointStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point32.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg;/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytopesStamped.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/message_files
)

### Generating Module File
_generate_module_py(message_files
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/message_files
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(message_files_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(message_files_generate_messages message_files_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg" NAME_WE)
add_dependencies(message_files_generate_messages_py _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Optimize.srv" NAME_WE)
add_dependencies(message_files_generate_messages_py _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PoseStampedArray.msg" NAME_WE)
add_dependencies(message_files_generate_messages_py _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg" NAME_WE)
add_dependencies(message_files_generate_messages_py _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Assign.srv" NAME_WE)
add_dependencies(message_files_generate_messages_py _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytopesStamped.msg" NAME_WE)
add_dependencies(message_files_generate_messages_py _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeArray.msg" NAME_WE)
add_dependencies(message_files_generate_messages_py _message_files_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PolygonArrayStamped.msg" NAME_WE)
add_dependencies(message_files_generate_messages_py _message_files_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(message_files_genpy)
add_dependencies(message_files_genpy message_files_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS message_files_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/message_files)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/message_files
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(message_files_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(message_files_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/message_files)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/message_files
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(message_files_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(message_files_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/message_files)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/message_files
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(message_files_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(message_files_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/message_files)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/message_files
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(message_files_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(message_files_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/message_files)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/message_files\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/message_files
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(message_files_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(message_files_generate_messages_py geometry_msgs_generate_messages_py)
endif()
