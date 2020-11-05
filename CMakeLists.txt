cmake_minimum_required(VERSION 3.1.0)

project(learn_thread)

set( CMAKE_CXX_COMPILER "g++" )
# set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )
set(CMAKE_BUILD_TYPE Debug CACHE STRING "set build type to debug")

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


# add_library(${PROJECT_NAME}
# )

add_executable(learn_1 learn_thread1.cc )



# add_executable(yuzhi common_op.cc )


target_link_libraries( learn_1   -lpthread -lm )




