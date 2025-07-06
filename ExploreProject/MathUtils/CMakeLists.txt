cmake_minimum_required(VERSION 3.20)
project(MathUtils VERSION 1.0)

set(CMAKE_BUILD_TYPE Release)

message("MathUtils source path : " ${PROJECT_SOURCE_DIR} )

set(SOURCE_FILES 
    ${PROJECT_SOURCE_DIR}/source/clsMathUtils.cpp
)

message("source files : " ${SOURCE_FILES} )


add_library(MathUtils SHARED "${SOURCE_FILES}")

target_include_directories(MathUtils PUBLIC "${PROJECT_SOURCE_DIR}/include")
