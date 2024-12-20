cmake_minimum_required(VERSION 3.10)

project(robotic_home)

include_directories(src)
include_directories(include)
include_directories(test)

#add_executable(main src/main.cpp)
#add_executable(maze_test test/maze_test.cpp)
#add_executable(randomRobot_test test/randomRobot_test.cpp)
#add_executable(rightHandRuleRobot_test test/rightHandRuleRobot_test.cpp)

#add_library(maze include/Maze.h src/Maze.cpp)
#add_library(randomRobot include/Robot.h include/RandomRobot.h src/RandomRobot.cpp)
#add_library(rightHandRuleRobot include/Robot.h include/RightHandRuleRobot.h src/RightHandRuleRobot.cpp)

#target_link_libraries(main maze randomRobot rightHandRuleRobot)
#target_link_libraries(maze_test maze)
#target_link_libraries(randomRobot_test maze randomRobot)
#target_link_libraries(rightHandRuleRobot_test maze rightHandRuleRobot)

set(CMAKE_CXX_STANDARD 11)
