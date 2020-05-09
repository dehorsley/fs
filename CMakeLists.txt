cmake_minimum_required (VERSION 2.8.7)

project(webtty)

option(NNG_TESTS "Build nanomsg tests" OFF)
option(NNG_TOOLS "Build nanomsg tools" OFF)
#option(NNG_ENABLE_TLS "Enable TLS protocol (requires mbedTLS)" ON)

add_subdirectory(nng EXCLUDE_FROM_ALL)

add_executable(server server.c stream.c msg.c)
target_link_libraries(server nng c)
