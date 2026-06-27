cmake_minimum_required(VERSION 3.10)

project(MiniRedis)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

# Server
add_executable(server
    src/main.cpp
    src/server/server.cpp
    src/parser/parser.cpp
    src/database/database.cpp
    src/executor/executor.cpp
)

target_link_libraries(server PRIVATE Threads::Threads)

# Client
add_executable(client
    src/client/main.cpp
    src/client/client.cpp
)