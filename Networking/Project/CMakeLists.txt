cmake_minimum_required(VERSION 3.20)

project(networking VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#targets stored in References
set(OUTPUT_DIR "${PROJECT_SOURCE_DIR}/References")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})  # .a files
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})  # .so files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})  # executables

if(WIN32)
    set(PLATFORM_NAME "windows")
    add_definitions(-DPLATFORM_WINDOWS)
elseif(UNIX AND NOT APPLE)
    set(PLATFORM_NAME "linux")
    add_definitions(-DPLATFORM_LINUX)
elseif(APPLIE)
    set(PLATFORM_NAME "mac")
    add_definitions(-DPLATFORM_MAC)
endif()

add_subdirectory(TCPServer)
add_subdirectory(TCPClient)
add_subdirectory(Example)