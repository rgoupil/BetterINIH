cmake_minimum_required(VERSION 2.8)

project(INIH)

option(INIH_BUILD_CPP "Build INIH c++ version" ON)
option(INIH_ALLOW_MULTILINE "Allow multi-line entrie in the style of Python's ConfigParser" ON)
option(INIH_ALLOW_BOM "Allow a UTF-8 BOM sequence (0xEF 0xBB 0xBF) at the start of INI files" ON)
option(INIH_USE_STACK "Allocate the line buffer on the stack instead of using malloc" OFF)
option(INIH_STOP_ON_FIRST_ERROR "Stop on first parsing error" OFF)
#option(INIH_MAX_LINE "The maximum line length in bytes" 200)

if(INIH_ALLOW_MULTILINE)
	add_definitions(-DINI_ALLOW_MULTILINE=1)
else(INIH_ALLOW_MULTILINE)
	add_definitions(-DINI_ALLOW_MULTILINE=0)
endif(INIH_ALLOW_MULTILINE)
if(INIH_ALLOW_BOM)
	add_definitions(-DINI_ALLOW_BOM=1)
else(INIH_ALLOW_BOM)
	add_definitions(-DINI_ALLOW_BOM=0)
endif(INIH_ALLOW_BOM)
if(INIH_USE_STACK)
	add_definitions(-DINI_USE_STACK=1)
else(INIH_USE_STACK)
	add_definitions(-DINI_USE_STACK=0)
endif(INIH_USE_STACK)
if(INIH_STOP_ON_FIRST_ERROR)
	add_definitions(-DINI_STOP_ON_FIRST_ERROR=1)
else(INIH_STOP_ON_FIRST_ERROR)
	add_definitions(-DINI_STOP_ON_FIRST_ERROR=0)
endif(INIH_STOP_ON_FIRST_ERROR)

set(SOURCES)
set(HEADERS)

include_directories(".")
list(APPEND SOURCES "ini.c")
list(APPEND HEADERS "ini.h")

if(INIH_BUILD_CPP)
	include_directories("cpp")
	list(APPEND SOURCES "cpp/INIReader.cpp" "cpp/AINIReader.cpp")
	list(APPEND HEADERS "cpp/INIReader.h" "cpp/AINIReader.h")
endif(INIH_BUILD_CPP)

#TODO: Examples + (unit) testing

add_library(INIH ${SOURCES} ${HEADERS})

#TODO: This is sooo dirty, need to find a cleaner way to do that
set(INIH_BUILD_INCLUDE_DIR "${PROJECT_BINARY_DIR}/include/")
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${INIH_BUILD_INCLUDE_DIR})
configure_file(ini.h "${INIH_BUILD_INCLUDE_DIR}ini.h")
if(INIH_BUILD_CPP)
	configure_file(cpp/INIReader.h "${INIH_BUILD_INCLUDE_DIR}INIReader.h")
	configure_file(cpp/AINIReader.h "${INIH_BUILD_INCLUDE_DIR}AINIReader.h")
endif(INIH_BUILD_CPP)