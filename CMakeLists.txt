cmake_minimum_required(VERSION 3.8.2)
set(PROJECT find-ifdefs)
project(${PROJECT})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include_directories(include)
set(HEADERS
	include/params.h
	include/parser.h
	include/string_utils.h)
set(SOURCES
	src/params.cpp
	src/parser.cpp
	src/main.cpp)

#add_definitions(-Wall)
add_executable(${PROJECT} ${SOURCES} ${HEADERS})
install(TARGETS ${PROJECT} DESTINATION bin)
