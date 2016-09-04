cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

file(GLOB gloox_SRC
	"./src/*.h"
	"./src/*.cpp"
)

add_library(gloox STATIC ${gloox_SRC})

#message(STATUS, "gloox_SRC = ${gloox_SRC}")
