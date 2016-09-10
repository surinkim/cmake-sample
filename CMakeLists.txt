cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

project(wrapper CXX)

add_subdirectory(gloox-1.0.17)
add_subdirectory(cpprestsdk-2.8.0/Release)

#add_executable(sample main.cpp)

#target_link_libraries(sample gloox)
#target_link_libraries(sample cpprest)
