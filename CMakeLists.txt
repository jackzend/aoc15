#
# Generic CmakeList file
#
# @author Natesh Narain

cmake_minimum_required(VERSION 2.8)

project(aoc15)


# find packages
find_package(Eigen3)

# includes
include_directories(
  include/utils
)

set(DAY7_SOURCES src/day7.cpp)



add_executable(${PROJECT_NAME}_day7 ${DAY7_SOURCES})
target_compile_options(${PROJECT_NAME}_day7 PUBLIC -std=c++17 -O3)

