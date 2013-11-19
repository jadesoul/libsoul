cmake_minimum_required(VERSION 2.6)
project (jadesoul)

add_executable (optparse_test optparse_test.cpp)
# target_link_libraries(optparse_test libjade)
install(TARGETS optparse_test DESTINATION ${BIN_INSTALL_DIR})


