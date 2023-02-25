cmake_minimum_required (VERSION 2.8)
project (Test)
set(CMAKE_BUILD_TYPE Debug)
include_directories(include "${CMAKE_CURRENT_BINARY_DIR}")

# set sources seperately! Use only header files for template classes because, 
# if you are using a template class its header must include in its cpp; 
# or definitions shall be written in itself; else cause link error after building.
#set(SOURCES *.h )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add the executable
add_executable(Test ${SOURCES} Test.cpp )
