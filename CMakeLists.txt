cmake_minimum_required(VERSION 3.10)
project(PostgreSQLExample)

set(CMAKE_CXX_STANDARD 14)

include_directories("/usr/include/pqxx")
link_directories("/usr/lib/x86_64-linux-gnu")

add_executable(PostgreSQLExample main.cpp)

target_link_libraries(PostgreSQLExample pqxx pq)