cmake_minimum_required(VERSION 3.20)
project(MathUtils VERSION 1.0)

set(CMAKE_BUILD_TYPE Release)

message("MathUtils source path : " ${PROJECT_SOURCE_DIR} )

set(SOURCE_FILES 
    ${PROJECT_SOURCE_DIR}/source/clsMathUtils.cpp
)

message("source files : " ${SOURCE_FILES} )


add_library(MathUtils SHARED "${SOURCE_FILES}")

# Through CMake making conditional compiling for API/Funcitons based on users need
option(ADVANCED_API_ENABLED "This is flag for Advanced API opiton" ON)

if(ADVANCED_API_ENABLED)
    message("ADVANCED_API : ON")
    target_compile_definitions(MathUtils PUBLIC ADVANCED_API) 
    #using PUBLIC, ADVANCED_API macro applies to MathUtils target and all other target that links against MathUitls 
endif()

target_include_directories(MathUtils PUBLIC "${PROJECT_SOURCE_DIR}/include")
