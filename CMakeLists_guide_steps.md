## CMakeLists.txt Writing Rules & Steps ##

#  Start with Minimum Required Version
# This ensures compatibility with your CMake installation.
cmake_minimum_required(VERSION 3.20)

# Declare Project Name and Version
# Set the project name and optionally the version and language.
project(MyProject VERSION 1.0 LANGUAGES CXX)

# Set Build Type (Debug/Release)
set(CMAKE_BUILD_TYPE Release)

# Set the C++ Standard
# Define the standard you want (e.g., C++11, C++17, C++20):
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# For debugging CMake (It will print output on console )
message("Current source dir : " ${CMAKE_CURRENT_SOURCE_DIR} )

# storing the all ouptput files in perticular directory
set(OUTPUT_DIR "${PROJECT_SOURCE_DIR}/References")

# targets stored in References
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})  # .a files
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})  # .so files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})  # executables

# Add an Executable This builds an executable from your source file(s):
add_executable(MyProject main.cpp)

# Multiple files:
add_executable(MyProject main.cpp helper.cpp utils.cpp)


# Add Include Directories
# Tell the compiler where to find header files:
target_include_directories(MyProject PRIVATE include)

Use PRIVATE, PUBLIC, or INTERFACE depending on visibility:
PRIVATE: only for this target
PUBLIC: for this and any dependent target
INTERFACE: only for dependents, not this target

# Link Libraries (inbuild or use defined libraries to main executable)
# If you’re using any libraries (e.g., pthread, math, Boost, etc.):
target_link_libraries(MyProject PRIVATE pthread)

# Add Subdirectories (for multi-folder projects)
# If you have a modular structure:

MyProject/
├── CMakeLists.txt
├── src/
│   └── CMakeLists.txt

# In main CMakeLists.txt:
add_subdirectory(src)

# In src/CMakeLists.txt:
# Creating the user defined static and Shared libraris (.a / .so )
add_library(MyLib STATIC mylib.cpp)
add_library(MyLib SHARED mylib.cpp)

# Tell the compiler where to find header files:
target_include_directories(MyLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add Compiler Flags (Optional)
add_compile_options(-Wall -Wextra)

Or per target:
target_compile_options(MyProject PRIVATE -Wall -Wextra)

*********************************************************************************


🧱 Full Example: CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(MyProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(MyProject
    src/main.cpp
    src/hello.cpp
)

target_include_directories(MyProject PRIVATE include)

target_compile_options(MyProject PRIVATE -Wall -Wextra)

target_link_libraries(MyProject PRIVATE pthread)

*********************************************************************************

🏁 Steps to Build the Project
#  Terminal commands
mkdir build
cd build
cmake ..
cmake --build .
./MyProject  #  Run the executable

*********************************************************************************
