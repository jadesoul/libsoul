cmake_minimum_required(VERSION 2.6)
project (jadesoul)

add_executable(thread_test thread_test.cpp)
# target_link_libraries(thread_test libjade)
install(TARGETS thread_test DESTINATION ${BIN_INSTALL_DIR})

