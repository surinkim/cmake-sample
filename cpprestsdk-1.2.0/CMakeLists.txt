cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)


set(Casablanca_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Release/include)
set(Casablanca_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Release/src)

set(Casablanca_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/Release/include ${CMAKE_CURRENT_SOURCE_DIR}/Release/src/pch )

include_directories(${Casablanca_INCLUDE_DIRS})


file(GLOB_RECURSE cpprest_SRC
	"${Casablanca_INCLUDE_DIR}/cpprest/*.h"
	"${Casablanca_INCLUDE_DIR}/compat/*.h"
	"${Casablanca_INCLUDE_DIR}/pplx/*.h"
	"./Release/src/pch/stdafx.h"

    "${Casablanca_SOURCE_DIR}/http/client/http_msg_client.cpp"
    "${Casablanca_SOURCE_DIR}/http/common/http_helpers.cpp"
    "${Casablanca_SOURCE_DIR}/http/common/http_msg.cpp"
    "${Casablanca_SOURCE_DIR}/http/logging/log.cpp"
    "${Casablanca_SOURCE_DIR}/http/uri/uri.cpp"
    "${Casablanca_SOURCE_DIR}/http/uri/uri_builder.cpp"
    "${Casablanca_SOURCE_DIR}/http/uri/uri_parser.cpp"
    "${Casablanca_SOURCE_DIR}/json/json.cpp"
    "${Casablanca_SOURCE_DIR}/utilities/asyncrt_utils.cpp"
    "${Casablanca_SOURCE_DIR}/utilities/base64.cpp"
    "${Casablanca_SOURCE_DIR}/utilities/dllmain.cpp"
    "${Casablanca_SOURCE_DIR}/pch/stdafx.cpp"
)

set(Casablanca_DEFINITIONS -D_NO_ASYNCRTIMP -D_NO_PPLXIMP CACHE INTERNAL "Definitions for consume casablanca library")


# Platform (not compiler) specific settings
if(WIN32)
	add_definitions(${Casablanca_DEFINITIONS} -D_WINSOCK_DEPRECATED_NO_WARNINGS -DWIN32)
endif()


# Compiler (not platform) specific settings
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

add_library(cpprest STATIC ${cpprest_SRC})

#message(STATUS, "cpprest_SRC = ${cpprest_SRC}")
#message(STATUS, "current = ${CMAKE_CURRENT_SOURCE_DIR}")

