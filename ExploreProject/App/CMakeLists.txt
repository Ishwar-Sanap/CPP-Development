cmake_minimum_required(VERSION 3.20)
project(APP VERSION 1.0)

set(CMAKE_BUILD_TYPE Release)

message("App source path : " ${PROJECT_SOURCE_DIR} )

add_executable(app main.cpp)
target_link_libraries(app MathUtils)