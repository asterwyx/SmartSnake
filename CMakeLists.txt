cmake_minimum_required(VERSION 3.0.0)

project(SmartSnake VERSION 1.0.0)

set(INC_DIR "C:/CCompiler/SDL2-2.0.12/include")
set(LINK_DIR "C:/CCompiler/SDL2-2.0.12/lib")
include_directories(${INC_DIR})
link_directories(${LINK_DIR})
link_libraries(SDL2d)

add_executable(test test.cpp)
target_link_libraries(test PRIVATE SDL2d)
