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
elseif(ANDROID)
 	  message(STATUS, "HERE ANDROID")	
	  set(Boost_COMPILER "-clang")
	  set(Boost_USE_STATIC_LIBS ON)
	  if(ARM)
	    set(BOOST_ROOT "${CMAKE_BINARY_DIR}/../Boost-for-Android/build")
	    set(BOOST_LIBRARYDIR "${CMAKE_BINARY_DIR}/../Boost-for-Android/build/lib")
	  else()
	    message(STATUS, "HERE X86")
	    message(STATUS, "${CMAKE_BINARY_DIR}/../Boost-for-Android-x86/build") 
	    set(BOOST_ROOT "${CMAKE_BINARY_DIR}/../Boost-for-Android-x86/build")
	    set(BOOST_LIBRARYDIR "${CMAKE_BINARY_DIR}/../Boost-for-Android-x86/build/lib")
	    #set(BOOST_ROOT "~/boost_1_55_0")
	    #set(BOOST_LIBRARYDIR "~/boost_1_55_0/libs")
	    #set(BOOST_INCLUDEDIR "~/boost_1_55_0")

	  endif()
	  find_host_package(Boost 1.55 EXACT REQUIRED COMPONENTS random system thread filesystem chrono atomic)

	  set(OPENSSL_FOUND 1)
	  if(ARM)
	    set(OPENSSL_INCLUDE_DIR "${CMAKE_BINARY_DIR}/../openssl/armeabi-v7a/include")
	    set(OPENSSL_LIBRARIES
	      "${CMAKE_BINARY_DIR}/../openssl/armeabi-v7a/lib/libssl.a"
	      "${CMAKE_BINARY_DIR}/../openssl/armeabi-v7a/lib/libcrypto.a"
	      )
	  else()
	    set(OPENSSL_INCLUDE_DIR "${CMAKE_BINARY_DIR}/../openssl/x86/include")
	    set(OPENSSL_LIBRARIES
	      "${CMAKE_BINARY_DIR}/../openssl/x86/lib/libssl.a"
	      "${CMAKE_BINARY_DIR}/../openssl/x86/lib/libcrypto.a"
	      )
	  endif()

	  if(ARM)
	    set(LIBCXX_STL "${ANDROID_NDK}/sources/cxx-stl/gnu-libstdc++/4.8/libs/armeabi-v7a/thumb/libgnustl_static.a")
	  else()
	    set(LIBCXX_STL "${ANDROID_NDK}/sources/cxx-stl/gnu-libstdc++/4.8/libs/x86/libgnustl_static.a")
	  endif()
	  # These are used in the shared library case
	  set(ANDROID_STL_FLAGS
	    ${LIBCXX_STL}
	    atomic
	    dl
	    gcc
	    c
	    m
	    -nodefaultlibs
	    )

	  option(BUILD_SHARED_LIBS "Build shared Libraries." OFF)
	  set(BUILD_SAMPLES OFF)
	  option(BUILD_TESTS "Build tests." ON)

endif()


# Compiler (not platform) specific settings
if(ANDROID)
	  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-strict-aliasing")
	  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pedantic")
	  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-attributes -Wno-pointer-arith")
	  include_directories(
	    "${ANDROID_NDK}/sources/cxx-stl/gnu-libstdc++/4.8/include"
	    "${ANDROID_NDK}/sources/cxx-stl/gnu-libstdc++/4.8/libs/armeabi-v7a/include"
	    "${ANDROID_NDK}/sources/cxx-stl/gnu-libstdc++/4.8/include/backward"
	    )
	elseif((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR IOS)
	  message("-- Setting clang options")

	  set(WARNINGS "-Wall -Wextra -Wcast-qual -Wconversion -Wformat=2 -Winit-self -Winvalid-pch -Wmissing-format-attribute -Wmissing-include-dirs -Wpacked -Wredundant-decls")
	  set(OSX_SUPPRESSIONS "-Wno-overloaded-virtual -Wno-sign-conversion -Wno-deprecated -Wno-unknown-pragmas -Wno-reorder -Wno-char-subscripts -Wno-switch -Wno-unused-parameter -Wno-unused-variable -Wno-deprecated -Wno-unused-value -Wno-unknown-warning-option -Wno-return-type-c-linkage -Wno-unused-function -Wno-sign-compare -Wno-shorten-64-to-32 -Wno-reorder -Wno-unused-local-typedefs")
	  set(WARNINGS "${WARNINGS} ${OSX_SUPPRESSIONS}")

	  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -Wno-return-type-c-linkage -Wno-unneeded-internal-declaration")
	  set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
	  set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")

	  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-strict-aliasing")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

add_library(cpprest STATIC ${cpprest_SRC})

#message(STATUS, "cpprest_SRC = ${cpprest_SRC}")
#message(STATUS, "current = ${CMAKE_CURRENT_SOURCE_DIR}")

