cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


include_directories(${CMAKE_SOURCE_DIR})

add_executable(TestWrapper ./src/TestWrapper.cpp)

target_link_libraries(TestWrapper wrapper)
