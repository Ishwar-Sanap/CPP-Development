# Modern CMake Guide for C++ Projects

A practical reference for writing **clean, modern, and scalable
`CMakeLists.txt` files**.

---

# 1. Minimum Required CMake Version

Always start with the minimum required version.

```cmake
cmake_minimum_required(VERSION 3.20)
```

This ensures compatibility with modern CMake features.

---

# 2. Define the Project

Declare the project name, version, and supported languages.

```cmake
project(MyProject VERSION 1.0 LANGUAGES CXX)
```

# 3. Set Build Type

Used mainly in **single configuration generators**.

```cmake
set(CMAKE_BUILD_TYPE Release)
```

Common values:

- Debug
- Release
- RelWithDebInfo
- MinSizeRel

---

# 4. Set C++ Standard

```cmake
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
```

Recommended to disable compiler specific extensions.

---

# 5. Useful Debug Messages

```cmake
message(STATUS "Source dir: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "Binary dir: ${CMAKE_BINARY_DIR}")
```

```
Useful variables:

  Variable             Meaning
  -------------------- -----------------------
  CMAKE_SOURCE_DIR     Root source directory
  PROJECT_SOURCE_DIR   Project root
  CMAKE_BINARY_DIR     Build directory
```

---

# 6. Configure Output Directories

```cmake
set(OUTPUT_DIR "${PROJECT_SOURCE_DIR}/References")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
```

```
Output types:

  Type      Description
  --------- ------------------
  ARCHIVE   Static libraries  .a files
  LIBRARY   Shared libraries  .so files
  RUNTIME   Executables       .exe files
```

---

# 7. Add Executable

```cmake
add_executable(MyProject main.cpp)
```

Multiple files:

```cmake
add_executable(MyProject
    src/main.cpp
    src/utils.cpp
    src/helper.cpp
)
```

This will creates the executable target `MyProject` from the specified source files.

---

# 8. Include Directories (Modern Method)

❌ Old method :
includes the directory globally for all targets, which can lead to conflicts and is not recommended.

```cmake
include_directories(include)
```

✅ Modern target-based method

```cmake
target_include_directories(MyProject PRIVATE include)
```

It tells CMake that `MyProject` needs the `include` directory for compilation. The `PRIVATE` keyword means that this include path is only needed for this target and will not be propagated to targets that link against `MyProject`.

```
Visibility levels:

  Keyword     Meaning
  ----------- --------------------------
  PRIVATE     Only this target
  PUBLIC      This target + dependents
  INTERFACE   Only dependents
```

---

# 9. Creating Libraries

Creating the user defined static (.a) or Shared libraris (.so) from the source files

Static library:

```cmake
add_library(MyLib STATIC src/mylib.cpp)
```

Shared library:

```cmake
add_library(MyLib SHARED src/mylib.cpp)
```

Add include directories: required for finding header files when compiling the library and also for users of the library.

```cmake
target_include_directories(MyLib PUBLIC include)
```

---

# 10. Linking Libraries

Linking a library to an executable or another library. This tells CMake that `MyProject` depends on `MyLib`, and it will link the appropriate library files during the build process.

```cmake
target_link_libraries(MyProject PRIVATE MyLib)
```

Example with system library:

```cmake
target_link_libraries(MyProject PRIVATE pthread)
```

---

# 11. Modular Project Structure

Large projects should use multiple directories.
Keep CMakeLists Small and Modular. use multiple CMakeLists.txt files and add_subdirectory().

Example:

    MyProject/
    │
    ├── CMakeLists.txt
    ├── src/
    │   ├── CMakeLists.txt
    │   └── main.cpp
    │
    ├── include/
    │
    └── tests/

Main CMake:

```cmake
add_subdirectory(src)
add_subdirectory(tests)
```

---

# 12. Compiler Options

Global:

```cmake
add_compile_options(-Wall -Wextra)
```

Preferred (target based):

