cmake_minimum_required(VERSION 2.6)
project (jadesoul)

add_executable(set_test set_test.cpp)
# target_link_libraries(set_test libjade)
install(TARGETS set_test DESTINATION ${BIN_INSTALL_DIR})

