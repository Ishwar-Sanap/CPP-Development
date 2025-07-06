cmake_minimum_required(VERSION 3.20)

# MyProject name of the Project
project(MyProject VERSION 1.0)

# MyProject → the name of the output executable (also called the target name)
# Source/main.cpp, Source/helper1.cpp → the source files to compile
add_executable(MyProject 
Source/main.cpp 
Source/helper1.cpp
)