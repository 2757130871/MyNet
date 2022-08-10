cmake_minimum_required(3.0)
project(echo_server)

#调试使用
set(CMAKE_BUILD_TYPE "Debug")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
include_directories(${PROJECT_SOURCE_DIR}../include)


set(SRC_LIST .)
#生成的可执行文件名
add_executable(echoserver ${SRC_LIST})

target_link_libraries(echoserver mynet)
