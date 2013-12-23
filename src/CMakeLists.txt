cmake_minimum_required(VERSION 2.6)
project(jadesoul)

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

# set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/..) # or "/usr/local"
set(CMAKE_INSTALL_PREFIX ~)

set(LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib")
# set(INC_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include")
set(INC_INSTALL_DIR "${CMAKE_SOURCE_DIR}/../include")
set(BIN_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/bin")

set(CMAKE_CXX_FLAGS "-fPIC -Wall -D_GNU_SOURCE -std=c++0x")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O2 -DNDEBUG")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

include_directories(${INC_INSTALL_DIR})

aux_source_directory(. sources)

message("Got Source Files: ${sources}")
add_library(libsoul_static STATIC ${sources})
if(UNIX)
	target_link_libraries(libsoul_static pthread)
endif(UNIX)
set_target_properties(libsoul_static PROPERTIES OUTPUT_NAME "soul")
install(TARGETS libsoul_static DESTINATION ${LIB_INSTALL_DIR})

add_library(libsoul_shared SHARED ${sources})
if(UNIX)
	target_link_libraries(libsoul_shared pthread)
endif(UNIX)
set_target_properties(libsoul_shared PROPERTIES OUTPUT_NAME "soul")
set_target_properties(libsoul_shared PROPERTIES VERSION 1.2 SOVERSION 1)
install(TARGETS libsoul_shared DESTINATION ${LIB_INSTALL_DIR})

# link_libraries(libsoul_static)
link_libraries(libsoul_shared)

set(subdirs
	tests
	apps
	tools
)

foreach(subdir ${subdirs})
	if ( EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${subdir} )
		add_subdirectory( ${subdir} )
	endif ( EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${subdir} )
endforeach(subdir)
