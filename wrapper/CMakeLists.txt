cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

file(GLOB wrapper_SRC
	./src/*.h
	./src/*.cpp
)

add_library(wrapper STATIC ${wrapper_SRC})

target_link_libraries(wrapper gloox)
target_link_libraries(wrapper cpprest)
