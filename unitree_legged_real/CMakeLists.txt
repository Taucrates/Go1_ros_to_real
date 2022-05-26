cmake_minimum_required(VERSION 2.8.3)
project(unitree_legged_real)
add_compile_options(-std=c++11)
find_package(catkin REQUIRED COMPONENTS
    roscpp
    geometry_msgs
    unitree_legged_msgs
)
catkin_package()
include_directories(
    include
    ${Boost_INCLUDE_DIR}
    ${catkin_INCLUDE_DIRS}
)
set(CMAKE_CXX_FLAGS "-O3")
#set(ROBOT_SDK ${CATKIN_DEVEL_PREFIX}/../../../src CACHE PATH "Location of unitree_legged_sdk directory")
message("-- SOURCE DIRECTORY ${CMAKE_SOURCE_DIR}")

include_directories(${CMAKE_SOURCE_DIR}/Go1_ros_to_real/unitree_legged_sdk/include)
link_directories(${CMAKE_SOURCE_DIR}/Go1_ros_to_real/unitree_legged_sdk/lib)

message("-- CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
if("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "x86_64.*")
  set(ARCH amd64)
else()
  set(ARCH arm64)
endif()
string(CONCAT LEGGED_SDK_NAME libunitree_legged_sdk_${ARCH}.so)
set(EXTRA_LIBS ${LEGGED_SDK_NAME} lcm)


add_executable(example_walk src/exe/example_walk.cpp)
target_link_libraries(example_walk ${EXTRA_LIBS} ${catkin_LIBRARIES})
add_dependencies(example_walk ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(example_position src/exe/example_position.cpp)
target_link_libraries(example_position ${EXTRA_LIBS} ${catkin_LIBRARIES})
add_dependencies(example_position ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(state_sub src/exe/state_sub.cpp)
target_link_libraries(state_sub ${EXTRA_LIBS} ${catkin_LIBRARIES})
add_dependencies(state_sub ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(ros_udp src/exe/ros_udp.cpp)
target_link_libraries(ros_udp ${EXTRA_LIBS} ${catkin_LIBRARIES})
add_dependencies(ros_udp ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(prova src/exe/prova.cpp)
target_link_libraries(prova ${EXTRA_LIBS} ${catkin_LIBRARIES})
add_dependencies(prova ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