```cmake
target_compile_options(MyProject PRIVATE -Wall -Wextra)
```

---

# 13. Installing Targets

Install executable:

```cmake
install(TARGETS MyProject DESTINATION bin)
```

Install headers:

```cmake
install(DIRECTORY include/ DESTINATION include)
```

---

# 14. Using External Libraries

### find_package()

```cmake
find_package(Boost REQUIRED)
target_link_libraries(MyProject PRIVATE Boost::boost)
```

---

# 15. FetchContent (Dependency Download)

```cmake
include(FetchContent)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)

FetchContent_MakeAvailable(json)

target_link_libraries(MyProject PRIVATE nlohmann_json::nlohmann_json)
```

---

# 16. Managing Dependencies and build order

```cmake
add_dependencies(MyProject MyLib1 MyLib2 MyLib3)
```

This ensures that `MyLib1`, `MyLib2`, and `MyLib3` are built before `MyProject`. This is especially important when `MyProject` depends on these libraries, as it guarantees that all necessary components are available during the build process.

**Normally CMake determines build order automatically using the linking information provided by `target_link_libraries()`. However, there are cases where you might have targets that do not directly link to each other but still require a specific build order. In such cases, `add_dependencies()` can be used to explicitly specify the build order.**

# 17. Out-of-Source Builds

Never build inside the source folder.

    project/
       src/
       include/
       build/

Build:

    mkdir build
    cd build
    cmake ..
    cmake --build .

---

# 18. Full Example CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.20)

project(MyProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(MyLib src/mylib.cpp)

target_include_directories(MyLib PUBLIC include)

add_executable(MyProject src/main.cpp)

target_link_libraries(MyProject PRIVATE MyLib)

target_compile_options(MyProject PRIVATE -Wall -Wextra)
```

---

# 19. Commonly Used Commands

```
  Command                      Purpose
  ---------------------------- -------------------
  add_executable               Create executable
  add_library                  Create library
  target_link_libraries        Link libraries
  target_include_directories   Add header paths
  add_subdirectory             Include module
  install                      Install project
  enable_testing               Enable tests
  set(SRC_FILES src/main.cpp)  Set variable values
```

---

# 20. CMake Best Practices

✔ Prefer **target-based commands**\
✔ Keep `CMakeLists.txt` modular\
✔ Use **out-of-source builds**\
✔ Avoid global include directories\
✔ Use `FetchContent` or `find_package` for dependencies

---

# 21. Useful CMake Variables

```
  Variable                   Meaning
  -------------------------- -----------------
  PROJECT_NAME               Project name
  PROJECT_VERSION            Version
  CMAKE_SOURCE_DIR           Root source
  CMAKE_BINARY_DIR           Build directory
  CMAKE_CURRENT_SOURCE_DIR   Current folder
  WIN32                     Windows platform
  UNIX                      Unix/Linux platform
  APPLE                     Apple platform

```

---

# 22. Platform Detection

```cmake
if(WIN32)
    target_compile_definitions(MyProject PRIVATE PLATFORM_WINDOWS)
elseif(APPLE)
    target_compile_definitions(MyProject PRIVATE PLATFORM_MAC)
elseif(UNIX)
    target_compile_definitions(MyProject PRIVATE PLATFORM_LINUX)
endif()
```

C++ Usage :

```cpp
#ifdef PLATFORM_WINDOWS
#include <windows.h>
#endif

#ifdef PLATFORM_LINUX
#include <unistd.h>
#endif
```

---

# 23. Target specific compile definitions

```cmake
target_compile_definitions(MyProject PRIVATE WRITE_LOGS) # Define a macro without a value
target_compile_definitions(MyProject PRIVATE VERSION=1) # Define a macro with a value
```

C++ Usage:

```cpp
#ifdef WRITE_LOGS
std::cout << "Logging enabled" << std::endl;
std::cout << "Version: " << VERSION << std::endl;
#endif
```

---