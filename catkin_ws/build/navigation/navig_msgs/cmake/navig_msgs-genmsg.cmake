# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "navig_msgs: 0 messages, 1 services")

set(MSG_I_FLAGS "-Igeometry_msgs:/opt/ros/indigo/share/geometry_msgs/cmake/../msg;-Inav_msgs:/opt/ros/indigo/share/nav_msgs/cmake/../msg;-Isensor_msgs:/opt/ros/indigo/share/sensor_msgs/cmake/../msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg;-Iactionlib_msgs:/opt/ros/indigo/share/actionlib_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(navig_msgs_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/jorge/MobileRobot/catkin_ws/src/navigation/navig_msgs/srv/CalculatePath.srv" NAME_WE)
add_custom_target(_navig_msgs_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "navig_msgs" "/home/jorge/MobileRobot/catkin_ws/src/navigation/navig_msgs/srv/CalculatePath.srv" "geometry_msgs/PoseStamped:nav_msgs/OccupancyGrid:nav_msgs/Path:geometry_msgs/Quaternion:geometry_msgs/Point:geometry_msgs/Pose:nav_msgs/MapMetaData:std_msgs/Header"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages

### Generating Services
_generate_srv_cpp(navig_msgs
  "/home/jorge/MobileRobot/catkin_ws/src/navigation/navig_msgs/srv/CalculatePath.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/indigo/share/nav_msgs/cmake/../msg/OccupancyGrid.msg;/opt/ros/indigo/share/nav_msgs/cmake/../msg/Path.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/indigo/share/nav_msgs/cmake/../msg/MapMetaData.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/navig_msgs
)

### Generating Module File
_generate_module_cpp(navig_msgs
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/navig_msgs
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(navig_msgs_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(navig_msgs_generate_messages navig_msgs_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/jorge/MobileRobot/catkin_ws/src/navigation/navig_msgs/srv/CalculatePath.srv" NAME_WE)
add_dependencies(navig_msgs_generate_messages_cpp _navig_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(navig_msgs_gencpp)
add_dependencies(navig_msgs_gencpp navig_msgs_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS navig_msgs_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages

### Generating Services
_generate_srv_lisp(navig_msgs
  "/home/jorge/MobileRobot/catkin_ws/src/navigation/navig_msgs/srv/CalculatePath.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/indigo/share/nav_msgs/cmake/../msg/OccupancyGrid.msg;/opt/ros/indigo/share/nav_msgs/cmake/../msg/Path.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/indigo/share/nav_msgs/cmake/../msg/MapMetaData.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/navig_msgs
)

### Generating Module File
_generate_module_lisp(navig_msgs
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/navig_msgs
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(navig_msgs_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(navig_msgs_generate_messages navig_msgs_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/jorge/MobileRobot/catkin_ws/src/navigation/navig_msgs/srv/CalculatePath.srv" NAME_WE)
add_dependencies(navig_msgs_generate_messages_lisp _navig_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(navig_msgs_genlisp)
add_dependencies(navig_msgs_genlisp navig_msgs_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS navig_msgs_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages

### Generating Services
_generate_srv_py(navig_msgs
  "/home/jorge/MobileRobot/catkin_ws/src/navigation/navig_msgs/srv/CalculatePath.srv"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/PoseStamped.msg;/opt/ros/indigo/share/nav_msgs/cmake/../msg/OccupancyGrid.msg;/opt/ros/indigo/share/nav_msgs/cmake/../msg/Path.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/indigo/share/nav_msgs/cmake/../msg/MapMetaData.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/navig_msgs
)

### Generating Module File
_generate_module_py(navig_msgs
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/navig_msgs
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(navig_msgs_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(navig_msgs_generate_messages navig_msgs_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/jorge/MobileRobot/catkin_ws/src/navigation/navig_msgs/srv/CalculatePath.srv" NAME_WE)
add_dependencies(navig_msgs_generate_messages_py _navig_msgs_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(navig_msgs_genpy)
add_dependencies(navig_msgs_genpy navig_msgs_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS navig_msgs_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/navig_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/navig_msgs
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(navig_msgs_generate_messages_cpp geometry_msgs_generate_messages_cpp)
add_dependencies(navig_msgs_generate_messages_cpp nav_msgs_generate_messages_cpp)
add_dependencies(navig_msgs_generate_messages_cpp sensor_msgs_generate_messages_cpp)
add_dependencies(navig_msgs_generate_messages_cpp std_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/navig_msgs)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/navig_msgs
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(navig_msgs_generate_messages_lisp geometry_msgs_generate_messages_lisp)
add_dependencies(navig_msgs_generate_messages_lisp nav_msgs_generate_messages_lisp)
add_dependencies(navig_msgs_generate_messages_lisp sensor_msgs_generate_messages_lisp)
add_dependencies(navig_msgs_generate_messages_lisp std_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/navig_msgs)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/navig_msgs\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/navig_msgs
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(navig_msgs_generate_messages_py geometry_msgs_generate_messages_py)
add_dependencies(navig_msgs_generate_messages_py nav_msgs_generate_messages_py)
add_dependencies(navig_msgs_generate_messages_py sensor_msgs_generate_messages_py)
add_dependencies(navig_msgs_generate_messages_py std_msgs_generate_messages_py)
