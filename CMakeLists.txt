cmake_minimum_required(VERSION 3.25)
project(homework_3)
set(CMAKE_CXX_STANDARD 20)

find_package(Threads)

# Socket library.
add_library(mros_socket SHARED
        lib/socket/socket.cpp
        lib/socket/server_socket.cpp
        lib/socket/client_socket.cpp
        lib/socket/connection_socket.cpp
        lib/socket/message_socket/message_socket.cpp
        lib/socket/message_socket/client_message_socket.cpp
        lib/socket/message_socket/connection_message_socket.cpp
)
target_include_directories(mros_socket PUBLIC lib)

# Single threaded chat socket.
add_executable(single_threaded_chat_client test_manual/single_threaded_chat_client.cpp src/chat_socket.cpp)
target_include_directories(single_threaded_chat_client PRIVATE include)
target_link_libraries(single_threaded_chat_client mros_socket Threads::Threads)

add_executable(single_threaded_chat_server test_manual/single_threaded_chat_server.cpp src/chat_socket.cpp)
target_include_directories(single_threaded_chat_server PRIVATE include)
target_link_libraries(single_threaded_chat_server mros_socket Threads::Threads)

# Multi threaded chat socket.
add_executable(chat_client test_manual/chat_client.cpp src/chat_socket.cpp)
target_include_directories(chat_client PRIVATE include)
target_link_libraries(chat_client mros_socket Threads::Threads)

add_executable(chat_server test_manual/chat_server.cpp src/chat_socket.cpp)
target_include_directories(chat_server PRIVATE include)
target_link_libraries(chat_server mros_socket Threads::Threads)

# Multi threaded unsafe send.
add_executable(multi_send_client test_manual/multi_send_client.cpp src/multi_send_socket.cpp)
target_include_directories(multi_send_client PRIVATE include)
target_link_libraries(multi_send_client mros_socket Threads::Threads)

add_executable(multi_send_server test_manual/multi_send_server.cpp src/multi_send_socket.cpp src/chat_socket.cpp)
target_include_directories(multi_send_server PRIVATE include)
target_link_libraries(multi_send_server mros_socket Threads::Threads)

# Send on safe multi-threaded chat socket.
