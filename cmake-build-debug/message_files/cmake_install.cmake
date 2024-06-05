# Install script for directory: /home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/message_files/msg" TYPE FILE FILES
    "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PolygonArrayStamped.msg"
    "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/PoseStampedArray.msg"
    "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytope.msg"
    "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/StarConvexPolytopesStamped.msg"
    "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeNode.msg"
    "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/msg/SteinerTreeArray.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/message_files/srv" TYPE FILE FILES
    "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Assign.srv"
    "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/srv/Optimize.srv"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/message_files/cmake" TYPE FILE FILES "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/cmake-build-debug/message_files/catkin_generated/installspace/message_files-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/cmake-build-debug/devel/include/message_files")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/cmake-build-debug/devel/share/roseus/ros/message_files")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/cmake-build-debug/devel/share/common-lisp/ros/message_files")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/cmake-build-debug/devel/share/gennodejs/ros/message_files")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python2" -m compileall "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/cmake-build-debug/devel/lib/python2.7/dist-packages/message_files")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/cmake-build-debug/devel/lib/python2.7/dist-packages/message_files")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/cmake-build-debug/message_files/catkin_generated/installspace/message_files.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/message_files/cmake" TYPE FILE FILES "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/cmake-build-debug/message_files/catkin_generated/installspace/message_files-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/message_files/cmake" TYPE FILE FILES
    "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/cmake-build-debug/message_files/catkin_generated/installspace/message_filesConfig.cmake"
    "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/cmake-build-debug/message_files/catkin_generated/installspace/message_filesConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/message_files" TYPE FILE FILES "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/package.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/message_files" TYPE DIRECTORY FILES "/home/melodies/SYSU_ROBOT/Communication_Relay/src/communication-relay/message_files/include/message_files/" FILES_MATCHING REGEX "/[^/]*\\.h$" REGEX "/\\.svn$" EXCLUDE)
endif()

