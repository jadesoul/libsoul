#~~~ Auto generated by gen_cmake_recursively.py @  ~~~
cmake_minimum_required(VERSION 2.6)
project(jadesoul)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

#add_subdirectory
add_subdirectory(utils utils_dir)

#include_directories
include_directories(../../include)

#for each target
add_executable(includes includes.cpp)
add_custom_command(
	TARGET includes
	POST_BUILD
	COMMAND python ${CMAKE_SOURCE_DIR}/scripts/move_target.py ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} includes
	COMMENT "Postbuild action : move target includes"
)

add_executable(thread thread.cpp)
add_custom_command(
	TARGET thread
	POST_BUILD
	COMMAND python ${CMAKE_SOURCE_DIR}/scripts/move_target.py ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} thread
	COMMENT "Postbuild action : move target thread"
)
