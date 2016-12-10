# Install script for directory: /home/jorge/MobileRobot/catkin_ws/src/operation/joystick_operation

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/home/jorge/MobileRobot/catkin_ws/install")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/jorge/MobileRobot/catkin_ws/build/operation/joystick_operation/catkin_generated/installspace/joystick_operation.pc")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/joystick_operation/cmake" TYPE FILE FILES
    "/home/jorge/MobileRobot/catkin_ws/build/operation/joystick_operation/catkin_generated/installspace/joystick_operationConfig.cmake"
    "/home/jorge/MobileRobot/catkin_ws/build/operation/joystick_operation/catkin_generated/installspace/joystick_operationConfig-version.cmake"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/joystick_operation" TYPE FILE FILES "/home/jorge/MobileRobot/catkin_ws/src/operation/joystick_operation/package.xml")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

