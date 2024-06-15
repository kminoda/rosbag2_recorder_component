cmake_minimum_required(VERSION 3.5)
project(rosbag2_recorder_component)

## Compile options
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

## Dependencies
find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

## Include directories
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(rosbag2_transport REQUIRED)
include_directories(
  ${rosbag2_transport_INCLUDE_DIRS}
)

## Targets
ament_auto_add_library(rosbag2_transport_component SHARED
  src/rosbag2_recorder_component.cpp
)

ament_target_dependencies(rosbag2_transport_component
  rclcpp
  rclcpp_components
  rosbag2_transport
)

rclcpp_components_register_node(rosbag2_transport_component
  PLUGIN "rosbag2_transport::RecorderComponent"
  EXECUTABLE rosbag2_transport_node
)

## Package
ament_auto_package(
  INSTALL_TO_SHARE
    # config
    launch
)