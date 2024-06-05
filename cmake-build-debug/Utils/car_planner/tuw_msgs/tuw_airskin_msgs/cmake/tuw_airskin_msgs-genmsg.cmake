# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "tuw_airskin_msgs: 3 messages, 0 services")

set(MSG_I_FLAGS "-Ituw_airskin_msgs:/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/melodic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(tuw_airskin_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinColors.msg" NAME_WE)
add_custom_target(_tuw_airskin_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tuw_airskin_msgs" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinColors.msg" "std_msgs/ColorRGBA:std_msgs/Header"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinInfo.msg" NAME_WE)
add_custom_target(_tuw_airskin_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tuw_airskin_msgs" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinInfo.msg" "std_msgs/Header"
)

get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinPressures.msg" NAME_WE)
add_custom_target(_tuw_airskin_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "tuw_airskin_msgs" "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinPressures.msg" "std_msgs/Header"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(tuw_airskin_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinColors.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_airskin_msgs
)
_generate_msg_cpp(tuw_airskin_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_airskin_msgs
)
_generate_msg_cpp(tuw_airskin_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinPressures.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_airskin_msgs
)

### Generating Services

### Generating Module File
_generate_module_cpp(tuw_airskin_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_airskin_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(tuw_airskin_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(tuw_airskin_msgs_generate_messages tuw_airskin_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinColors.msg" NAME_WE)
add_dependencies(tuw_airskin_msgs_generate_messages_cpp _tuw_airskin_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinInfo.msg" NAME_WE)
add_dependencies(tuw_airskin_msgs_generate_messages_cpp _tuw_airskin_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinPressures.msg" NAME_WE)
add_dependencies(tuw_airskin_msgs_generate_messages_cpp _tuw_airskin_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(tuw_airskin_msgs_gencpp)
add_dependencies(tuw_airskin_msgs_gencpp tuw_airskin_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS tuw_airskin_msgs_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(tuw_airskin_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinColors.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_airskin_msgs
)
_generate_msg_eus(tuw_airskin_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_airskin_msgs
)
_generate_msg_eus(tuw_airskin_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinPressures.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_airskin_msgs
)

### Generating Services

### Generating Module File
_generate_module_eus(tuw_airskin_msgs
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_airskin_msgs
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(tuw_airskin_msgs_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(tuw_airskin_msgs_generate_messages tuw_airskin_msgs_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinColors.msg" NAME_WE)
add_dependencies(tuw_airskin_msgs_generate_messages_eus _tuw_airskin_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinInfo.msg" NAME_WE)
add_dependencies(tuw_airskin_msgs_generate_messages_eus _tuw_airskin_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinPressures.msg" NAME_WE)
add_dependencies(tuw_airskin_msgs_generate_messages_eus _tuw_airskin_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(tuw_airskin_msgs_geneus)
add_dependencies(tuw_airskin_msgs_geneus tuw_airskin_msgs_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS tuw_airskin_msgs_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(tuw_airskin_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinColors.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_airskin_msgs
)
_generate_msg_lisp(tuw_airskin_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_airskin_msgs
)
_generate_msg_lisp(tuw_airskin_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinPressures.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_airskin_msgs
)

### Generating Services

### Generating Module File
_generate_module_lisp(tuw_airskin_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_airskin_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(tuw_airskin_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(tuw_airskin_msgs_generate_messages tuw_airskin_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinColors.msg" NAME_WE)
add_dependencies(tuw_airskin_msgs_generate_messages_lisp _tuw_airskin_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinInfo.msg" NAME_WE)
add_dependencies(tuw_airskin_msgs_generate_messages_lisp _tuw_airskin_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinPressures.msg" NAME_WE)
add_dependencies(tuw_airskin_msgs_generate_messages_lisp _tuw_airskin_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(tuw_airskin_msgs_genlisp)
add_dependencies(tuw_airskin_msgs_genlisp tuw_airskin_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS tuw_airskin_msgs_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(tuw_airskin_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinColors.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_airskin_msgs
)
_generate_msg_nodejs(tuw_airskin_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_airskin_msgs
)
_generate_msg_nodejs(tuw_airskin_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinPressures.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_airskin_msgs
)

### Generating Services

### Generating Module File
_generate_module_nodejs(tuw_airskin_msgs
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_airskin_msgs
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(tuw_airskin_msgs_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(tuw_airskin_msgs_generate_messages tuw_airskin_msgs_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinColors.msg" NAME_WE)
add_dependencies(tuw_airskin_msgs_generate_messages_nodejs _tuw_airskin_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinInfo.msg" NAME_WE)
add_dependencies(tuw_airskin_msgs_generate_messages_nodejs _tuw_airskin_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinPressures.msg" NAME_WE)
add_dependencies(tuw_airskin_msgs_generate_messages_nodejs _tuw_airskin_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(tuw_airskin_msgs_gennodejs)
add_dependencies(tuw_airskin_msgs_gennodejs tuw_airskin_msgs_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS tuw_airskin_msgs_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(tuw_airskin_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinColors.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/ColorRGBA.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_airskin_msgs
)
_generate_msg_py(tuw_airskin_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinInfo.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_airskin_msgs
)
_generate_msg_py(tuw_airskin_msgs
  "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinPressures.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_airskin_msgs
)

### Generating Services

### Generating Module File
_generate_module_py(tuw_airskin_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_airskin_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(tuw_airskin_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(tuw_airskin_msgs_generate_messages tuw_airskin_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinColors.msg" NAME_WE)
add_dependencies(tuw_airskin_msgs_generate_messages_py _tuw_airskin_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinInfo.msg" NAME_WE)
add_dependencies(tuw_airskin_msgs_generate_messages_py _tuw_airskin_msgs_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/Utils/car_planner/tuw_msgs/tuw_airskin_msgs/msg/AirskinPressures.msg" NAME_WE)
add_dependencies(tuw_airskin_msgs_generate_messages_py _tuw_airskin_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(tuw_airskin_msgs_genpy)
add_dependencies(tuw_airskin_msgs_genpy tuw_airskin_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS tuw_airskin_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_airskin_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/tuw_airskin_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(tuw_airskin_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(tuw_airskin_msgs_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_airskin_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/tuw_airskin_msgs
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(tuw_airskin_msgs_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(tuw_airskin_msgs_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_airskin_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/tuw_airskin_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(tuw_airskin_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(tuw_airskin_msgs_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_airskin_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/tuw_airskin_msgs
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(tuw_airskin_msgs_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(tuw_airskin_msgs_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_airskin_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_airskin_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/tuw_airskin_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(tuw_airskin_msgs_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(tuw_airskin_msgs_generate_messages_py geometry_msgs_generate_messages_py)
endif()
