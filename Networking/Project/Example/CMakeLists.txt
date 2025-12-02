project(demo)

#creating exutable for server and client

# server example build
add_executable(server server.cpp)
target_link_libraries(server tcpserver) # linking TCPServer library
set(INCLUDE_SERVER_DIRS "../TCPServer")
target_include_directories(server PUBLIC ${INCLUDE_SERVER_DIRS})


# # client example build
add_executable(client client.cpp)
target_link_libraries(client tcpclient) # linking TCPClient library
set(INCLUDE_CLIENT_DIRS "../TCPClient")
target_include_directories(server PUBLIC ${INCLUDE_CLIENT_DIRS})