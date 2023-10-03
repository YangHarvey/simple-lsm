include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(skiplist_test skiplist_test.cpp)
target_link_libraries(skiplist_test simple-lsm gtest pthread)