cmake_minimum_required(VERSION 2.8.3)
project(tb_digital_twin)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)
add_message_files(
        FILES
        Current.msg
        Voltage.msg
        Power.msg
        Float32Stamped.msg
)
generate_messages(
        DEPENDENCIES
        std_msgs
)
catkin_package(
        CATKIN_DEPENDS message_runtime roscpp
        INCLUDE_DIRS include
)
###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
    include
    ${catkin_INCLUDE_DIRS}
)
add_library(DATA_LOGGER
    include/data_logger/data_logger.hpp
    include/data_logger/data_logger.cpp
)
## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(EfficiencyMap src/EfficiencyMap.cpp)
add_executable(Controller
        src/Controller.cpp
        src/pid.cpp)
add_executable(angularConverter src/AngularConverter.cpp)
add_executable(windingCheck src/WindingErrorChecker.cpp)
add_executable(powerCalculator src/PowerCalculator.cpp)
add_executable(currentVoltageFlow
        src/currentVoltageFlow.cpp
        src/ParseDewetron.cpp
        src/PhysicalValueTemplate.cpp)
add_executable(torqueCalculator src/TorqueCalculator.cpp)
## Specify libraries to link a library or executable target against
#target_link_libraries(${PROJECT_NAME}_CCN

target_link_libraries(EfficiencyMap DATA_LOGGER
  ${catkin_LIBRARIES})
target_link_libraries(angularConverter DATA_LOGGER
  ${catkin_LIBRARIES})
target_link_libraries(Controller
  ${catkin_LIBRARIES})
target_link_libraries(currentVoltageFlow DATA_LOGGER
  ${catkin_LIBRARIES})
target_link_libraries(powerCalculator DATA_LOGGER
  ${catkin_LIBRARIES})
target_link_libraries(windingCheck
  ${catkin_LIBRARIES})
target_link_libraries(torqueCalculator DATA_LOGGER
  ${catkin_LIBRARIES})
