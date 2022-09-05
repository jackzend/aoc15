#
# Generic CmakeList file
#
# @author Natesh Narain

cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_COMPILER clang++)


project(aoc15)


# find packages
find_package(Eigen3)
find_package(mio)

# includes
include_directories(
  include
)

set(DAY7_SOURCES src/day7.cpp)



add_executable(${PROJECT_NAME}_day7 ${DAY7_SOURCES})
target_compile_options(${PROJECT_NAME}_day7 PUBLIC -std=c++17 -O3)
target_link_libraries( ${PROJECT_NAME}_day7 PUBLIC mio::mio )

add_executable(${PROJECT_NAME}_test_mio src/test_mio.cpp)
target_compile_options(${PROJECT_NAME}_test_mio PUBLIC -std=c++17 -O3)
target_link_libraries( ${PROJECT_NAME}_test_mio PUBLIC mio::mio )

