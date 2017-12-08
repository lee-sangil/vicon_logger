cmake_minimum_required(VERSION 2.8.3)
project(data_logger)

find_package(catkin REQUIRED cmake_modules)
find_package(Eigen REQUIRED)
find_package(catkin REQUIRED COMPONENTS
		roscpp
		roslib
)

catkin_package(
		DEPENDS Eigen
)

set(includeDirs ${includeDirs} ${CMAKE_CURRENT_BINARY_DIR})
set(includeDirs ${includeDirs} include)

set(SRC ${SRC} src/main.cpp)
set(SRC ${SRC} src/DataLogger.cpp)
set(SRC ${SRC} include/DataLogger.h)

include_directories( ${includeDirs} )
include_directories( ${catkin_INCLUDE_DIRS} )
include_directories( ${Eigen_INCLUDE_DIRS} )

add_executable (data_logger ${SRC} )
target_link_libraries (data_logger ${catkin_LIBRARIES} )
target_link_libraries (data_logger ${Eigen_LIBRARIES} )
