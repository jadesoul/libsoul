cmake_minimum_required(VERSION 2.6)
project(jadesoul)

#set(CMAKE_INSTALL_PREFIX "/usr/local")
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

set(LIB_INSTALL_DIR "lib")
set(INC_INSTALL_DIR "include")
set(BIN_INSTALL_DIR "bin")

set(CMAKE_CXX_FLAGS "-fPIC -O3 -Wall -D_GNU_SOURCE -std=c++0x")

#set(CMAKE_CXX_FLAGS_DEBUG "-g ")
#set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

#set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O2 -DNDEBUG")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

set(components
	bootstrap
	algorithms
	corelib
	encoding
	debug
	logging
	datetime
	filesys
	network
	regexp
	json
	random
	utils
	thread
	optparse
	ml
	include
)

include_directories(${components})

macro(add_source name)
	#message("Adding source ${CMAKE_CURRENT_SOURCE_DIR}/${name}")
	list(APPEND sub_sources "${CMAKE_CURRENT_SOURCE_DIR}/${name}")
endmacro(add_source)

macro(add_sources names)
	#message("Adding sources in ${CMAKE_CURRENT_SOURCE_DIR}: ${names}")
	foreach(name ${names})
		add_source(${name})
	endforeach(name)
endmacro(add_sources)

foreach(component ${components})
	add_subdirectory(${component})
	get_directory_property(${component}_sources DIRECTORY ${component} DEFINITION sub_sources)
	list(APPEND sources ${${component}_sources})
endforeach(component)

#message("Got all sources: ${sources}")
#add_library(libjade_static STATIC ${sources})
# if(UNIX)
# target_link_libraries(libjade_static pthread)
# endif(UNIX)
#set_target_properties(libjade_static PROPERTIES OUTPUT_NAME "jade")
#install(TARGETS libjade_static DESTINATION ${LIB_INSTALL_DIR})

add_library(libjade_shared SHARED ${sources})
if(UNIX)
target_link_libraries(libjade_shared pthread)
endif(UNIX)
set_target_properties(libjade_shared PROPERTIES OUTPUT_NAME "jade")
set_target_properties(libjade_shared PROPERTIES VERSION 1)
install(TARGETS libjade_shared DESTINATION ${LIB_INSTALL_DIR})

link_libraries(libjade_shared)

set(subdirs
	cmake
	tests
	apps
	tools
)

foreach(subdir ${subdirs})
	if ( EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${subdir} )
		add_subdirectory( ${subdir} )
	endif ( EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${subdir} )
endforeach(subdir)
