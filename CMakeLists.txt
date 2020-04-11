cmake_minimum_required(VERSION 3.0.0)

project(SmartSnake VERSION 1.0.0)

# 设置第三方库的include路径
set(INC_DIR "C:/CCompiler/SDL2-2.0.12/x86_64-w64-mingw32/include/SDL2")
set(LINK_DIR "C:/CCompiler/SDL2-2.0.12/x86_64-w64-mingw32/lib")
# 设置include目录
include_directories(${INC_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
# 设置库目录
link_directories(${LINK_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
# add_test(test_object test_object.cpp object.h object.cpp)

add_executable(test_object test_object.cpp object.h object.cpp)
target_link_libraries(test_object PRIVATE SDL2main)
target_link_libraries(test_object PRIVATE SDL2)