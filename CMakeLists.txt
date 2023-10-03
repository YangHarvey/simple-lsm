# 设置最低版本要求
cmake_minimum_required(VERSION 3.0)

# 设置项目名称
project(Simple-LSMTree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
# 添加可执行文件，将源文件编译为可执行文件
file(GLOB SIMPLE-LSMTREE-SOURCES src/*.cpp)
add_library(simple-lsm ${SIMPLE-LSMTREE-SOURCES})

add_subdirectory(test)
