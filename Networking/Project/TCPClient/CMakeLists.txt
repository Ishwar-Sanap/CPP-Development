project(tcpclient)

if(WIN32)
    set(SERVER_OS_SRC Windows/win.cpp)
elseif(UNIX AND NOT APPLE)
    set(SERVER_OS_SRC Linux/lin.cpp)
elseif(APPLIE)
    set(SERVER_OS_SRC "")
endif()


#Creating static library
add_library(tcpclient STATIC tcpclient.cpp ${SERVER_OS_SRC})

target_include_directories(tcpclient PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) 