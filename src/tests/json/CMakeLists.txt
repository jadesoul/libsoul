cmake_minimum_required(VERSION 2.6)
project (jadesoul)

add_executable (json_test json_test.cpp)
install(TARGETS json_test DESTINATION ${BIN_INSTALL_DIR})
